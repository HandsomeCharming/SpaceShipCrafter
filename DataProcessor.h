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

using namespace std;


class Item {
public:
    int type;
    int count;
};

class DataProcessor {
public:
    DataProcessor() {
    }
    vector<Item> items;
    void pickItem(Item item);
    vector<Item> getItems();
};

#endif /* defined(__FinalProject__DataProcessor__) */
