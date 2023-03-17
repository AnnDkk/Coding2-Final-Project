# Coding Two - Final Project
### Quiet Chaos —— by An Dong
<div align=center>
<img src="https://github.com/AnnDkk/Coding2-Final-Project/blob/main/image/WechatIMG465.png" width="700" height="500">
</div>

## Introduction

This project creates a seemingly stable and harmonious space. However, with the constant fluctuation of the texture in the middle, the particles emitted gradually make people feel a sense of chaos, disorder and anxiety. After touching the Arduino, the red light flashes with the particle to stop releasing and return to the brief tranquility when it is still needed to maintain the state.

## Documentation
Video Link：https://ual.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=388f259f-9f6a-44c7-b28d-afc800d45052

## Code Application

My initial idea was to continue the style of finalwork made at the end of last semester and still make wave points. At first I tried to write in Boid, but its representation was so regular that I saw other ways through queries. I generate random balls in the specified box of and attach textures to them. But I changed the method again because I couldn't control the multiple forms of expression.
Finally, I learned to use the OpenFrameworks particle system and completed the work by combining Shader and Arduino I learned in class.


> Set mesh surface

        for (int y = 0; y < height; y++){
        or (int x = 0; x<width; x++){
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
    
    
  > Set basic parameters for particles and 3D effects

    ofSetBackgroundColor(0, 0, 0);
    int numPetals = 8;
    hue = 0;
    maxParticles =2000;
    ofEnableLighting();
    ofEnableDepthTest();
    light.setPosition(0, -600, 300);
    ofEnableDepthTest();
    ofSetSphereResolution(4);



>   Set the Arduino to receive data
    
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
        
        
<div align=center>
<img src="https://github.com/AnnDkk/Coding2-Final-Project/blob/main/image/IMG_4375.JPG" width="400" height="300"><img src="https://github.com/AnnDkk/Coding2-Final-Project/blob/main/image/WechatIMG474.png" width="400" height="300">
</div>
        


>Link the write receive signal at update to the corresponding control particle and set the parameters of the mensh plane

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
> Finally, three groups of information are output at ofApp: : drawo() and the Arduino received instruction is connected with the particle for judgment output. The write space key in keyPressed does most of the interaction

## Achievements

<div align=center>
        <img src="https://github.com/AnnDkk/Coding2-Final-Project/blob/main/image/WechatIMG472.png" width="400" height="300"><img src="https://github.com/AnnDkk/Coding2-Final-Project/blob/main/image/WechatIMG464.png" width="400" height="300">
<img src="https://github.com/AnnDkk/Coding2-Final-Project/blob/main/image/WechatIMG470.png" width="400" height="300">
</div>


