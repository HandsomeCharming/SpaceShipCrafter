//
//  DataProcessor.cpp
//  FinalProject
//
//  Created by  帅哥 on 11/18/14.
//  Copyright (c) 2014 帅哥. All rights reserved.
//

#include "DataProcessor.h"

void DataProcessor::pickItem(Item item) {
    items.push_back(item);
}

vector<Item> DataProcessor::getItems() {
    return items;
}