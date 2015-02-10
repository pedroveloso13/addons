#include "ofApp.h"
#define STRINGIFY(A) #A

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofEnableSmoothing();

    light.setPosition(100,500, 100);
    cam.setAutoDistance(true);

    makeTissue(50, ofGetHeight()*0.8, ofGetHeight()*0.8, 20);

    //added
    width = 640;
    height = 480;
    ofSetWindowShape(width, height);
    video.initGrabber(width, height);
    grayscale.allocate(width, height);
    blur.allocate(width, height);
    blur.setPasses(10);
    normals.allocate(width, height);
    disp.allocate(width,height);
    bDrawVideo = false;
    bDrawField = false;
    bDrawNormals = false;
    bCapture = true;
    //
}

void testApp::makeTissue(int _nCells, int _width, int _height, int _deep){

    //  Fresh begining
    //
    cellMeshes.clear();
    cellCentroids.clear();
    cellRadius.clear();

    //  Define a container
    //
    voro::container con(-_width*0.5,_width*0.5,
                        -_height*0.5,_height*0.5,
                        -_deep*0.5,_deep*0.5,
                        1,1,1,
                        true,true,true,
                        8);

    //  Add walls (un comment one pair if you like to shape the container)
    //
    voro::wall_cylinder cyl(0,0,0,0,0,20, min(_width*0.5, _height*0.5));
    con.add_wall(cyl);

//    voro::wall_sphere sph(0, 0, 0, min(_width*0.5, _height*0.5) );
//    con.add_wall(sph);

//    voro::wall_cone cone(0,0,min(_width*0.5, _height*0.5),0,0,-1,atan(0.5));
//    con.add_wall(cone);

    //  Add the cell seed to the container
    //
    for(int i = 0; i < _nCells;i++){
        ofPoint newCell = ofPoint(ofRandom(-_width*0.5,_width*0.5),
                                  ofRandom(-_height*0.5,_height*0.5),
                                  ofRandom(-_deep*0.25,_deep*0.25));

        addCellSeed(con, newCell, i, true);
    }

    cellMeshes = getCellsFromContainer(con,0.0);
    cellMeshWireframes = getCellsFromContainer(con,0.0,true);
    cellRadius = getCellsRadius(con);
    cellCentroids = getCellsCentroids(con);
}

//--------------------------------------------------------------
void testApp::update(){
    //added
    video.update();

    if ( video.isFrameNew() ){
        grayscale.setTexture( video.getTextureReference() );
        grayscale.update();
        blur << grayscale;
        blur.update();
        normals << blur;
        normals.update();
    }

    if (bCapture){
        disp.getBackBuffer()->begin();
        ofSetColor(255);
        video.draw(0, 0);
        disp.getBackBuffer()->end();

        bCapture = false;
    }

    disp.setTexture(normals.getTextureReference());
    disp.update();
    //

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(100); //255

    //added
    ofSetColor(255);
    if ( bDrawVideo ){
        video.draw(0,0,ofGetWidth(),ofGetHeight());
        ofSetColor(255,200);
    }

    disp.draw(0,0,ofGetWidth(),ofGetHeight());

    if ( bDrawNormals ){
        ofSetColor(255);
        normals.draw(0,0,ofGetWidth(),ofGetHeight());
    }
    //

    ofPushMatrix();
    cam.begin();
    light.enable();
    ofEnableLighting();
    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < cellCentroids.size(); i++){
        ofSetColor(0);
		ofSphere(cellCentroids[i], cellRadius[i]*0.15);
    }

    for(int i = 0; i < cellMeshes.size(); i++){
        ofSetColor(100,30);
        cellMeshes[i].drawFaces();

        ofPushStyle();
        ofSetLineWidth(3);
        ofSetColor(100);
        cellMeshWireframes[i].draw();
        ofPopStyle();
    }

    glDisable(GL_DEPTH_TEST);
    ofDisableLighting();
    light.disable();
    cam.end();
    ofPopMatrix();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    //
    if (key == 'v'){
        bDrawVideo = !bDrawVideo;
    } else if (key == 'n'){
        bDrawNormals = !bDrawNormals;
    } else {
        bCapture = true;
    }
    //

    if ( key == 'f'){
        ofToggleFullscreen();
    } else {
        makeTissue(50, ofGetWidth()*0.8, ofGetHeight()*0.8,20);
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

    blur.setPasses(ofMap(y, 0, ofGetHeight(),0, 10, true));

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
