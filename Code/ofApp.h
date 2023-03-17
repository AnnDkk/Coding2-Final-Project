#pragma once

#include "ofMain.h"


class particle {
public:
    ofColor color;
    float size;
    glm::vec3 force, position, direction;
    
    void update();
    void draw();
    
    particle(int x, int y, int z, int hue);
    ~particle();
};


class ofApp :
public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		
    vector<particle> particles;
    int hue;
    ofEasyCam cam;
    ofLight light;
    int maxParticles;
    
    ofMesh mainMesh;
        ofEasyCam mainCam;

        int width, height;
        bool b_messyMesh, b_perlinMesh, b_drawWireFrame, b_marchMesh;
        float perlinRange, perlinHeight;
    
    ofTrueTypeFont font;
    ofSerial serial;
    
    string sensorValue;
    int byteData;
    string msg;
    char sendData = 1;
    
    bool byteDataReceived = false;
    bool whiteScreen = false;
    
    
   
    
    
  
};
