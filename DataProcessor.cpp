//
//  DataProcessor.cpp
//  FinalProject
//
//  Created by  帅哥 on 11/18/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

#include "DataProcessor.h"

void DataProcessor::pickItem(Item* item) {
    invenItems->push_back(item);
}

vector<Item*>* DataProcessor::getInvenItems() {
    return invenItems;
}

vector<Item*>* DataProcessor::getBarItems() {
    return barItems;
}