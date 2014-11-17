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

using namespace std;

struct BitMapFile
{
    int sizeX;
    int sizeY;
    unsigned char *data;
};

BitMapFile *getBMPData(string filename);
void loadExternalTextures();

#endif /* defined(__FinalProject__Basic__) */
