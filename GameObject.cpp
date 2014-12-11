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
#include "GameScene.h"
#include "DataProcessor.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

MineObject::MineObject() : mineType(0) {
    texType = 3;
}

void MineObject::drawObject() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glLoadName(touchNum);
    //glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 1); glVertex3f(coor.x*BLOCK_SIZE, -3, (coor.y+1)*BLOCK_SIZE);
    glTexCoord2f(0, 0); glVertex3f(coor.x*BLOCK_SIZE, -3, coor.y*BLOCK_SIZE);
    glTexCoord2f(1, 1); glVertex3f((coor.x+1)*BLOCK_SIZE, -3, (coor.y+1)*BLOCK_SIZE);
    glTexCoord2f(1, 0); glVertex3f((coor.x+1)*BLOCK_SIZE, -3, coor.y*BLOCK_SIZE);
    glEnd();
    if(isGrid) {
        glDisable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        glVertex3f(coor.x*BLOCK_SIZE, -2.99, (coor.y+1)*BLOCK_SIZE);
        glVertex3f(coor.x*BLOCK_SIZE, -2.99, coor.y*BLOCK_SIZE);
        glVertex3f((coor.x+1)*BLOCK_SIZE, -2.99, coor.y*BLOCK_SIZE);
        glVertex3f((coor.x+1)*BLOCK_SIZE, -2.99, (coor.y+1)*BLOCK_SIZE);
        glEnd();
        glEnable(GL_TEXTURE_2D);
    }
    glLoadName(0);
}

PickObject::PickObject() : dir(0) ,type(0), move(0) {
    texType = 4;
}

void PickObject::drawObject() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_TEXTURE_2D);
    
    coor.x = (int)pos[0]/BLOCK_SIZE;
    coor.y = (int)pos[1]/BLOCK_SIZE;
    
    if(move > 0) {
        move--;
        switch (dir) {
            case CONV1:
                pos[0] += moveDis;
                break;
            case CONV2:
                pos[1] -= moveDis;
                break;
            case CONV3:
                pos[0] -= moveDis;
                break;
            case CONV4:
                pos[1] += moveDis;
                break;
            default:
                break;
        }
    }
    
    
    glPushMatrix();
    glTranslatef( pos[0] , -3, pos[1]);
    switch (type) {
        case COAL:
            glColor3fv(coalColor);
            break;
        case COPPER:
            glColor3fv(copperColor);
            break;
        case IRON:
            glColor3fv(ironColor);
        default:
            break;
    }
    
    glLoadName(touchNum);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-0.5, 0, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    
    if(isGrid) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1, 1, 1);
        glBegin(GL_LINES);
        glVertex3f(-0.5, 0, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex3f(0.5, 0, -0.5);
        glVertex3f(0.5, 0, 0.5);
        glVertex3f(-0.5, 0, 0.5);
        glVertex3f(-0.5, 0, -0.5);
        glEnd();
    }
    glLoadName(0);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

void Conveyor::animate() {
    //move = (move+1)%5;
}

void Conveyor::drawObject() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_TEXTURE_2D);
    glLoadName(touchNum);
    
    //animate();
    move = gameScene->conveMove;
    
    glPushMatrix();
    glTranslatef( coor.x*BLOCK_SIZE , 0.01, coor.y*BLOCK_SIZE);
    
    glTranslatef(BLOCK_SIZE/2.0, 0, BLOCK_SIZE/2.0);
    glRotatef(toward*90, 0, 1, 0);
    glTranslatef(-BLOCK_SIZE/2.0, 0, -BLOCK_SIZE/2.0);
    
    //glBindTexture(GL_TEXTURE_2D, texture[2]);
    if(!isBuilding)
        glColor3f(0, 0, 0.6);
    else {
        if(canBuild)
            glColor4f(0, 1, 0, 0.6);
        else
            glColor4f(1, 0, 0, 0.6);
    }
    glBegin(GL_POLYGON);
    glVertex3f(0, -3, 0);
    glVertex3f(BLOCK_SIZE, -3, 0);
    glVertex3f(BLOCK_SIZE, -3, BLOCK_SIZE);
    glVertex3f(0, -3, BLOCK_SIZE);
    glEnd();
    
    //glutSolidCube(3);
    if(!isBuilding)
        glColor3f(1, 1, 0);
    else
        glColor4f(1, 1, 0, 0.6);
    
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f((move*0.1)*BLOCK_SIZE, -2.99, BLOCK_SIZE);
    glVertex3f((move*0.1+0.2)*BLOCK_SIZE, -2.99, BLOCK_SIZE);
    glVertex3f((move*0.1+0.1)*BLOCK_SIZE, -2.99, BLOCK_SIZE/2.0);
    glVertex3f((move*0.1+0.3)*BLOCK_SIZE, -2.99, BLOCK_SIZE/2.0);
    glVertex3f((move*0.1)*BLOCK_SIZE, -2.99, 0);
    glVertex3f((move*0.1+0.2)*BLOCK_SIZE, -2.99, 0);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f((move*0.1+0.5)*BLOCK_SIZE, -2.99, BLOCK_SIZE);
    glVertex3f( ((move*0.1+0.7)>1?1:(move*0.1+0.7))*BLOCK_SIZE, -2.99, BLOCK_SIZE);
    glVertex3f(((move*0.1+0.6)>1?1:(move*0.1+0.6))*BLOCK_SIZE, -2.99, BLOCK_SIZE/2.0);
    glVertex3f(((move*0.1+0.8)>1?1:(move*0.1+0.8))*BLOCK_SIZE, -2.99, BLOCK_SIZE/2.0);
    glVertex3f(((move*0.1+0.5)>1?1:(move*0.1+0.5))*BLOCK_SIZE, -2.99, 0);
    glVertex3f(((move*0.1+0.7)>1?1:(move*0.1+0.7))*BLOCK_SIZE, -2.99, 0);
    glEnd();
    if(move == 4) {
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0, -2.99, BLOCK_SIZE);
        glVertex3f(0.1*BLOCK_SIZE, -2.99, BLOCK_SIZE);
        glVertex3f(0, -2.99, BLOCK_SIZE/2.0);
        glVertex3f(0.2*BLOCK_SIZE, -2.99, BLOCK_SIZE/2.0);
        glVertex3f(0*BLOCK_SIZE, -2.99, 0);
        glVertex3f(0.1*BLOCK_SIZE, -2.99, 0);
        glEnd();
    }
    else if(move == 3) {
        glBegin(GL_TRIANGLES);
        glVertex3f(0, -2.99, BLOCK_SIZE);
        glVertex3f(0.1*BLOCK_SIZE, -2.99, BLOCK_SIZE/2.0);
        glVertex3f(0, -2.99, 0);
        glEnd();
    }
    if(isGrid) {
        glDisable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        glVertex3f(0, -2.99, 0);
        glVertex3f(BLOCK_SIZE, -2.99, 0);
        glVertex3f(BLOCK_SIZE, -2.99, BLOCK_SIZE);
        glVertex3f(0, -2.99, BLOCK_SIZE);
        glEnd();
        glEnable(GL_TEXTURE_2D);
    }
    glLoadName(0);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

void MinerBuilding::animate() {
    produceTime = (produceTime+1)%5;
}

void MinerBuilding::drawObject() {
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_TEXTURE_2D);
    glLoadName(touchNum);
    
    glTranslatef( coor.x*BLOCK_SIZE , -3, coor.y*BLOCK_SIZE);
    
    glTranslatef(BLOCK_SIZE, 0, BLOCK_SIZE);
    glRotatef(toward*90, 0, 1, 0);
    glRotated(-90, 0, 1, 0);
    glTranslatef(-BLOCK_SIZE, 0, -BLOCK_SIZE);
    
    
    glColor4f(1, 1, 0, 0.7);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(BLOCK_SIZE*0.4, 0.2, -0.5);
    glVertex3f(BLOCK_SIZE*0.6, 0.2, -0.5);
    glVertex3f(BLOCK_SIZE*0.4, 0.2, -1);
    glVertex3f(BLOCK_SIZE*0.6, 0.2, -1);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(BLOCK_SIZE*0.75, 0.2, -1);
    glVertex3f(BLOCK_SIZE*0.25, 0.2, -1);
    glVertex3f(BLOCK_SIZE*0.5, 0.2, -1.25);
    glEnd();
    
    if(!isBuilding)
        glColor4f(0.5, 0.5, 0.5, 1);
    else {
        if(canBuild)
            glColor4f(0, 0.5, 0, 0.5);
        else
            glColor4f(0.5, 0, 0, 0.5);
    }
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2.5, 0);
    glVertex3f(0, 0, BLOCK_SIZE*2);
    glVertex3f(0, 2.5, BLOCK_SIZE*2);
    glVertex3f(BLOCK_SIZE*2, 0, BLOCK_SIZE*2);
    glVertex3f(BLOCK_SIZE*2, 2.5, BLOCK_SIZE*2);
    glVertex3f(BLOCK_SIZE*2, 0, 0);
    glVertex3f(BLOCK_SIZE*2, 2.5, 0);
    glVertex3f(BLOCK_SIZE*0.75, 0, 0);
    glVertex3f(BLOCK_SIZE*0.75, 2.5, 0);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(BLOCK_SIZE*0.25, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(BLOCK_SIZE*0.25, 1, 0);
    glVertex3f(0, 2.5, 0);
    glVertex3f(BLOCK_SIZE*0.75, 1, 0);
    glVertex3f(BLOCK_SIZE*0.75, 2.5, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(0, 2.5, 0);
    glVertex3f(BLOCK_SIZE*2, 2.5, 0);
    glVertex3f(BLOCK_SIZE*2, 2.5, BLOCK_SIZE*2);
    glVertex3f(0, 2.5, BLOCK_SIZE*2);
    glEnd();
    
    
    
    glLoadName(0);
    
    if(isGrid) {
        glColor3f(1, 1, 1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        glVertex3f(0, 2.5, 0);
        glVertex3f(BLOCK_SIZE*2, 2.5, 0);
        glVertex3f(BLOCK_SIZE*2, 2.5, BLOCK_SIZE*2);
        glVertex3f(0, 2.5, BLOCK_SIZE*2);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 2.5, 0);
        glVertex3f(0, 0, BLOCK_SIZE*2);
        glVertex3f(0, 2.5, BLOCK_SIZE*2);
        glVertex3f(BLOCK_SIZE*2, 0, BLOCK_SIZE*2);
        glVertex3f(BLOCK_SIZE*2, 2.5, BLOCK_SIZE*2);
        glVertex3f(BLOCK_SIZE*2, 0, 0);
        glVertex3f(BLOCK_SIZE*2, 2.5, 0);
        glEnd();
    }
    
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Statue::animate() {
    
}

void Statue::drawStatue() {
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLoadName(touchNum);
    
    glTranslatef( (coor.x+1.5)*BLOCK_SIZE , 0.5, (coor.y+1.5)*BLOCK_SIZE);
    
    int level = 0;
    float levelH = 1.5;
    float rotate = 20;
    
    
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    //glutSolidSphere(10, 100, 100);
    
    for(int a=0;a!=colors.size();++a) {
        int k = a%8;
        if(k == 0) {
            level++;
            glRotatef(rotate, 0, 1, 0);
        }
        int tex = colors[a];
        glBindTexture(GL_TEXTURE_2D, tex);
        float r = 0.5;
        if(k == 0 || k == 7)r = 0.8;
        glPushMatrix();
        glTranslatef((float)k - 3.5, level * levelH, 0);
        glutSolidSphere(r, 10, 10);
        glPopMatrix();
        
        
    }
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    
    glPopMatrix();
    glPopMatrix();
}

void Statue::drawObject() {
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_TEXTURE_2D);
    glLoadName(touchNum);
    
    glTranslatef( coor.x*BLOCK_SIZE , -3, coor.y*BLOCK_SIZE);
    
    glTranslatef(BLOCK_SIZE*1.5, 0, BLOCK_SIZE*1.5);
    glRotatef(toward*90, 0, 1, 0);
    glRotated(-90, 0, 1, 0);
    glTranslatef(-BLOCK_SIZE*1.5, 0, -BLOCK_SIZE*1.5);
    
    
    glPushMatrix();
    glTranslatef(BLOCK_SIZE*1.5, 0, -1);
    glRotatef(180, 0, 1, 0);
    glTranslatef(-BLOCK_SIZE*1.5, 0, 1);
    glColor4f(1, 1, 0, 0.7);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(BLOCK_SIZE*1.4, 0.2, -0.5);
    glVertex3f(BLOCK_SIZE*1.6, 0.2, -0.5);
    glVertex3f(BLOCK_SIZE*1.4, 0.2, -1);
    glVertex3f(BLOCK_SIZE*1.6, 0.2, -1);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(BLOCK_SIZE*1.75, 0.2, -1);
    glVertex3f(BLOCK_SIZE*1.25, 0.2, -1);
    glVertex3f(BLOCK_SIZE*1.5, 0.2, -1.25);
    glEnd();
    glPopMatrix();
    
    if(!isBuilding)
        glColor4f(0.5, 0.5, 0.5, 1);
    else {
        if(canBuild)
            glColor4f(0, 0.5, 0, 0.5);
        else
            glColor4f(0.5, 0, 0, 0.5);
    }
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2.5, 0);
    glVertex3f(0, 0, BLOCK_SIZE*3);
    glVertex3f(0, 2.5, BLOCK_SIZE*3);
    glVertex3f(BLOCK_SIZE*3, 0, BLOCK_SIZE*3);
    glVertex3f(BLOCK_SIZE*3, 2.5, BLOCK_SIZE*3);
    glVertex3f(BLOCK_SIZE*3, 0, 0);
    glVertex3f(BLOCK_SIZE*3, 2.5, 0);
    glVertex3f(BLOCK_SIZE*1.75, 0, 0);
    glVertex3f(BLOCK_SIZE*1.75, 2.5, 0);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(BLOCK_SIZE*1.25, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(BLOCK_SIZE*1.25, 1, 0);
    glVertex3f(0, 2.5, 0);
    glVertex3f(BLOCK_SIZE*1.75, 1, 0);
    glVertex3f(BLOCK_SIZE*1.75, 2.5, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(0, 2.5, 0);
    glVertex3f(BLOCK_SIZE*3, 2.5, 0);
    glVertex3f(BLOCK_SIZE*3, 2.5, BLOCK_SIZE*3);
    glVertex3f(0, 2.5, BLOCK_SIZE*3);
    glEnd();
    
    
    
    glLoadName(0);
    
    if(isGrid) {
        glColor3f(1, 1, 1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        glVertex3f(0, 2.5, 0);
        glVertex3f(BLOCK_SIZE*3, 2.5, 0);
        glVertex3f(BLOCK_SIZE*3, 2.5, BLOCK_SIZE*3);
        glVertex3f(0, 2.5, BLOCK_SIZE*3);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 2.5, 0);
        glVertex3f(0, 0, BLOCK_SIZE*3);
        glVertex3f(0, 2.5, BLOCK_SIZE*3);
        glVertex3f(BLOCK_SIZE*3, 0, BLOCK_SIZE*3);
        glVertex3f(BLOCK_SIZE*3, 2.5, BLOCK_SIZE*3);
        glVertex3f(BLOCK_SIZE*3, 0, 0);
        glVertex3f(BLOCK_SIZE*3, 2.5, 0);
        glEnd();
    }
    
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
    
    if(!isBuilding)
        drawStatue();
    
}

GroundObject::GroundObject() : GameObject() {
    texType = 1;
}

void GroundObject::drawObject() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glLoadName(touchNum);
    glPushMatrix();
    //glTranslatef( coor.x*BLOCK_SIZE , -3, coor.y*BLOCK_SIZE);
    
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 1); glVertex3f(coor.x*BLOCK_SIZE, -3, (coor.y+1)*BLOCK_SIZE);
    glTexCoord2f(0, 0); glVertex3f(coor.x*BLOCK_SIZE, -3, coor.y*BLOCK_SIZE);
    glTexCoord2f(1, 1); glVertex3f((coor.x+1)*BLOCK_SIZE, -3, (coor.y+1)*BLOCK_SIZE);
    glTexCoord2f(1, 0); glVertex3f((coor.x+1)*BLOCK_SIZE, -3, coor.y*BLOCK_SIZE);
    glEnd();
    if(isGrid) {
        glDisable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        glVertex3f(coor.x*BLOCK_SIZE, -2.99, (coor.y+1)*BLOCK_SIZE);
        glVertex3f(coor.x*BLOCK_SIZE, -2.99, coor.y*BLOCK_SIZE);
        glVertex3f((coor.x+1)*BLOCK_SIZE, -2.99, coor.y*BLOCK_SIZE);
        glVertex3f((coor.x+1)*BLOCK_SIZE, -2.99, (coor.y+1)*BLOCK_SIZE);
        glEnd();
        glEnable(GL_TEXTURE_2D);
    }
    
    glPopMatrix();
    glLoadName(0);
}