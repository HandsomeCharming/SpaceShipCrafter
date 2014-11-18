//
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
    if(showInventory) {
        glPushMatrix();
        glTranslatef(0, 0, -5);
        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex3f(0, 0, 0);
        glVertex3f(2, 0, 0);
        glVertex3f(2, 2, 0);
        glVertex3f(0, 2, 0);
        glEnd();
        glPopMatrix();
    }
    glEnable(GL_TEXTURE_2D);
}