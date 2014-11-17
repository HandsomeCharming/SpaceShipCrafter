//
//  GameObject.cpp
//  FinalProject
//
//  Created by  帅哥 on 11/16/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

#include "GameObject.h"
#include <iostream>
#include <cmath>
#include <vector>

#include "Basic.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

GroundObject::GroundObject() : GameObject(), isGrid(0) {};

void GroundObject::drawObject() {
    
}