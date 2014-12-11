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
#include <string>
#include "Basic.h"

class GameObject;
class GUIs;
class GroundObject;
class MineObject;
class PickObject;
class BuildingObject;
class Conveyor;
class DataProcessor;

class GameScene {
public:
    GameScene() : buildingObject(NULL) {}
    
    float facingAngle = 90/57.3 ;
    float VerAngle = 0;
    float playerPos[3] = {375,0,375};
    int closestName = 0;
    //int mapSize = 250;
    
    GameObject* selectedObject;
    BuildingObject* buildingObject;
    GUIs* guis;
    
    int grid[MAP_SIZE][MAP_SIZE];
    /*
     1: grass
     2: convayor
     3: coal
     
     */
    bool occupied[MAP_SIZE][MAP_SIZE];
    
    std::vector<GroundObject*> groundVec;
    std::vector<MineObject*> mineVec;
    std::vector<GameObject*> gameVec;
    std::vector<PickObject*> pickVec;
    std::vector<BuildingObject*> buildingVec;
    std::vector<Conveyor*> conVec;
    DataProcessor* dataProcessor;
    
    int hits; // Number of entries in hit buffer.
    unsigned int buffer[1024]; // Hit buffer.
    //static int blockNameInit = 1000;
    
    const float oneD = 1.0/57.3;
    const int blockSize = 3;
    
    
    int updateTime;
    int mouseX;
    int mouseY;
    int conveMove;
    
    int usingTexture;
    
    float width;
    float height;
    
    const float moveDis = 0.3;
    
    int selected;
    bool isSelecting;
    
    bool pickTouchNum[300];
    
    void setup();
    void loadExternalTextures();
    void setProjection();
    void setPointOfView();
    void movePickObject();
    void generateNewObjects();
    void addStatue();
    void drawGround();
    void drawMines();
    void drawGameObject();
    void drawBuilding();
    void drawName();
    void drawScene(void);
    void drawMouseItem();
    void drawPickObject();
    void drawIsBuilding();
    void drawConveyor();
    void drawSky();
    void animate(int value);
    void passiveHit(int closestName);
    void clickHit(int closestName);
    void rightClickHit(int closestName);
    int findClosestHit(int hits, unsigned int buffer[]);
    float dist(float x1, float y1, float x2, float y2);
    void pickFunction(int button, int state, int x, int y);
    void passiveMouse(int x, int y);
    void keyInput(unsigned char key, int x, int y);
    void specialKeyInput(int key, int x, int y);
    char* getName();
    bool checkOccupied(int x, int y, int count);
};

#endif /* defined(__FinalProject__GameScene__) */
