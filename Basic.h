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

#define MAP_SIZE 250
#define BLOCK_SIZE 3

#define BLOCK_TOUCH_NUM 1000

static unsigned int texture[7]; // Array of texture indices.

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
};

BitMapFile *getBMPData(string filename);

#endif /* defined(__FinalProject__Basic__) */
