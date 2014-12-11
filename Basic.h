//
//  Basic.h
//  FinalProject
//
//  Created by  帅哥 on 11/16/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

#ifndef __FinalProject__Basic__
#define __FinalProject__Basic__

#include <stdio.h>
#include <string>
#include <cmath>

#define MAP_SIZE 250
#define BLOCK_SIZE 3

#define BLOCK_TOUCH_NUM 1000
#define INVEN_TOUCH_NUM 900
#define BAR_TOUCH_NUM 950
#define PICK_TOUCH_NUM 63510
#define BUILDING_TOUCH_NUM 10

#define GRASS 1
#define CONV1 2
#define CONV2 3
#define CONV3 4
#define CONV4 5
#define COAL 6
#define COPPER 7
#define IRON 8
#define ENTRY 9

const float PI = std::acos(-1);

enum GridStatus {
    grass = 1,
    convayor1,
    convayor2,
    convayor3,
    convayor4,
    coal,
    
};

enum ItemType {
    CoalMine = 0,
    Conve,
    Stat
};

enum PickType {
    Coal = 0,
    Copper,
    Iron
};

static unsigned int texture[10]; // Array of texture indices.


using namespace std;

struct BitMapFile
{
    int sizeX;
    int sizeY;
    unsigned char *data;
};

struct Coordinate {
    int x;
    int y;
    void setCoor(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

BitMapFile *getBMPData(string filename);

void writeBitmapString(void *font, char *string);

#endif /* defined(__FinalProject__Basic__) */
