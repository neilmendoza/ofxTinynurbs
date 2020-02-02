/*
 *  Nurbs.cpp
 *
 *  Copyright (c) 2019, Neil Mendoza, http://www.neilmendoza.com
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Neil Mendoza nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "Nurbs.h"
#include "ofMain.h"

namespace nm
{
    Nurbs::Nurbs()
    {
        nurbs.degree = 2;
    }
    
    void Nurbs::addVertices(const std::vector<glm::vec3>& vs)
    {
        nurbs.control_points.insert(nurbs.control_points.end(), vs.begin(), vs.end());
        
        updateKnots();
    }

    void Nurbs::addVertex(const glm::vec3& v)
    {
        nurbs.control_points.push_back(v);
       
        if (nurbs.control_points.size() > 2) updateKnots();
    }

    void Nurbs::draw(float vertexRadius, unsigned resolution)
    {
        drawCurve(resolution);
        drawVertices(vertexRadius);
    }

    void Nurbs::drawVertices(float radius)
    {
        for (auto& v : nurbs.control_points)
        {
            ofDrawSphere(v, radius);
        }
    }

    glm::vec3 Nurbs::curvePoint(float t) const
    {
        return tinynurbs::curvePoint(nurbs, t);
    }

    glm::vec3 Nurbs::curveTangent(float t) const
    {
        return tinynurbs::curveTangent(nurbs, t);
    }

    void Nurbs::drawCurve(unsigned resolution)
    {
        if (nurbs.control_points.size() > 1)
        {
            for (unsigned i = 1; i < resolution; ++i)
            {
                ofDrawLine(
                    tinynurbs::curvePoint(nurbs, (i - 1) / (float)(resolution - 1)),
                    tinynurbs::curvePoint(nurbs, i / (float)(resolution - 1))
                );
            }
        }
    }
    
    float Nurbs::distanceLookup(float t)
    {
        if (distanceLut.empty()) updateDistanceLut();
        
        auto it = distanceLut.lower_bound(t);
        float lowKey = it->first;
        float lowVal = it->second;
        it++;
        float highKey = it->first;
        float highVal = it->second;
        
        return ofMap(t, lowKey, highKey, lowVal, highVal);
    }
    
    void Nurbs::updateDistanceLut(unsigned lutSize)
    {
        vector<float> distances;
        distances.push_back(0);
        glm::vec3 prevPt = curvePoint(0.f);
        for (unsigned i = 1; i < lutSize; ++i)
        {
            glm::vec3 pt = curvePoint(i / float(lutSize - 1));
            distances.push_back(distances[i - 1] + glm::distance(prevPt, pt));
            prevPt = pt;
        }
        
        distanceLut.clear();
        for (unsigned i = 0; i < lutSize; ++i)
        {
            distanceLut[distances[i] / distances.back()] = i / float(lutSize - 1);
        }
    }

    void Nurbs::updateKnots()
    {
        // check if degree, knots and control points are configured as per
        // #knots == #control points + degree + 1
        
        const unsigned knots = nurbs.control_points.size() + nurbs.degree + 1;
        const unsigned repeatedKnots = nurbs.degree + 1;
        const unsigned numIncreasingKnots = knots - 2 * repeatedKnots;
        
        nurbs.knots.clear();
        
        for (unsigned i = 0; i < repeatedKnots; ++i)
        {
            nurbs.knots.push_back(0.f);
        }
        
        for (unsigned i = 0; i < numIncreasingKnots; ++i)
        {
            nurbs.knots.push_back((i + 1) / (float)(numIncreasingKnots + 1));
        }
        
        for (unsigned i = 0; i < repeatedKnots; ++i)
        {
            nurbs.knots.push_back(1.f);
        }
    }
    
    void Nurbs::clear()
    {
        nurbs.control_points.clear();
        nurbs.knots.clear();
        distanceLut.clear();
    }
}
