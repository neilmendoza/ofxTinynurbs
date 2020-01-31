/*
 *  Nurbs.h
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

#pragma once

#include "tinynurbs.h"
#include <map>

namespace nm
{
    class Nurbs
    {
    public:
        Nurbs();
        
        void addVertices(const std::vector<glm::vec3>& vs);
        void addVertex(const glm::vec3& v);
        glm::vec3 getVertex(unsigned idx) { return nurbs.control_points[idx]; }
        
        void drawCurve(unsigned resolution = 50);
        void drawVertices(float radius = 4.f);
        void draw(float vertexRadius = 4.f);
        
        glm::vec3 curvePoint(float t) const;
        glm::vec3 curveTangent(float t) const;
        
        float distanceLookup(float t);

        void clear();
        unsigned size() const { return nurbs.control_points.size(); }
        
    private:
        void updateDistanceLut(unsigned lutSize = 1000);
        void updateKnots();
        
        std::map<float, float> distanceLut;
        
        tinynurbs::Curve<float> nurbs;
    };
}
