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



class GameObject {
public:
    GameObject():isSelected(false), isGrid(0){};
    bool isSelected;
    bool isGrid;
    int touchNum;
    virtual void drawObject() = 0;
};

class GroundObject : public GameObject{
public:
    GroundObject();
    
    Coordinate coor;
    void drawObject();
};

#endif /* defined(__FinalProject__GameObject__) */
