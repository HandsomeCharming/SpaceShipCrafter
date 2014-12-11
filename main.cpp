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
#include "GUIs.h"
#include "GameObject.h"
#include "GameScene.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

GameScene* gameScene;

float width,height;

void drawScene(void)
{
    gameScene->drawScene();
}

void resize(int w, int h)
{
    width = w; height = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gameScene->width = w;
    gameScene->height = h;
    gameScene->setProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void animate(int value) {
    glutTimerFunc(0.1, animate, 1);
    gameScene->animate(value);
    glutPostRedisplay();
}

void pickFunction(int button, int state, int x, int y) {
    gameScene->pickFunction(button, state, x, y);
}

void passiveMouse(int x, int y) {
    gameScene->passiveMouse(x, y);
}

void keyInput(unsigned char key, int x, int y) {
    gameScene->keyInput(key, x, y);
}

void specialKeyInput(int key, int x, int y) {
    gameScene->specialKeyInput(key, x, y);
}



int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow ("Crafter.cpp");
    gameScene = new GameScene();
    gameScene->setup();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutTimerFunc(5, animate, 1);
    glutSpecialFunc(specialKeyInput);
    glutMouseFunc(pickFunction);
    glutPassiveMotionFunc(passiveMouse);
    glutKeyboardFunc(keyInput);
    
    
    glutMainLoop();
    
    return 0;
}
