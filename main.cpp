//
//  main.cpp
//  FinalProject
//
//  Created by  帅哥 on 11/16/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

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

float width,height;
float facingAngle = 90/57.3 ;
float VerAngle = 0;
float playerPos[3] = {0,0,5};
int closestName = 0;

static int hits; // Number of entries in hit buffer.
static unsigned int buffer[1024]; // Hit buffer.
static int blockNameInit = 1000;

static float oneD = 1.0/57.3;
static int blockSize = 3;
static unsigned int texture[7]; // Array of texture indices.

int grid[1000][1000];


void loadExternalTextures()
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

void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
    gluPerspective(60, 1.0, 1.0, 200);
    glMatrixMode(GL_MODELVIEW);
}

void setPointOfView()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //float x = cos(facingAngle), y = 0, z = -sin(facingAngle);
    
    gluLookAt(playerPos[0], playerPos[1], playerPos[2],
              playerPos[0] + cos(facingAngle), playerPos[1] + sin(VerAngle), playerPos[2] + -sin(facingAngle),
              0, 1, 0);
}

void drawGround() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glColor3f(0, 1, 0);
    int k = 0;
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
    }
    glLoadName(0);
}

void drawSphere() {
    
    glLoadName(2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(0, 2, -10);
    glutSolidSphere(3, 10, 10);
    glEnd();
    glLoadName(0);
}

void drawScene(void)
{
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    
    setPointOfView();
    setProjection();
    
    drawGround();
    drawSphere();
    
    glutSwapBuffers();
}

void resize(int w, int h)
{
    width = w; height = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setup() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
    
    glGenTextures(2, texture);
    loadExternalTextures();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    ///glEnable(GL_LIGHTING);
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

}

void animate(int value)
{
    glutTimerFunc(0.1, animate, 1);
    glutPostRedisplay();
}

void findClosestHit(int hits, unsigned int buffer[])//[ballAndTorusPicking.cpp]
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
}


float dist(float x1, float y1, float x2, float y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void pickFunction(int button, int state, int x, int y)  //[ballAndTorusPicking.cpp]
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
    setPointOfView();
    drawGround();
    drawSphere();
    hits = glRenderMode(GL_RENDER);//[ballAndTorusPicking.cpp]
    
    glMatrixMode(GL_PROJECTION);//[ballAndTorusPicking.cpp]
    glPopMatrix();//[ballAndTorusPicking.cpp]
    glMatrixMode(GL_MODELVIEW);//[ballAndTorusPicking.cpp]
    
    findClosestHit(hits, buffer);//[ballAndTorusPicking.cpp]
    
    glutPostRedisplay();//[ballAndTorusPicking.cpp]
}
// [ballANdTorusPicking.cpp] by Sumanta Guha

void specialKeyInput(int key, int x, int y)
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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow ("Crafter.cpp");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutTimerFunc(5, animate, 1);
    glutSpecialFunc(specialKeyInput);
    glutMouseFunc(pickFunction);
    glutMainLoop();
    
    return 0;
}
