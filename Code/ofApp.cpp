#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0, 0, 0);
  
    int numPetals = 8;
    hue = 0;
    maxParticles =2000;
    ofEnableLighting();
    ofEnableDepthTest();
    light.setPosition(0, -600, 300);
    ofEnableDepthTest();
    ofSetSphereResolution(4);
    
    

    ofSetVerticalSync(true);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    font.load("Helvetica", 18);
    
    // Display the list of available serial devices
        serial.listDevices();
        vector <ofSerialDeviceInfo> devicelist = serial.getDeviceList();

        // Set the serial communication baud rate
        int baud = 9600;
        
        // Connect to the serial device
        // Change this line depending on your platform and device
        serial.setup("/dev/cu.usbmodem1101", baud);
    
    
    
    
    
    mainMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        
        ofEnableDepthTest();
        
        width = 10;
        height = 10;
        // set our rendering styles to false
        b_messyMesh = false;
        b_perlinMesh = false;
        b_marchMesh = false;
        b_drawWireFrame = true;

            perlinRange =1.0;
            perlinHeight = 5.0;
        
        ofBackground(0);
        mainCam.setPosition(0, 0, 80);
        
    
        
    for (int y = 0; y < height; y++){
        for (int x = 0; x<width; x++){
            mainMesh.addVertex( ofPoint(x - width /2 , y - height / 2 ,0)); // mesh index = x + y*width
            mainMesh.addColor(ofFloatColor(2,0,50));
            
        }
        
    }
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            mainMesh.addIndex(x+y*width);
            mainMesh.addIndex((x+1)+y*width);
            mainMesh.addIndex(x+(y+1)*width);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (serial.available() > 0) {
      // Read the byte data from the serial connection
      byteData = serial.readByte();
        
      cout << "Received byte data: " << byteData << endl;
    }
    else {
            // Set the `byteData` to a default value (for example, 0)
            byteData = 0;
          }



    if (particles.size()> maxParticles){
        particles.erase(particles.begin());
    }
    for(int i=0; i<particles.size();i++){
        particles[i].update();
    }

    
    
    
    
    ofColor newColor;
        ofVec3f newPosition, oldPosition;
        
        // change the z value for each vertex in our mesh
        if (b_messyMesh) {
            if (!b_marchMesh ){
            for (int i = 0; i < mainMesh.getNumVertices(); i++){ // find the total of all the vertices in the mesh and loop through them
                newPosition = mainMesh.getVertex(i); // get the current x,y,z position of this vertex
                newPosition.z = ofRandom(-perlinHeight, perlinHeight); // set the z value of it to a new random number
                mainMesh.setVertex(i, newPosition);
            }
        }
    }
}
       
    

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofRotateDeg(180, 0, 0, 1);
    light.enable();
    //    ofDrawAxis(400);
    for(int i=0; i<particles.size();i++){
        particles[i].draw();
    }
    light.disable();
    cam.end();
    
  
    if (byteData == 99){
        particle newParticle(0,0,0,hue);
        particles.push_back(newParticle);
    }
   
    
    
    
    glPointSize(10);
        mainCam.begin();

        if (b_drawWireFrame){
            mainMesh.drawWireframe();
        }
        
        mainCam.end();
        
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){

        case ' ':
            int numParticles = 200;
            for (int i=0; i< numParticles; i++){
                particle newParticle(0,0,0,hue);
                particles.push_back(newParticle);
            }
            break;
    }
    
    
    
    switch(key) {
           
           case ' ':
               b_messyMesh = !b_messyMesh;
               break;
                
              
               
       }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    hue = ofRandom(255);
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
//--------------------------------------------------------------

particle::particle(int x, int y, int z, int hue){
    position = glm::vec3(x, y, z);
    force = glm::vec3(0, 0,0);
    direction = glm::vec3( ofRandom( -2.0, 2.0), ofRandom( -2.0, 2.0) ,ofRandom( -2.0, 2.0));
    size = 4;
    color.setHsb(200,  255, 255);
}
//--------------------------------------------------------------

particle::~particle(){
}
//--------------------------------------------------------------

void particle::update(){
    position += direction ;
    direction +=  force;
        if (size > 1){
            size -=0.07;
        }
        float brightness = color.getBrightness();
        float myHue = color.getHue();
    
        if (brightness >20){
           // color.setBrightness( brightness -=0.5 );
            color.setHue( myHue -=0.5 );
    
        }
}

//--------------------------------------------------------------

void particle::draw(){
//    ofSetColor(color);
//    ofDrawCircle(position, size);
    ofSetColor(color);
    ofDrawSphere(position, size);
}
