//
//  MacroScope.h
//  TMG Shape Displays
//
//  Created by XX+DD on 10/4/15.
//  Copyright 2015 MIT Media Lab. All rights reserved.
//

#pragma once

#include "Application.h"
#include "TouchDetector.h"


// This code is meant as an easy-to-understand example of an Application. Feel
// free to copy it as a way to get started. Please don't add to or change this
// file, though - keep it a simple example for new people meeting the codebase.

class MacroScopeApp : public Application {
public:
    MacroScopeApp();
    
    void update(float dt);
    void drawGraphicsForShapeDisplay(int x, int y, int width, int height);
    string appInstructionsText();
    void keyPressed(int key);
    
    string getName() {return "MacroScope";};
    
    void drawDebugGui(int x, int y);
    
private:
    void updateHeights();
    
    TouchDetector *touchDetector;
    
    float normalizedPhase = 0;
    float frequency = 0.5;
    float numCrests = 4;
    ofColor color;
};