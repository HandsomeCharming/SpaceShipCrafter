//
//  DataProcessor.h
//  FinalProject
//
//  Created by  帅哥 on 11/18/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

#ifndef __FinalProject__DataProcessor__
#define __FinalProject__DataProcessor__

#include <stdio.h>
#include <vector>
#include "Basic.h"


using namespace std;



class Item {
public:
    
    
    ItemType type;
    int count;  //Stack
    int pos;    //pos in inventory or bar.
    int state;  //0 for inventory, 1 for bar, 2 for selected by mouse.
};

class DataProcessor {
public:
    DataProcessor() : mouseItem(NULL) {
        invenItems = new vector<Item*>();
        barItems = new vector<Item*>();
    }
    vector<Item*>* invenItems;
    vector<Item*>* barItems;
    Item* mouseItem;
    void pickItem(Item* item);
    vector<Item*>* getBarItems();
    vector<Item*>* getInvenItems();
};


#endif /* defined(__FinalProject__DataProcessor__) */
