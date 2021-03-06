//
//  ObjectDetector.h
//  TMG Shape Displays
//
//  Created by Daniel Windham on 8/04/15.
//  Copyright 2015 MIT Media Lab. All rights reserved.
//

#pragma once

#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "constants.h"
#include "nuiComputerVision.h"
#include "Hand.h"


const int DEFAULT_NEAR_THRESHOLD = 230;
const int DEFAULT_FAR_THRESHOLD = 70;

class ObjectDetector {
public:
    ObjectDetector(int nearThreshold = DEFAULT_NEAR_THRESHOLD, int farThreshold = DEFAULT_FAR_THRESHOLD);
    ObjectDetector(int roiX, int roiY, int roiWidth, int roiHeight, int nearThreshold = DEFAULT_NEAR_THRESHOLD, int farThreshold = DEFAULT_FAR_THRESHOLD);

    void update(const ofPixels &colorPixels, const ofPixels &depthPixels);

    void setDepthThresholds(int near, int far);
    void thresholdImage(ofxCvGrayscaleImage &src, ofxCvGrayscaleImage &dst, int near=-1, int far=-1);

    void findHands(vector<Hand> &hands);

    // get images as pixels
    const ofPixels &colorPixels();
    const ofPixels &depthPixels();
    const ofPixels &depthThreshedPixels();
    const ofPixels &depthThreshedDiffPixels();

    // draw various images given coordinates and size
    void drawColorImage(int x, int y, int width, int height);
    void drawDepthImage(int x, int y, int width, int height);
    void drawDepthThreshedImage(int x, int y, int width, int height);
    void drawDepthThreshedDiff(int x, int y, int width, int height);
    
    bool useMask = false;

private:
    void setup();

    void updateImages(const ofPixels &colorPixels, const ofPixels &depthPixels);
    
    void loadAlphaMask();
    void maskInputDepthImage();
    void blurImage(ofxCvImage &img);
    
    ContourFinder handContourFinder;

    ofxCvColorImage inputColorImg;
    ofxCvColorImage colorImgRaw;
    ofxCvColorImage colorImgBlurred;
    ofxCvGrayscaleImage inputDepthImg;
    ofxCvGrayscaleImage depthImgRaw;
    ofxCvGrayscaleImage depthImgBlurred;

    ofxCvGrayscaleImage imageMask;
    ofxCvGrayscaleImage nearThresholdHelper;
    ofxCvGrayscaleImage farThresholdHelper;
    ofxCvGrayscaleImage depthThreshed;
    ofxCvGrayscaleImage lastDepthThreshed;
    ofxCvGrayscaleImage depthThreshedDiff;

    const int inputImageWidth = KINECT_X;
    const int inputImageHeight = KINECT_Y;
    const int roiX;
    const int roiY;
    const int imageWidth;
    const int imageHeight;

    int nearThreshold; // the near threshold, closest possible value is 255, farthest possible value 0
    int farThreshold; // the far threshold, closest possible value is 255, farthest possible value 0
};