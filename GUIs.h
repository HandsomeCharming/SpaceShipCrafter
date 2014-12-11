//
//  GUIs.h
//  FinalProject
//
//  Created by  帅哥 on 11/17/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

#ifndef __FinalProject__GUIs__
#define __FinalProject__GUIs__

#include <stdio.h>

#define INVEN_ROW 5
#define INVEN_COL 9
#define INVEN_BLK_SIZE 1
#define BAR_COL 9

class DataProcessor;

class Inventory {
public:
    Inventory() : inventoryPos{0,0}, inventorySize{2.5,2} {}
    float inventoryPos[2];
    float inventorySize[2];
    int selected;
    void drawInventory();
    void drawItems();
    DataProcessor* dataProcessor;
};

class Bar {
public:
    Bar() {}
    const float barPos[2] = {-1.2,-2.8};
    const float barSize[2] = {2.5,0.5};
    int selected;  //-1 for not selected
    void drawBar();
    void drawItems();
    DataProcessor* dataProcessor;
};

class GUIs {
public:
    GUIs() : showInventory(false), showBar(true) {
        inventory = new Inventory();
        bar = new Bar();
    }
    
    Inventory* inventory;
    Bar* bar;
    
    bool showBar;
    bool showInventory;
    void drawGUI();
    void notSelected();
};



#endif /* defined(__FinalProject__GUIs__) */
