#pragma once

#include "ofMain.h"
//
#include "ofxGrayscale.h"
#include "ofxBlur.h"
#include "ofxNormals.h"
#include "ofxDisplacePixels.h"
//
#include "ofxVoro.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void makeTissue(int _nCells, int _width, int _height, int _deep);

    ofEasyCam   cam;
    ofLight     light;

    vector<ofPoint> cellCentroids;
    vector<float>   cellRadius;
    vector<ofVboMesh>  cellMeshes;
    vector<ofVboMesh>  cellMeshWireframes;

    //
    ofVideoGrabber      video;

    ofxGrayscale        grayscale;
    ofxBlur             blur;
    ofxNormals          normals;
    ofxDisplacePixels   disp;

    int             width, height;

    bool            bDrawVideo;
    bool            bDrawNormals;
    bool            bDrawField;
    bool            bCapture;
    //

};
