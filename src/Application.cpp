//
//  Application.cpp
//  TMG Shape Displays
//
//  Created by Daniel Windham on 7/10/15.
//  Copyright 2015 MIT Media Lab. All rights reserved.
//

#include "Application.h"


Application::Application() {
    heightsForShapeDisplay.allocate(SHAPE_DISPLAY_SIZE_X, SHAPE_DISPLAY_SIZE_Y, OF_IMAGE_GRAYSCALE);
    heightsForShapeDisplay.set(0);
    heightsDrawingBuffer.allocate(SHAPE_DISPLAY_SIZE_X, SHAPE_DISPLAY_SIZE_Y);
};

void Application::getHeightsForShapeDisplay(ofPixels &heights) {
    heights = heightsForShapeDisplay;
};

void Application::getPinConfigsForShapeDisplay(PinConfigs configs[SHAPE_DISPLAY_SIZE_X][SHAPE_DISPLAY_SIZE_Y]) {
    PinConfigs *src = (PinConfigs *) pinConfigsForShapeDisplay;
    copy(src, src + SHAPE_DISPLAY_SIZE_2D, (PinConfigs *) configs);
};

void Application::setHeightsFromShapeDisplayRef(const ofPixels *heights) {
    heightsFromShapeDisplay = heights;
    hasHeightsFromShapeDisplay = true;
};

void Application::setPixelsFromKinectRefs(const ofPixels *colorPixels, const ofPixels *depthPixels) {
    colorPixelsFromKinect = colorPixels;
    depthPixelsFromKinect = depthPixels;
    hasPixelsFromKinect = true;
};