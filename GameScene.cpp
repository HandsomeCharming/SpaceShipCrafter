//
//  GameScene.cpp
//  FinalProject
//
//  Created by  帅哥 on 11/22/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//
#pragma once

#include "GameScene.h"
#include <iostream>
#include <cmath>
#include <vector>

//#include "Basic.h"
#include "GUIs.h"
#include "GameObject.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


void GameScene::loadExternalTextures()
{
    // Local storage for bmp image data.
    BitMapFile *image[2];
    
    // Load the textures.
    image[0] = getBMPData("Textures/grass.bmp");
    image[1] = getBMPData("Textures/sky.bmp");
    
    // Bind grass image to texture index[0].
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);
    
    // Bind sky image to texture index[1]
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);
}

void GameScene::setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
    gluPerspective(60, 1.0, 1.0, 200);
    glMatrixMode(GL_MODELVIEW);
}

void GameScene::setPointOfView()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //float x = cos(facingAngle), y = 0, z = -sin(facingAngle);
    
    gluLookAt(playerPos[0], playerPos[1], playerPos[2],
              playerPos[0] + cos(facingAngle), playerPos[1] + sin(VerAngle), playerPos[2] + -sin(facingAngle),
              0, 1, 0);
}

void GameScene::drawGround() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glColor3f(0, 1, 0);
    for(int a=0;a!=groundVec.size();++a) {
        groundVec[a]->drawObject();
    }
    /*int k = 0;
     glLoadName(1);
     blockNameInit = 1000;
     for(int a=0;a!=300;++a) {
     glBegin(GL_TRIANGLE_STRIP);
     for(int b=0;b!=300;++b) {
     blockNameInit+=(k+1)%2;
     glLoadName(blockNameInit);
     glTexCoord2f(k, 0); glVertex3f(a*blockSize-200, -3, b*blockSize-200);
     glTexCoord2f(k, 1); glVertex3f((a+1)*blockSize-200, -3, b*blockSize-200);
     k = (k+1)%2;
     }
     glEnd();
     }*/
    glLoadName(0);
}

void drawSphere() {
    glLoadName(2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(375, 2, 365);
    glutSolidSphere(3, 10, 10);
    glEnd();
    glLoadName(0);
}

void GameScene::drawScene(void)
{
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    
    guis->drawGUI();
    
    setPointOfView();
    setProjection();
    
    drawGround();
    //drawSphere();
    
    glutSwapBuffers();
}


void GameScene::setup() {
    
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
    
    glGenTextures(2, texture);
    loadExternalTextures();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    for(int a=0; a!=MAP_SIZE; ++a) {
        for(int b=0; b!=MAP_SIZE; ++b) {
            GroundObject* ground = new GroundObject();
            ground->coor.x = a;
            ground->coor.y = b;
            ground->touchNum = a*MAP_SIZE+b+BLOCK_TOUCH_NUM;
            groundVec.push_back(ground);
        }
    }
    
    guis = new GUIs();
    ///glEnable(GL_LIGHTING);
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
}

void GameScene::animate(int value)
{
}

void GameScene::passiveHit(int closestName) {
    if(closestName >= 1000) {
        if(selectedObject)
            selectedObject->isGrid = false;
        selectedObject = groundVec[closestName-1000];
        groundVec[closestName-1000]->isGrid = true;
        guis->notSelected();
    }
    else if(closestName >= 950) {
        guis->bar->selected = closestName - 950;
        selectedObject->isGrid = false;
    }
    else if(closestName >= 900) {
        guis->inventory->selected = closestName - 900;
        selectedObject->isGrid = false;
    }
}

void GameScene::clickHit(int closestName) {
    
}

int GameScene::findClosestHit(int hits, unsigned int buffer[])//[ballAndTorusPicking.cpp]
{
    unsigned int *ptr, minZ;//[ballAndTorusPicking.cpp]
    
    minZ= 0xffffffff; // 2^32 - 1//[ballAndTorusPicking.cpp]
    ptr = buffer;//[ballAndTorusPicking.cpp]
    closestName = 0;//[ballAndTorusPicking.cpp]
    for (int i = 0; i < hits; i++)//[ballAndTorusPicking.cpp]
    {
        ptr++;
        if (*ptr < minZ)
        {
            minZ = *ptr;
            ptr += 2;
            closestName = *ptr;
            ptr++;
        }
        else ptr += 3;
    }
    cout<<closestName<<endl;
    return closestName;
}


float GameScene::dist(float x1, float y1, float x2, float y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void GameScene::pickFunction(int button, int state, int x, int y)  //[ballAndTorusPicking.cpp]
{
    int viewport[4]; // Viewport data.//[ballAndTorusPicking.cpp]
    
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;//[ballAndTorusPicking.cpp]
    
    
    glGetIntegerv(GL_VIEWPORT, viewport);//[ballAndTorusPicking.cpp]
    
    glSelectBuffer(1024, buffer);//[ballAndTorusPicking.cpp]
    (void) glRenderMode(GL_SELECT);//[ballAndTorusPicking.cpp]
    glMatrixMode(GL_PROJECTION);//[ballAndTorusPicking.cpp]
    glPushMatrix();//[ballAndTorusPicking.cpp]
    
    glLoadIdentity();//[ballAndTorusPicking.cpp]
    gluPickMatrix((float)x, (float)(viewport[3] - y), 3.0, 3.0, viewport);//[ballAndTorusPicking.cpp]
    gluPerspective(60, 1.0, 1.0, 200);
    
    glMatrixMode(GL_MODELVIEW);//[ballAndTorusPicking.cpp]
    glLoadIdentity();//[ballAndTorusPicking.cpp]
    
    glInitNames();//[ballAndTorusPicking.cpp]
    glPushName(0);//[ballAndTorusPicking.cpp]
    guis->drawGUI();
    setPointOfView();
    drawGround();
    hits = glRenderMode(GL_RENDER);//[ballAndTorusPicking.cpp]
    
    glMatrixMode(GL_PROJECTION);//[ballAndTorusPicking.cpp]
    glPopMatrix();//[ballAndTorusPicking.cpp]
    glMatrixMode(GL_MODELVIEW);//[ballAndTorusPicking.cpp]
    
    clickHit( findClosestHit(hits, buffer));//[ballAndTorusPicking.cpp]
    
    glutPostRedisplay();//[ballAndTorusPicking.cpp]
}
// [ballANdTorusPicking.cpp] by Sumanta Guha


void GameScene::passiveMouse(int x, int y) {
    int viewport[4]; // Viewport data.//[ballAndTorusPicking.cpp]
    
    glGetIntegerv(GL_VIEWPORT, viewport);//[ballAndTorusPicking.cpp]
    
    glSelectBuffer(1024, buffer);//[ballAndTorusPicking.cpp]
    (void) glRenderMode(GL_SELECT);//[ballAndTorusPicking.cpp]
    glMatrixMode(GL_PROJECTION);//[ballAndTorusPicking.cpp]
    glPushMatrix();//[ballAndTorusPicking.cpp]
    
    glLoadIdentity();//[ballAndTorusPicking.cpp]
    gluPickMatrix((float)x, (float)(viewport[3] - y), 3.0, 3.0, viewport);//[ballAndTorusPicking.cpp]
    gluPerspective(60, 1.0, 1.0, 200);
    
    glMatrixMode(GL_MODELVIEW);//[ballAndTorusPicking.cpp]
    glLoadIdentity();//[ballAndTorusPicking.cpp]
    
    glInitNames();//[ballAndTorusPicking.cpp]
    glPushName(0);//[ballAndTorusPicking.cpp]
    guis->drawGUI();
    setPointOfView();
    drawGround();
    hits = glRenderMode(GL_RENDER);//[ballAndTorusPicking.cpp]
    
    glMatrixMode(GL_PROJECTION);//[ballAndTorusPicking.cpp]
    glPopMatrix();//[ballAndTorusPicking.cpp]
    glMatrixMode(GL_MODELVIEW);//[ballAndTorusPicking.cpp]
    
    passiveHit( findClosestHit(hits, buffer));//[ballAndTorusPicking.cpp]
    
    glutPostRedisplay();//[ballAndTorusPicking.cpp]
}

void GameScene::keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'e':
            guis->showInventory = !guis->showInventory;
            break;
    }
    glutPostRedisplay();
}


void GameScene::specialKeyInput(int key, int x, int y)
{
    bool isShift = glutGetModifiers()==GLUT_ACTIVE_SHIFT?1:0;
    bool isAlt = glutGetModifiers()==GLUT_ACTIVE_ALT?1:0;
    if(key == GLUT_KEY_UP) {
        if(!isShift) {
            playerPos[0] += cos(facingAngle);
            playerPos[2] += -sin(facingAngle);
        }
        else {
            if(VerAngle < oneD*90)
                VerAngle += oneD;
        }
    }
    if(key == GLUT_KEY_DOWN) {
        if(!isShift) {
            playerPos[0] -= cos(facingAngle);
            playerPos[2] -= -sin(facingAngle);
        }
        else {
            if(VerAngle > -oneD*90)
                VerAngle -= oneD;
        }
    }
    if(key == GLUT_KEY_LEFT) {facingAngle += 2/57.3;
    }
    if(key == GLUT_KEY_RIGHT) {
        facingAngle -= 2/57.3;
    }
    //glutSwapBuffers();
}