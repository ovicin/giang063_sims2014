//
//  FlowField.cpp
//  VectorField
//
//  Created by Gabriel Gianordoli on 11/30/14
//  Implementing a 3D vector field
//
//  Based on Charlie Whitney's code from 10/7/13.
//
//

#include "FlowField.h"

FlowField::FlowField() {
    
}

void FlowField::setup( int width, int height, int depth, int res ) {
    fieldWidth = width;
    fieldHeight = height;
    fieldDepth = depth;
    resolution = res;
    
    int cols = fieldWidth / resolution;
    int rows = fieldHeight / resolution;
    int zRows = fieldDepth / resolution;

    for( int z = 0; z < zRows; z++){
        vector<vector<ofVec3f> > myPlane;
        for( int y=0; y<rows; y++){
            vector<ofVec3f> myList;
            for( int x=0; x<cols; x++){
                ofVec3f dir(10.0, 0, 5.0);
                myList.push_back( dir );
            }
            myPlane.push_back( myList );
        }
        flowList.push_back(myPlane);
    }
    
    // Debug
//    for( int z=0; z<flowList.size(); z++){
//        vector<vector<ofVec3f> > myPlane = flowList[z];
//        for( int y = 0; y < myPlane.size(); y++){
//            vector<ofVec3f> myList = myPlane[y];
//            for( int x=0; x < myList.size(); x++){
//                cout << "[z]" << z << "][" << y << "][" << x << "] : " << flowList[z][y][x].x << ", " << flowList[z][y][x].y << ", " << flowList[z][y][x].z << endl;
//            }
//        }
//    }
}

//void FlowField::setRandom( const float &strength ) {
//    for( int y=0; y<flowList.size(); y++){
//        for( int x=0; x<flowList[y].size(); x++){
//            flowList[y][x].set( ofRandom(-1,1) * strength, ofRandom(-1,1) * strength );
//        }
//    }
//}
//
void FlowField::setPerlin() {
    
    for( int z=0; z<flowList.size(); z++){
        vector<vector<ofVec3f> > myPlane = flowList[z];
        for( int y = 0; y < myPlane.size(); y++){
            vector<ofVec3f> myList = myPlane[y];
            for( int x=0; x < myList.size(); x++){
                float noise = ofMap( ofNoise(x*0.05, y*0.05, z*0.05), 0, 1, 0, TWO_PI);
                flowList[z][y][x].set( ofVec3f( cos(noise)*20, sin(noise)*20, sin(noise)*20) );            }
        }
    }
}
//
void FlowField::update() {
    
    for( int z=0; z<flowList.size(); z++){
        vector<vector<ofVec3f> > myPlane = flowList[z];
        for( int y = 0; y < myPlane.size(); y++){
            vector<ofVec3f> myList = myPlane[y];
            for( int x=0; x < myList.size(); x++){
                flowList[z][y][x] *= 0.99;
                
                if( flowList[z][y][x].length() < 1.0){
                    flowList[z][y][x].normalize();
                }
            }
        }
    }
}
//
ofVec3f FlowField::getForceAtPosition(ofVec3f pos) {
    float pctX = pos.x / fieldWidth;
    float pctY = pos.y / fieldHeight;
    float pctZ = pos.z / fieldDepth;
    
    int cols = fieldWidth / resolution;
    int rows = fieldHeight / resolution;
    int zRows = fieldDepth / resolution;
    
    int xVal = ofClamp( pctX * cols, 0, cols-1 );
    int yVal = ofClamp( pctY * rows, 0, rows-1 );
    int zVal = ofClamp( pctZ * zRows, 0, zRows-1 );
    
    ofVec3f newPos;
    newPos.set( flowList[zVal][yVal][xVal] );
    
    return newPos;
}
//
void FlowField::addDirection(ofVec3f _dir) {
    _dir.normalize();
    for( int z=0; z<flowList.size(); z++){
        vector<vector<ofVec3f> > myPlane = flowList[z];
        for( int y = 0; y < myPlane.size(); y++){
            vector<ofVec3f> myList = myPlane[y];
            for( int x=0; x < myList.size(); x++){
                flowList[z][y][x] += _dir;
            }
        }
    }
}
//
//void FlowField::addForceAtPosition(ofVec2f _force, ofVec2f pos) {
////    cout << _force << endl;
//    _force.normalize();
//    
//    float pctX = pos.x / fieldWidth;
//    float pctY = pos.y / fieldHeight;
//    
//    int cols = fieldWidth / resolution;
//    int rows = fieldHeight / resolution;
//    
//    int xVal = ofClamp( pctX * cols, 0, cols-1 );
//    int yVal = ofClamp( pctY * rows, 0, rows-1 );
//    
////    ofVec2f newPos;
////    newPos.set(  );
////    newPos += _force;
//    
//    flowList[yVal][xVal] += _force;
//    
////    return newPos;
//}
//
//void FlowField::addRepelForce(float x, float y, float radius, float strength) {
//    
//    float pctX = x / fieldWidth;
//    float pctY = y / fieldWidth;
//    
//    int cols = fieldWidth / resolution;
//    int rows = fieldHeight / resolution;
//    
//    int xVal = pctX * cols;
//    int yVal = pctY * rows;
//    
//    
//    ofVec2f mousePos(x, y);
//    
//    for( int y=0; y<flowList.size(); y++){
//        for( int x=0; x<flowList[y].size(); x++){
//            ofVec2f np( x*resolution, y*resolution );
//            
//            if( np.distance(mousePos) < radius ){
//                float pct = 1 - (np.distance(mousePos) / radius);
//                
//                // add strength in the direction it's already moving in
////                flowList[y][x] += flowList[y][x].normalized() * strength;
//                
//                // add strength away from the mouse
//                ofVec2f dir = (np - mousePos);
//                flowList[y][x] += dir.normalized() * strength;
//            }
//        }
//    }
//}
//
//void FlowField::addAttractForce(float x, float y, float radius, float strength) {
//    
//    float pctX = x / fieldWidth;
//    float pctY = y / fieldWidth;
//    
//    int cols = fieldWidth / resolution;
//    int rows = fieldHeight / resolution;
//    
//    int xVal = pctX * cols;
//    int yVal = pctY * rows;
//    
//    ofVec2f mousePos(x, y);
//    
//    for( int y=0; y<flowList.size(); y++){
//        for( int x=0; x<flowList[y].size(); x++){
//            ofVec2f np( x*resolution, y*resolution );
//            
//            if( np.distance(mousePos) < radius ){
//                float pct = 1 - (np.distance(mousePos) / radius);
//                
//                // add strength against the direction it's already moving in
////                flowList[y][x] -= flowList[y][x].normalized() * strength;
//                
//                // add strength towards the mouse
//                ofVec2f dir = (np - mousePos);
//                flowList[y][x] -= dir.normalized() * strength;
//            }
//        }
//    }
//}
//
//void FlowField::addCircularForce(float x, float y, float radius, float strength) {
//    
//    float pctX = x / fieldWidth;
//    float pctY = y / fieldWidth;
//    
//    int cols = fieldWidth / resolution;
//    int rows = fieldHeight / resolution;
//    
//    int xVal = pctX * cols;
//    int yVal = pctY * rows;
//    
//    ofVec2f mousePos(x, y);
//    
//    for( int y=0; y<flowList.size(); y++){
//        for( int x=0; x<flowList[y].size(); x++){
//            ofVec2f np( x*resolution, y*resolution );
//            
//            if( np.distance(mousePos) < radius ){
//                float pct = 1 - (np.distance(mousePos) / radius);
//                
//                // add strength towards the mouse
//                ofVec2f dir = (np - mousePos);
//                flowList[y][x].x -= dir.normalized().y * strength;
//                flowList[y][x].y += dir.normalized().x * strength;
//            }
//        }
//    }
//}
//
void FlowField::draw() {
    
    for( int z=0; z<flowList.size(); z++){
        vector<vector<ofVec3f> > myPlane = flowList[z];
        for( int y = 0; y < myPlane.size(); y++){
            vector<ofVec3f> myList = myPlane[y];
            for( int x=0; x < myList.size(); x++){
                ofVec3f np( x*resolution, y*resolution, z*resolution );
                drawVectorAt( flowList[z][y][x], np, flowList[z][y][x].length() );
                ofVec3f tmpPos(x*resolution, y*resolution, z*resolution);
            }
        }
    }
}

void FlowField::drawVectorAt( const ofVec3f &vec, const ofVec3f &pos, const float &strength ) {
    ofVec3f np = pos;
//    cout << strength << endl;
    drawVector( np, np + vec.normalized() * strength, 5, 3 );
}

void FlowField::drawVector( const ofVec3f &start, const ofVec3f &end, float headLength, float headRadius ) {
	const int NUM_SEGMENTS = 32;
	float lineVerts[3*2];
	ofVec3f coneVerts[NUM_SEGMENTS+2];
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, lineVerts );
	lineVerts[0] = start.x; lineVerts[1] = start.y; lineVerts[2] = start.z;
	lineVerts[3] = end.x; lineVerts[4] = end.y; lineVerts[5] = end.z;
	glDrawArrays( GL_LINES, 0, 2 );
	
	// Draw the cone
	ofVec3f axis = ( end - start ).normalized();
    ofVec3f temp = ( axis.dot( ofVec3f(0,1,0) ) > 0.999f ) ? axis.crossed( ofVec3f(1,0,0) ) : axis.crossed( ofVec3f(0,1,0) );
	ofVec3f left = ofVec3f(axis.crossed( temp )).normalized();
	ofVec3f up = axis.crossed( left ).normalized();
    
	glVertexPointer( 3, GL_FLOAT, 0, &coneVerts[0].x );
	coneVerts[0] = ofVec3f( end + axis * headLength );
	for( int s = 0; s <= NUM_SEGMENTS; ++s ) {
		float t = (float)s / (float)NUM_SEGMENTS;
		coneVerts[s+1] = ofVec3f( end + left * headRadius * cos( t * 2.0f * 3.14159f )
                                 + up * headRadius * sin( t * 2.0f * 3.14159f ) );
	}
	glDrawArrays( GL_TRIANGLE_FAN, 0, NUM_SEGMENTS+2 );
    
	// draw the cap
	glVertexPointer( 3, GL_FLOAT, 0, &coneVerts[0].x );
	coneVerts[0] = end;
	for( int s = 0; s <= NUM_SEGMENTS; ++s ) {
		float t = s / (float)NUM_SEGMENTS;
		coneVerts[s+1] = ofVec3f( end - left * headRadius * (float)cos( t * 2 * 3.14159f )
                                 + up * headRadius * (float)sin( t * 2 * 3.14159f ) );
	}
	glDrawArrays( GL_TRIANGLE_FAN, 0, NUM_SEGMENTS+2 );
    
	glDisableClientState( GL_VERTEX_ARRAY );
}