//
//  GameScene.h
//  FinalProject
//
//  Created by  帅哥 on 11/22/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

#ifndef __FinalProject__GameScene__
#define __FinalProject__GameScene__

#include <stdio.h>
#include <vector>

class GameObject;
class GUIs;
class GroundObject;

class GameScene {
public:
    GameScene() {}
    
    float facingAngle = 90/57.3 ;
    float VerAngle = 0;
    float playerPos[3] = {375,0,375};
    int closestName = 0;
    //int mapSize = 250;
    
    GameObject* selectedObject;
    GUIs* guis;
    
    int grid[1000][1000];
    
    std::vector<GroundObject*> groundVec;
    
    int hits; // Number of entries in hit buffer.
    unsigned int buffer[1024]; // Hit buffer.
    //static int blockNameInit = 1000;
    
    const float oneD = 1.0/57.3;
    const int blockSize = 3;
    
    void setup();
    void loadExternalTextures();
    void setProjection();
    void setPointOfView();
    void drawGround();
    void drawScene(void);
    void animate(int value);
    void passiveHit(int closestName);
    void clickHit(int closestName);
    int findClosestHit(int hits, unsigned int buffer[]);
    float dist(float x1, float y1, float x2, float y2);
    void pickFunction(int button, int state, int x, int y);
    void passiveMouse(int x, int y);
    void keyInput(unsigned char key, int x, int y);
    void specialKeyInput(int key, int x, int y);
};

#endif /* defined(__FinalProject__GameScene__) */
