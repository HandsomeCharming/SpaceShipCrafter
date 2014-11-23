
//  GUIs.cpp
//  FinalProject
//
//  Created by  帅哥 on 11/17/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

#include "GUIs.h"
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

void GUIs::drawGUI() {
    glDisable(GL_TEXTURE_2D);
    if(showBar) {
        bar->drawBar();
    }
    if(showInventory) {
        inventory->drawInventory();
    }
    glEnable(GL_TEXTURE_2D);
}

void Bar::drawBar() {
    //glDisable(GL_DEPTH_TEST);
    glLoadName(0);
    glColor3f(81/256.0, 53/256.0, 28/256.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(barPos[0] + 0.5*barSize[0], barPos[1] + 0.5*barSize[1], -5);
    glColor3f(91/256.0, 63/256.0, 38/256.0);
    glVertex3f(barPos[0], barPos[1], -5);
    glVertex3f(barPos[0] + barSize[0], barPos[1], -5);
    glVertex3f(barPos[0] + barSize[0], barPos[1] + barSize[1], -5);
    glVertex3f(barPos[0], barPos[1] + barSize[1], -5);
    glVertex3f(barPos[0], barPos[1], -5);
    glEnd();
    float xx = 0.25;
    float x = barPos[0] + 0.125, y = barPos[1] + 0.15;
    
    int touchNum = BAR_TOUCH_NUM;
    for(int a=0;a!=BAR_COL;++a) {
        glLoadName(touchNum);
        touchNum++;
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.6, 0.6, 0.6);
        glVertex3f(x+xx*0.7, y+xx*0.5, -4.95);
        glColor3f(0.7, 0.7, 0.7);
        glVertex3f(x, y, -4.95);
        glVertex3f(x+xx, y, -4.95);
        glVertex3f(x+xx, y+xx, -4.95);
        glVertex3f(x, y+xx, -4.95);
        glVertex3f(x, y, -4.95);
        glEnd();
        x+=xx;
    }
    glLoadName(0);
    if(selected != -1) {
        glColor3f(1, 1, 1);
        glBegin(GL_LINE_LOOP);
        x = barPos[0] + 0.125 + selected * xx, y = barPos[1] + 0.15;
        glVertex3f(x, y, -4.94);
        glVertex3f(x+xx, y, -4.94);
        glVertex3f(x+xx, y+xx, -4.94);
        glVertex3f(x, y+xx, -4.94);
        glEnd();
    }
    //glEnable(GL_DEPTH_TEST);
}

void GUIs::notSelected() {
    bar->selected = -1;
    inventory->selected = -1;
}

void Inventory::drawInventory() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    
    glPushMatrix();
    glColor3f(1, 0, 0);
    //glTranslatef(inventoryPos[0], inventoryPos[1], -2);
    glRasterPos3f(0.4, 0.7, -2);
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Inventory");
    glPopMatrix();
    
    glColor3f(81/256.0, 53/256.0, 28/256.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(inventoryPos[0] + 0.5*inventorySize[0], inventoryPos[1] + 0.5*inventorySize[1], -5);
    glColor3f(91/256.0, 63/256.0, 38/256.0);
    glVertex3f(inventoryPos[0], inventoryPos[1], -5);
    glVertex3f(inventoryPos[0] + inventorySize[0], inventoryPos[1], -5);
    glVertex3f(inventoryPos[0] + inventorySize[0], inventoryPos[1] + inventorySize[1], -5);
    glVertex3f(inventoryPos[0], inventoryPos[1] + inventorySize[1], -5);
    glVertex3f(inventoryPos[0], inventoryPos[1], -5);
    glEnd();
    float xx = inventorySize[0]/(INVEN_COL+2.0);
    
    float x = 0, y = 1.3;
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    glTranslatef(inventoryPos[0], inventoryPos[1], 0);
    int touchNum = INVEN_TOUCH_NUM;
    for(int a=0; a!=INVEN_ROW; ++a) {
        x = 0;
        y -= xx;
        for (int b=0; b!=INVEN_COL; ++b) {
            x += xx;
            glLoadName(touchNum);
            touchNum++;
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.6, 0.6, 0.6);
            glVertex3f(x+xx*0.7, y+xx*0.5, -4.95);
            glColor3f(0.7, 0.7, 0.7);
            glVertex3f(x, y, -4.95);
            glVertex3f(x+xx, y, -4.95);
            glVertex3f(x+xx, y+xx, -4.95);
            glVertex3f(x, y+xx, -4.95);
            glVertex3f(x, y, -4.95);
            glEnd();
        }
    }
    glLoadName(0);
    if(selected != -1) {
        x = (selected%9+1)*xx, y = 1.3 - xx*(selected/9+1);
        glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        glVertex3f(x, y, -4.94);
        glVertex3f(x+xx, y, -4.94);
        glVertex3f(x+xx, y+xx, -4.94);
        glVertex3f(x, y+xx, -4.94);
        glEnd();
    }
    glPopMatrix();
    glPopMatrix();
}