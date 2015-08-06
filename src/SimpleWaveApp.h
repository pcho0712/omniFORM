//
//  SimpleWaveApp.h
//  TMG Shape Displays
//
//  Created by Daniel Windham on 6/26/15.
//  Copyright 2015 MIT Media Lab. All rights reserved.
//

#pragma once

#include "Application.h"


// This code is meant as an easy-to-understand example of an Application. Feel
// free to copy it as a way to get started. Please don't add to or change this
// file, though - keep it a simple example for new people meeting the codebase.

class SimpleWaveApp : public Application {
public:
    SimpleWaveApp(ObjectDetector *detector);

    void update(float dt);
    void drawGraphicsForShapeDisplay();
    string appInstructionsText();
    void keyPressed(int key);

    string getName() {return "Simple Wave";};

private:
    void updateHeights();
    
    float normalizedPhase = 0;
    float frequency;
    float numCrests;
    ofColor color;
};