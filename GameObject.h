//
//  GameObject.h
//  FinalProject
//
//  Created by  帅哥 on 11/16/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

#ifndef __FinalProject__GameObject__
#define __FinalProject__GameObject__

#include <stdio.h>
#include "Basic.h"
#include <vector>

class GameScene;

class GameObject {
public:
    GameObject():isSelected(false), isGrid(0){
        coor.setCoor(0, 0);
    };
    bool isSelected;
    bool isGrid;
    int touchNum;
    int texType;
    Coordinate coor;
    virtual void drawObject() = 0;
};

class PickObject : public GameObject {
public:
    PickObject();
    int type;
    int dir;
    int move;
    const float ironColor[3] = {161.0/256.0, 151.0/256.0, 138.0/256.0};
    const float coalColor[3] = {0,0,0};
    const float copperColor[3] = {229.0/256.0, 138.0/256.0, 20.0/256.0};
    const float moveDis = BLOCK_SIZE/8.0;
    float pos[2];
    void drawObject();
    
};

class GroundObject : public GameObject{
public:
    GroundObject();
    void drawObject();
};

class MineObject : public GameObject {
public:
    MineObject();
    MineObject(int mType) : mineType(mType), GameObject(){
        
    }
    
    int mineType;
    void drawObject();
};

class BuildingObject : public GameObject {
public:
    BuildingObject() : toward(0),isBuilding(0), buildingType(0), GameObject() {
    }
    int buildingType;
    bool isBuilding;
    int produceTime;
    int toward;     //facing angle
    int size;
    bool canBuild;
    virtual bool checkBuild(std::vector<int> gridStatus) = 0;
    virtual void drawObject() = 0;
    virtual void animate() = 0;
};

class Statue : public BuildingObject {
public:
    Statue() : BuildingObject() {
        buildingType = Stat;
        size = 3;
        ex = 0;
        ey = 0;
    }
    bool checkBuild(std::vector<int> gridStatus){
        for(int a=0;a!=gridStatus.size();++a) {
            if (gridStatus[a] != GRASS ) {
                return false;
            }
        }
        return true;
    }
    int ex;
    int ey;
    std::vector<int> colors;
    void animate();
    void drawObject();
    void drawStatue();
};

class Conveyor : public BuildingObject {
public:
    Conveyor() : move(0), BuildingObject() {
        buildingType = Conve;
        size = 1;
    }
    Conveyor(GameScene* gScene) : move(0), BuildingObject() {
        buildingType = Conve;
        size = 1;
        gameScene = gScene;
    }
    GameScene* gameScene;
    int move;
    bool checkBuild(std::vector<int> gridStatus) {
        if(gridStatus[0] == GRASS)
            return true;
        return false;
    }
    void animate();
    void drawObject();
};

class MinerBuilding : public BuildingObject {
public:
    MinerBuilding() : minerType(0), BuildingObject(){
        setup();
    };
    MinerBuilding(int mType) : minerType(mType), BuildingObject(){
        setup();
    }
    void setup(){
        buildingType = CoalMine;
        produceTime = 0;
        size = 2;
    }
    int minerType;
    void drawObject();
    bool checkBuild(std::vector<int> gridStatus){
        for(int a=0;a!=gridStatus.size();++a) {
            if (gridStatus[a] < COAL ) {
                return false;
            }
        }
        minerType = gridStatus[0];
        return true;
    }
    void animate();
};


#endif /* defined(__FinalProject__GameObject__) */
