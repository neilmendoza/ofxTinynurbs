#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    spline.addVertices({
        glm::vec3(-100, 0, 0), // std::vector of 2D points
        glm::vec3(0, 100, 0),
        glm::vec3(100, 0, 0),
        glm::vec3(200, 0, 0),
    
        glm::vec3(140, 0, 100),
        glm::vec3(140, 288, -15),
        glm::vec3(140, 288, -139),
        glm::vec3(18, 288, -183)
    });
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
    cam.begin();
    spline.draw();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
