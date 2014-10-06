//
//  Ribbon.cpp
//  06_midterm
//
//  Created by Gabriel Gianordoli on 10/5/14.
//
//

#include "Ribbon.h"

void Ribbon::setup(float _x, float _y){
    
    depthInterval = -1;
    
    ofPoint pos = ofPoint(_x, _y);
    originalLine.addVertex(pos);
}

//------------------------------------------------------------
void Ribbon::update(int _shapeSmoothing){
//    originalLine = originalLine.getSmoothed(_shapeSmoothing, 0);
}

//------------------------------------------------------------
void Ribbon::applySmoothing(int _shapeSmoothing){
    cout << _shapeSmoothing << endl;
    currentLine = currentLine.getSmoothed(_shapeSmoothing, 0);
    cout << currentLine.size();
}

//------------------------------------------------------------
void Ribbon::resetSmoothing(){
    currentLine = originalLine;
}

//------------------------------------------------------------
void Ribbon::addPoint(float _x, float _y){
    ofPoint pos = ofPoint(_x, _y);
    originalLine.addVertex(pos);
    currentLine = originalLine;
}


//------------------------------------------------------------
void Ribbon::draw(bool _useCamera){
    
    if(!_useCamera){
        ofNoFill();
        ofSetColor(255);
        ofSetLineWidth(20);
        currentLine.draw();
    
    }else{
        vector<ofPoint> path = currentLine.getVertices();
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        for(unsigned int i = 1; i < path.size(); i++){
            
            //find this point and the next point
            ofVec3f thisPoint = ofPoint(path[i-1].x, path[i-1].y, (i-1) * depthInterval);
            ofVec3f nextPoint = ofPoint(path[i].x, path[i].y, i * depthInterval);
            
            //get the direction from one to the next.
            //the ribbon should fan out from this direction
            ofVec3f direction = (nextPoint - thisPoint);
            
            //get the distance from one point to the next
            float distance = direction.length();
            
            //get the normalized direction. normalized vectors always have a length of one
            //and are really useful for representing directions as opposed to something with length
            ofVec3f unitDirection = direction.normalized();
            
            //find both directions to the left and to the right
            ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
            ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
            
            //use the map function to determine the distance.
            //the longer the distance, the narrower the originalLine.
            //this makes it look a bit like brush strokes
    //		float thickness = ofMap(distance, 0, 60, 20, 2, true);
            float thickness = 10;
            
            //calculate the path to the left and to the right
            //by extending the current point in the direction of left/right by the length
            ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
            ofVec3f rightPoint = thisPoint+toTheRight*thickness;
            
            //add these path to the triangle strip
            mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
            mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
        }
        
        //end the shape
        mesh.draw();
    }
}