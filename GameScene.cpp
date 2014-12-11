//
//  GameScene.cpp
//  FinalProject
//
//  Created by  Handa Zhang on 11/22/14.
//  Copyright (c) 2014 Handa Zhang. All rights reserved.
//
#pragma once

#include "GameScene.h"
#include <iostream>
#include <cmath>
#include <vector>

//#include "Basic.h"
#include "GUIs.h"
#include "GameObject.h"
#include "DataProcessor.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


void GameScene::loadExternalTextures()
{
    // Local storage for bmp image data.
    BitMapFile *image[8];
    
    // Load the textures.
    image[0] = getBMPData("Textures/grass.bmp");
    image[1] = getBMPData("Textures/sky.bmp");
    image[2] = getBMPData("Textures/coal.bmp");
    image[3] = getBMPData("Textures/copper.bmp");
    image[4] = getBMPData("Textures/iron.bmp");
    image[5] = getBMPData("Textures/coalSphere.bmp");
    image[6] = getBMPData("Textures/copperSphere.bmp");
    image[7] = getBMPData("Textures/ironSphere.bmp");
    
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
    
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[2]->sizeX, image[2]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[2]->data);
    
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[3]->sizeX, image[3]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[3]->data);
    
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[4]->sizeX, image[4]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[4]->data);
    
    for(int a=5;a<=7;++a) {
        glBindTexture(GL_TEXTURE_2D, texture[a]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[a]->sizeX, image[4]->sizeY, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, image[a]->data);
    }
}

void GameScene::setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
    gluPerspective(60, 1.0, 1.0, 100);
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

void GameScene::drawMines() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glColor3f(0, 1, 0);
    for(int a=0;a!=mineVec.size();++a) {
        mineVec[a]->drawObject();
    }
    glLoadName(0);

}

void GameScene::drawGameObject() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glColor3f(0, 1, 0);
    for(int a=0;a!=gameVec.size();++a) {
        /*if(usingTexture != gameVec[a]->texType) {
            int texType = gameVec[a]->texType;
            usingTexture = texType;
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindTexture(GL_TEXTURE_2D, texType);
            //cout<<a<<' '<<texType<<endl;
        }*/
        if( abs(gameVec[a]->coor.x - playerPos[0]/BLOCK_SIZE) > 30 && abs(gameVec[a]->coor.y - playerPos[2]/BLOCK_SIZE) > 30)continue;
        if(!isSelecting)
            glBindTexture(GL_TEXTURE_2D, gameVec[a]->texType);
        gameVec[a]->drawObject();
    }
    glDisable(GL_CULL_FACE);
    glLoadName(0);

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

void GameScene::drawSky() {
    glLoadName(0);
    glPushMatrix();
    glTranslatef( playerPos[0], -3, playerPos[2]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    float t = 0;
    float r = 50, rr = 50 * cos(PI/50);
    float y = 0;
    float j = 0, k = 0;
    for(int a=0;a<=50;++a) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int b=0; b<=50; ++b) {
            glTexCoord2f(j, k); glVertex3f(r * cos(t), y, r * sin(t));
            glTexCoord2f(j, k+0.02); glVertex3f(rr * cos(t), y + 1, rr*sin(t));
            t += PI/25;
            j += 0.02;
        }
        j = 0;
        k += 0.02;
        glEnd();
        t = 0;
        y++;
        r = rr;
        rr = 50 * cos( (a+1)*PI/50);
    }
    glPopMatrix();
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

void GameScene::drawPickObject() {
    for(int a=0;a!=pickVec.size();++a) {
        pickVec[a]->drawObject();
    }
}

void GameScene::drawIsBuilding() {
     if(buildingObject)buildingObject->drawObject();
}

void GameScene::drawBuilding() {
    for(int a=0;a!=buildingVec.size();++a) {
        buildingVec[a]->drawObject();
    }
}

void GameScene::drawConveyor() {
    for(int a=0;a!=conVec.size();++a) {
        conVec[a]->drawObject();
    }
}

void GameScene::drawScene(void)
{
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    
    guis->drawGUI();
    drawName();
    drawMouseItem();
    
    setPointOfView();
    setProjection();
    
    drawSky();
    drawGround();
    drawMines();
    drawGameObject();
    drawPickObject();
    drawBuilding();
    drawConveyor();
    drawIsBuilding();
    //drawSphere();
    
    glutSwapBuffers();
}


void GameScene::setup() {
    
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
    
    glGenTextures(8, texture);
    loadExternalTextures();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    usingTexture = 0;
    isSelecting = false;
    updateTime = 0;
    conveMove = 0;
    
    memset(pickTouchNum, 0, sizeof(pickTouchNum));
    memset(occupied, 0, sizeof(occupied));
    for(int a=0;a!=MAP_SIZE;++a) {
        for (int b=0;b!=MAP_SIZE; ++b) {
            grid[a][b] = 1;
        }
    }
    grid[128][120] = COAL;
    grid[127][121] = COAL;
    grid[127][120] = COAL;
    grid[128][121] = COAL;
    
    grid[125][120] = COPPER;
    grid[124][121] = COPPER;
    grid[124][120] = COPPER;
    grid[125][121] = COPPER;
    
    grid[121][120] = IRON;
    grid[122][121] = IRON;
    grid[122][120] = IRON;
    grid[121][121] = IRON;
    
//    grid[126][128] = CONV1;
//    Conveyor* conv = new Conveyor(this);
//    conv->coor.setCoor(126, 128);
//    conv->touchNum = 126* MAP_SIZE + 128 + BLOCK_TOUCH_NUM;
//    conVec.push_back(conv);
//    
//    PickObject* pick = new PickObject();
//    pick->coor.x = 124;
//    pick->coor.y = 120;
//    pick->pos[0] = 124.5 * BLOCK_SIZE;
//    pick->pos[1] = 120.5 * BLOCK_SIZE;
//    pickVec.push_back(pick);
//    MinerBuilding* miner = new MinerBuilding();
//    miner->coor.setCoor(127, 127);
//    miner->touchNum = BUILDING_TOUCH_NUM;
//    buildingVec.push_back(miner);
//    Statue* statue = new Statue();
//    statue->coor.setCoor(120, 110);
//    statue->touchNum = BUILDING_TOUCH_NUM + 10;
//    buildingVec.push_back(statue);
    
    for(int a=0; a!=MAP_SIZE; ++a) {
        for(int b=0; b!=MAP_SIZE; ++b) {
            GameObject* game;
            if(grid[a][b] == GRASS) {
                game = new GroundObject();
                //groundVec.push_back((GroundObject*)game);
            }
            else if(grid[a][b] >= COAL) {
                game = new MineObject(grid[a][b]);
                game->texType = texture[grid[a][b] - 4];
                if(a == 125 && b == 126) {
                    int k = game->texType;
                }
                //mineVec.push_back((MineObject*)game);
            }
            else game = new GroundObject();
            game->coor.x = a;
            game->coor.y = b;
            game->touchNum = a*MAP_SIZE+b+BLOCK_TOUCH_NUM;
            gameVec.push_back(game);
        }
    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    
    dataProcessor = new DataProcessor();
    Item* item = new Item();
    item->count = 1;
    item->pos = 2;
    item->type = ItemType::CoalMine;
    item->state = 0;
    Item* con = new Item();
    con->count = 1;
    con->pos = 1;
    con->type = ItemType::Conve;
    con->state = 0;
    Item* sta = new Item();
    sta->count = 1;
    sta->pos = 0;
    sta->type = ItemType::Stat;
    sta->state = 0;
    guis = new GUIs();
    guis->bar->dataProcessor = dataProcessor;
    guis->inventory->dataProcessor = dataProcessor;
    //dataProcessor->pickItem(item);
    dataProcessor->barItems->push_back(item);
    dataProcessor->barItems->push_back(con);
    dataProcessor->barItems->push_back(sta);
    ///glEnable(GL_LIGHTING);
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
}

void GameScene::drawMouseItem() {
    Item* item = dataProcessor->mouseItem;
    if(item == NULL)return;
    glPushMatrix();
    //glTranslatef(mouseX, mouseY, -5);
    
    float tscale = 4.0;
    
    //cout<<(mouseX-width/2)/width<<' '<<(height/2 - mouseY)/height<<endl;
    glTranslatef( (mouseX-width/2)/width * tscale, (height/2 - mouseY)/height * tscale, -3.5);
    
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, -0.1, 0);
    glVertex3f(0.1, -0.1, 0);
    glVertex3f(0.1, 0.1, 0);
    glVertex3f(-0.1, 0.1, 0);
    glEnd();
    
    
    glPopMatrix();
}

void GameScene::animate(int value)
{
    updateTime = (updateTime+1)%10;
    conveMove = (conveMove+1)%5;
    movePickObject();
    for(int a=0; a!=conVec.size();++a) {
        conVec[a]->animate();
    }
    if(updateTime == 0) {
        for(int a=0; a!=buildingVec.size();++a) {
            buildingVec[a]->animate();
        }
        addStatue();
        
        generateNewObjects();
    }
}

bool GameScene::checkOccupied(int x, int y, int count) {
    for(int a=0;a!=count;++a) {
        for(int b=0;b!=count;++b) {
            if(occupied[x+a][y+b])
                return true;
        }
    }
    return false;
}

void GameScene::passiveHit(int closestName) {
    if (dataProcessor->mouseItem) {
        drawMouseItem();
    }
    selected = closestName;
    if(selectedObject)
        selectedObject->isGrid = false;
    if(closestName >= PICK_TOUCH_NUM) {
        int a=0;
        for(;a!=pickVec.size();++a)
            if(pickVec[a]->touchNum == selected)break;
        pickVec[a]->isGrid = true;
        selectedObject = pickVec[a];
        guis->notSelected();
    }
    else if(closestName >= BLOCK_TOUCH_NUM) {
        int x = (closestName-1000)/MAP_SIZE, y = (closestName-1000)%MAP_SIZE;
        selectedObject = gameVec[closestName-1000];
        gameVec[closestName-1000]->isGrid = true;
        guis->notSelected();
        if(buildingObject) {
            buildingObject->coor.setCoor(x, y);
            vector<int> vec;
            bool occu = false;
            if(buildingObject->buildingType == CoalMine) {
                occu = checkOccupied(x, y, 2);
                vec.push_back(grid[x][y]);
                vec.push_back(grid[x+1][y]);
                vec.push_back(grid[x][y+1]);
                vec.push_back(grid[x+1][y+1]);
            }
            else if(buildingObject->buildingType == Conve) {
                occu = checkOccupied(x, y, 1);
                vec.push_back(grid[x][y]);
            }
            else {
                occu = checkOccupied(x, y, 3);
                for(int a=0;a!=3;++a) {
                    for(int b=0;b!=3;++b)
                        vec.push_back(grid[x+a][y+b]);
                }
            }
            if(!occu)
                buildingObject->canBuild = buildingObject->checkBuild(vec);
            else
                buildingObject->canBuild = false;
        }
    }
    else if(closestName >= BAR_TOUCH_NUM) {
        guis->bar->selected = closestName - 950;
    }
    else if(closestName >= INVEN_TOUCH_NUM) {
        guis->inventory->selected = closestName - 900;
    }
    else if(closestName >= BUILDING_TOUCH_NUM) {
        int a;
        for(a=0;a!=buildingVec.size();++a) {
            if(buildingVec[a]->touchNum == closestName)break;
        }
        buildingVec[a]->isGrid = true;
        selectedObject = buildingVec[a];
    }
}

void GameScene::movePickObject() {
    for(int a=0;a!=pickVec.size();++a) {
        PickObject* pick = pickVec[a];
        int dir = grid[pick->coor.x][pick->coor.y];
        if(pick->move == 0 && (dir < CONV1 || dir > CONV4)) {
            pick->dir = 0;
        }
        else {
            if(pick->move > 0)return;
            int x = pick->coor.x, y = pick->coor.y;
            switch (dir) {
                case CONV1:
                    x++;
                    break;
                case CONV2:
                    y--;
                    break;
                case CONV3:
                    x--;
                    break;
                case CONV4:
                    y++;
                    break;
                default:
                    break;
            }
            if(!occupied[x][y]) {
                occupied[pick->coor.x][pick->coor.y] = false;
                occupied[x][y] = true;
                pick->dir = grid[pick->coor.x][pick->coor.y];
                pick->move = 8;
            }
        }
    }
}

void GameScene::generateNewObjects() {
    for(int a=0;a!=buildingVec.size();++a) {
        if(buildingVec[a]->produceTime == 0) {
            if(buildingVec[a]->buildingType == CoalMine) {
                MinerBuilding* mine = (MinerBuilding*)buildingVec[a];
                int x = mine->coor.x, y = mine->coor.y;
                int fx = x, fy = y;
                int toward = mine->toward;
                switch (toward) {
                    case 0:
                        x++;
                        fx = x+1;
                        fy = y;
                        break;
                    case 1:
                        fy = y-1;
                        break;
                    case 2:
                        y++;
                        fx = x-1;
                        fy = y;
                        break;
                    case 3:
                        y++;
                        x++;
                        fx = x;
                        fy = y+1;
                        break;
                    default:
                        break;
                }
                if(!occupied[fx][fy]) {
                    PickObject* pick = new PickObject();
                    pick->type = mine->minerType;
                    int k = 0;
                    for(;k!=300;++k)
                        if(!pickTouchNum[k])break;
                    pick->touchNum = k + PICK_TOUCH_NUM;
                    pickTouchNum[k] = true;
                    pick->coor.setCoor(x, y);
                    pick->pos[0] = (x+0.5)*BLOCK_SIZE;
                    pick->pos[1] = (y+0.5)*BLOCK_SIZE;
                    pick->dir = toward + CONV1;
                    pick->move = 8;
                    pickVec.push_back(pick);
                    occupied[fx][fy] = true;
                }
            }
        }
    }
}

void GameScene::addStatue() {
    for(int a=0;a!=buildingVec.size();++a) {
        if(buildingVec[a]->buildingType == Stat) {
            Statue* sta = (Statue*) buildingVec[a];
            Coordinate coor = sta->coor;
            int toword = sta->toward;
            int x = coor.x, y = coor.y;
            vector<PickObject*>::iterator i;
            for(i = pickVec.begin(); i!=pickVec.end(); ++i) {
                if( (*i)->coor.x == sta->ex && (*i)->coor.y == sta->ey )
                    break;
            }
            if( i == pickVec.end())continue;
            PickObject* p = *i;
            sta->colors.push_back(p->type);
            pickVec.erase(i);
            delete p;
            occupied[sta->ex][sta->ey] = false;
        }
    }
}

void GameScene::clickHit(int closestName) {
    selected = closestName;
    cout<<closestName/MAP_SIZE<<' '<<closestName%MAP_SIZE<<endl;
    if(closestName < 900)return;
    if(closestName < 950) {
        vector<Item*>* invenItems = dataProcessor->getInvenItems();
        if(dataProcessor->mouseItem != NULL) {
            Item* item = dataProcessor->mouseItem;
            item->pos = closestName - INVEN_TOUCH_NUM;
            invenItems->push_back(item);
            dataProcessor->mouseItem = NULL;
        }
        else {
            vector<Item*>::iterator i = invenItems->begin();
            for(; i != invenItems->end() ; ++i) {
                if((*i)->pos == closestName - INVEN_TOUCH_NUM) {
                    break;
                }
            }
            if(i != invenItems->end()) {
                Item* item = *i;
                dataProcessor->mouseItem = item;
                invenItems->erase(i);
            }
        }
    }
    else if(closestName < 1000) {
        vector<Item*>* barItems = dataProcessor->getBarItems();
        if(dataProcessor->mouseItem != NULL) {
            Item* item = dataProcessor->mouseItem;
            item->pos = closestName - BAR_TOUCH_NUM;
            barItems->push_back(item);
            dataProcessor->mouseItem = NULL;
        }
        else {
            vector<Item*>::iterator i = barItems->begin();
            for(; i != barItems->end() ; ++i) {
                if((*i)->pos == closestName - BAR_TOUCH_NUM) {
                    break;
                }
            }
            if(i != barItems->end()) {
                Item* item = *i;
                dataProcessor->mouseItem = item;
                barItems->erase(i);
            }
        }
    }
    else if(closestName < PICK_TOUCH_NUM) {
        if(buildingObject) {
            if(buildingObject->canBuild) {
                Coordinate coor = buildingObject->coor;
                buildingObject->touchNum = BUILDING_TOUCH_NUM;
                buildingObject->isBuilding = false;
                if(buildingObject->buildingType != Conve) {
                    for(int a=0;a<buildingObject->size;++a) {
                        for(int bb=0;bb<buildingObject->size;++bb) {
                            occupied[coor.x+a][coor.y+bb] = true;
                        }
                    }
                    if(buildingObject->buildingType == Stat) {
                        int toword = buildingObject->toward;
                        int x = coor.x, y = coor.y;
                        switch (toword) {
                            case 0:
                                x += 2;
                                y += 1;
                                break;
                            case 1:
                                x++;
                                break;
                            case 2:
                                y++;
                                break;
                            case 3:
                                x++;
                                y += 2;
                                break;
                            default:
                                break;
                        }
                        Statue* sta = (Statue*) buildingObject;
                        sta->ex = x;
                        sta->ey = y;
                        occupied[x][y] = false;
                        grid[x][y] = ENTRY;
                    }
                    buildingVec.push_back(buildingObject);
                    buildingObject->touchNum = BUILDING_TOUCH_NUM + buildingVec.size();
                    buildingObject->isBuilding = false;
                    buildingObject = NULL;
                }
                else {
                    Conveyor* conve = (Conveyor*)buildingObject;
                    
                    conVec.push_back(conve);
                    grid[coor.x][coor.y] = conve->toward + CONV1;
                    buildingObject = new Conveyor(this);
                    buildingObject->isBuilding = true;
                }
                
            }
            else {
                delete buildingObject;
                buildingObject = NULL;
            }
        }
    }
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
    //cout<<closestName<<endl;
    return closestName;
}

void GameScene::rightClickHit(int closestName) {
    if(buildingObject) {
        delete buildingObject;
        buildingObject = NULL;
        return;
    }
    if(closestName >= 1000 || closestName < 900)return;
    if(closestName < BAR_TOUCH_NUM) {
        vector<Item*>* invenItems = dataProcessor->getInvenItems();
        vector<Item*>::iterator i = invenItems->begin();
        for(; i != invenItems->end() ; ++i) {
            if((*i)->pos == closestName - INVEN_TOUCH_NUM) {
                break;
            }
        }
        Item* item = *i;
        // TO_DO: different items.
        if(item->type == CoalMine)
            buildingObject = new MinerBuilding();
        else if(item->type == Conve) {
            buildingObject = new Conveyor(this);
        }
        else
            buildingObject = new Statue;
        buildingObject->coor.setCoor(0, 0);
        buildingObject->isBuilding = true;
    }
    else {
        vector<Item*>* barItems = dataProcessor->getBarItems();
        vector<Item*>::iterator i = barItems->begin();
        for(; i != barItems->end() ; ++i) {
            if((*i)->pos == closestName - BAR_TOUCH_NUM) {
                break;
            }
        }
        Item* item = *i;
        // TO_DO: different items.
        if(item->type == CoalMine) 
            buildingObject = new MinerBuilding();
        else if(item->type == Conve) {
            buildingObject = new Conveyor(this);
        }
        else
            buildingObject = new Statue;
        buildingObject->coor.setCoor(0, 0);
        buildingObject->isBuilding = true;
    }
}

float GameScene::dist(float x1, float y1, float x2, float y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void GameScene::pickFunction(int button, int state, int x, int y)  //[ballAndTorusPicking.cpp]
{
    int viewport[4]; // Viewport data.//[ballAndTorusPicking.cpp]
    
    if (state != GLUT_DOWN) return;//[ballAndTorusPicking.cpp]
    
    
    glGetIntegerv(GL_VIEWPORT, viewport);//[ballAndTorusPicking.cpp]
    
    glSelectBuffer(1024, buffer);//[ballAndTorusPicking.cpp]
    (void) glRenderMode(GL_SELECT);//[ballAndTorusPicking.cpp]
    glMatrixMode(GL_PROJECTION);//[ballAndTorusPicking.cpp]
    glPushMatrix();//[ballAndTorusPicking.cpp]
    
    glLoadIdentity();//[ballAndTorusPicking.cpp]
    gluPickMatrix((float)x, (float)(viewport[3] - y), 3.0, 3.0, viewport);//[ballAndTorusPicking.cpp]
    gluPerspective(60, 1.0, 1.0, 200);
    
    isSelecting = true;
    glMatrixMode(GL_MODELVIEW);//[ballAndTorusPicking.cpp]
    glLoadIdentity();//[ballAndTorusPicking.cpp]
    
    glInitNames();//[ballAndTorusPicking.cpp]
    glPushName(0);//[ballAndTorusPicking.cpp]
    guis->drawGUI();
    setPointOfView();
    drawGameObject();
    drawPickObject();
    drawBuilding();
    hits = glRenderMode(GL_RENDER);//[ballAndTorusPicking.cpp]
    
    glMatrixMode(GL_PROJECTION);//[ballAndTorusPicking.cpp]
    glPopMatrix();//[ballAndTorusPicking.cpp]
    glMatrixMode(GL_MODELVIEW);//[ballAndTorusPicking.cpp]
    
    if(button == GLUT_LEFT_BUTTON)
        clickHit( findClosestHit(hits, buffer));//[ballAndTorusPicking.cpp]
    else
        rightClickHit(findClosestHit(hits, buffer));
    
    isSelecting = false;
    glutPostRedisplay();//[ballAndTorusPicking.cpp]
}
// [ballANdTorusPicking.cpp] by Sumanta Guhaaa

char* GameScene::getName() {
    char* res = "";
    int a = (selected-1000)/MAP_SIZE, b = (selected-1000)%MAP_SIZE;
    //cout<<a<<' '<<b<<' '<<grid[a][b]<<endl;
    if(selected < BUILDING_TOUCH_NUM)res = "";
    else if(selected < 900) {
        int a;
        for(a=0;a!=buildingVec.size();++a) {
            if(buildingVec[a]->touchNum == closestName)break;
        }
        BuildingObject* building = buildingVec[a];
        if(building->buildingType == 0) {
            MinerBuilding* miner = (MinerBuilding*) building;
            res = "Miner";
        }
        else res = "Statue";
    }
    else if(selected < 950) {
        res = "i";
        vector<Item*>* invenItems = dataProcessor->getInvenItems();
        vector<Item*>::iterator i = invenItems->begin();
        for(; i != invenItems->end() ; ++i) {
            if((*i)->pos == closestName - INVEN_TOUCH_NUM) {
                break;
            }
        }
        Item* item = *i;
        if(item->type == CoalMine)
            res = "Mine";
        else if(item->type == Conve) {
            res = "Conveyor";
        }
        else
            res = "Statue";
    }
    else if(selected < 1000) {
        vector<Item*>* barItems = dataProcessor->getBarItems();
        vector<Item*>::iterator i = barItems->begin();
        for(; i != barItems->end() ; ++i) {
            if((*i)->pos == closestName - BAR_TOUCH_NUM) {
                break;
            }
        }
        Item* item = *i;
        if(item->type == CoalMine)
            res = "Mine";
        else if(item->type == Conve) {
            res = "Conveyor";
        }
        else
            res = "Statue";
    }
    else if(selected < PICK_TOUCH_NUM) {
        if(grid[a][b] == GRASS)res = "Grass";
        else if(grid[a][b] == COAL)res = "Coal";
        else if(grid[a][b] == COPPER)res = "Copper";
        else if(grid[a][b] == IRON)res = "Iron";
        else res = "Conveyor";

    }
    else {
        int a=0;
        for(;a!=pickVec.size();++a)
            if(pickVec[a]->touchNum == selected)break;
        int type = pickVec[a]->type;
        switch (type) {
            case COAL:
                res = "Coal";
                break;
            case COPPER:
                res = "COPPER";
                break;
            case IRON:
                res = "Iron";
                break;
            default:
                break;
        }
    }
    return res;
}

void GameScene::drawName() {
    char* s = getName();
    if(s == "")return;
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(-1, -1.1, -2);
    glVertex3f(-1, -0.9, -2);
    glVertex3f(-0.5, -0.9, -2);
    glVertex3f(-0.5, -1.1, -2);
    glEnd();
    
    glColor3f(0, 0, 0);
    glRasterPos3f(-0.45, -0.51, -1);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, s);
    
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

void GameScene::passiveMouse(int x, int y) {
    if (x < 0 || x > width || y < 0 || y >height) {
        return;
    }
    mouseX = x;
    mouseY = y;
    
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
    isSelecting = true;
    guis->drawGUI();
    setPointOfView();
    drawGameObject();
    drawPickObject();
    drawBuilding();
    
    hits = glRenderMode(GL_RENDER);//[ballAndTorusPicking.cpp]
    
    glMatrixMode(GL_PROJECTION);//[ballAndTorusPicking.cpp]
    glPopMatrix();//[ballAndTorusPicking.cpp]
    glMatrixMode(GL_MODELVIEW);//[ballAndTorusPicking.cpp]
    
    passiveHit( findClosestHit(hits, buffer));//[ballAndTorusPicking.cpp]
    
    isSelecting = false;
    glutPostRedisplay();//[ballAndTorusPicking.cpp]
}

void GameScene::keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'e':
            guis->showInventory = !guis->showInventory;
            break;
        case 'r':
            if(buildingObject) {
                buildingObject->toward = (buildingObject->toward+1)%4;
            }
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