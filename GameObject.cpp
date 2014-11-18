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

GroundObject::GroundObject() : GameObject() {};

void GroundObject::drawObject() {
    //TO-DO: this
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glColor3f(0, 1, 0);
    int k = 0;
    glLoadName(touchNum);
    //glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 1); glVertex3f(coor.x*BLOCK_SIZE, -3, (coor.y+1)*BLOCK_SIZE);
    glTexCoord2f(0, 0); glVertex3f(coor.x*BLOCK_SIZE, -3, coor.y*BLOCK_SIZE);
    glTexCoord2f(1, 1); glVertex3f((coor.x+1)*BLOCK_SIZE, -3, (coor.y+1)*BLOCK_SIZE);
    glTexCoord2f(1, 0); glVertex3f((coor.x+1)*BLOCK_SIZE, -3, coor.y*BLOCK_SIZE);
    glEnd();
    if(isGrid) {
        glDisable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex3f(coor.x*BLOCK_SIZE, -2.9, (coor.y+1)*BLOCK_SIZE);
        glVertex3f(coor.x*BLOCK_SIZE, -2.9, coor.y*BLOCK_SIZE);
        glVertex3f((coor.x+1)*BLOCK_SIZE, -2.9, coor.y*BLOCK_SIZE);
        glVertex3f((coor.x+1)*BLOCK_SIZE, -2.9, (coor.y+1)*BLOCK_SIZE);
        glEnd();
        glEnable(GL_TEXTURE_2D);
    }
    
    glLoadName(0);
}