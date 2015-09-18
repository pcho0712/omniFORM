//
//  MaterialsRegionsApp.cpp
//  TMG Shape Displays
//
//  Created by Daniel Windham on 9/17/15.
//  Copyright 2015 MIT Media Lab. All rights reserved.
//

#include "MaterialsRegionsApp.h"


MaterialsRegionsApp::MaterialsRegionsApp() {
    // initialize touch detector
    touchDetector = new TouchDetector();
    touchDetector->setDepressionSignificanceThreshold(30);
    touchDetector->setStabilityTimeThreshold(0.3);
    
    regionsMap.allocate(SHAPE_DISPLAY_SIZE_X, SHAPE_DISPLAY_SIZE_Y, 1);
    nativeHeights.allocate(SHAPE_DISPLAY_SIZE_X, SHAPE_DISPLAY_SIZE_Y, 1);
    graphics.allocate(SHAPE_DISPLAY_SIZE_X, SHAPE_DISPLAY_SIZE_Y, OF_IMAGE_COLOR);
    
    loadInputMaps("ramps");
    
    setupMaterialRegions();
}

void MaterialsRegionsApp::loadInputMaps(string schemaName) {
    string path = "materialsRegionsMaps/" + schemaName;
    
    ofImage materialsRegionsMap;
    materialsRegionsMap.allocate(SHAPE_DISPLAY_SIZE_X, SHAPE_DISPLAY_SIZE_Y, OF_IMAGE_GRAYSCALE);
    materialsRegionsMap.loadImage(path + ".materials.png");
    materialsRegionsMap.setImageType(OF_IMAGE_GRAYSCALE);
    
    ofImage heightsMap;
    heightsMap.allocate(SHAPE_DISPLAY_SIZE_X, SHAPE_DISPLAY_SIZE_Y, OF_IMAGE_GRAYSCALE);
    heightsMap.loadImage(path + ".heights.png");
    heightsMap.setImageType(OF_IMAGE_GRAYSCALE);
    
    graphics.loadImage(path + ".graphics.png");
    graphics.setImageType(OF_IMAGE_COLOR);
    
    for (int x = 0; x < SHAPE_DISPLAY_SIZE_X; x++) {
        for (int y = 0; y < SHAPE_DISPLAY_SIZE_Y; y++) {
            int xy = regionsMap.getPixelIndex(x, y);
            regionsMap[xy] = materialsRegionsMap.getColor(x, y)[0];
            nativeHeights[xy] = heightsMap.getColor(x, y)[0];
        }
    }
}

void MaterialsRegionsApp::setupMaterialRegions() {
    ofPixels regionMap;
    regionMap.allocate(SHAPE_DISPLAY_SIZE_X, SHAPE_DISPLAY_SIZE_Y, 1);
    for (int i = 0; i < 3; i++) {
        regionMap.set(0);
        for (int x = 0; x < SHAPE_DISPLAY_SIZE_X; x++) {
            for (int y = 0; y < SHAPE_DISPLAY_SIZE_Y; y++) {
                int xy = regionsMap.getPixelIndex(x, y);
                if (regionsMap[xy] == i) {
                    regionMap[xy] = 255;
                }
            }
        }
        MaterialRegion *materialRegion;
        if (i == 0) {
            materialRegion = new DisconnectedMaterial(regionMap);
        } else if (i == 1) {
            materialRegion = new RigidMaterial(regionMap);
        } else if (i == 2) {
            materialRegion = new StretchyMaterial(regionMap);
        }
        materialRegion->setNativeHeights(nativeHeights);
        materialRegions.push_back(materialRegion);
    }
}

void MaterialsRegionsApp::update(float dt) {
    touchDetector->update(heightsForShapeDisplay, *heightsFromShapeDisplay);
    
    for (vector<MaterialRegion *>::iterator iter = materialRegions.begin(); iter < materialRegions.end(); iter++) {
        (*iter)->update(touchDetector->significantDepressionAmidstStabilityPixels());
        
        // TODO - fix this! this line is crazy fragile, it relies on the
        // material region only setting values for pixels in its region
        (*iter)->getCurrentHeights(heightsForShapeDisplay);
    }
}

void MaterialsRegionsApp::drawDebugGui(int x, int y) {
    ofImage(touchDetector->depressionPixels()).draw(x, y, 300, 300);
    ofImage(touchDetector->significantDepressionPixels()).draw(x + 302, y, 300, 300);
    ofImage(touchDetector->significantDepressionAmidstStabilityPixels()).draw(x + 604, y, 300, 300);
}

void MaterialsRegionsApp::drawGraphicsForShapeDisplay(int x, int y, int width, int height) {
    ofImage(heightsForShapeDisplay).draw(x, y, width, height);
}

string MaterialsRegionsApp::appInstructionsText() {
    string instructions = (string) "" +
        "Waves propagate from the display center.\n" +
        "\n" +
        "You can adjust the waves' frequency and wavelength using the\n" +
        "'a', 's', 'd', and 'f' keys.\n" +
        "";

    return instructions;
}

void MaterialsRegionsApp::keyPressed(int key) {
    if (key == 'a') {
    }
}