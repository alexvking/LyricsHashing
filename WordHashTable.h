//
//  WordHashTable.h
//  SongSearch
//
//  Created by Alex King on 4/14/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#ifndef __SongSearch__WordHashTable__
#define __SongSearch__WordHashTable__

#include <iostream>
#include "FreqNode.h"
#include "WordNode.h"
#include "SongDB.h"


using namespace std;

struct WordHashTable {
    
    WordHashTable();
    WordHashTable(int size);

    void loadGlobalHashTable(SongDB *aDB);
    void expandGlobalHashTable();

    void setHTLength(int inlength);
    void setHTCapacity (int inlength);
    void setWordNode(int place, WordNode* wordNodeToAdd);

    void addToHT(FreqNode* freqNodeToAdd);
    
    void search(SongDB *aDB);
    
    string alphaOnly(string s);
    
    int getHTLength();
    int getHTCapacity();
    WordNode getWordNode(int index);
    WordNode* getWordNodes();
    
    ~WordHashTable();
    
private:
    
    int HTLength;
    int HTCapacity;
    WordNode *wordNodes;
    
};

#endif /* defined(__SongSearch__WordHashTable__) */
