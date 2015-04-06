//
//  LocalHashTable.h
//  SongSearch
//
//  Created by Alex King on 4/15/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#ifndef __SongSearch__LocalHashTable__
#define __SongSearch__LocalHashTable__

#include <iostream>
#include "FreqNode.h"
#include "Song.h"
#include <vector>

struct LocalHashTable {
    
    LocalHashTable();
    
    string alphaOnly(string s);
    int getHTCapacity();
    
    void makeLocalHashTable(Song *aSong, int inIndex);
    void addToLocalHashTable(string lyric, int inIndex);
    void expandLocalHashTable();
    FreqNode* getFreqNodes();
    
    ~LocalHashTable();
    
private:

    FreqNode* freqNodes;
    int HTCapacity;
    int HTLength;
    
};

#endif /* defined(__SongSearch__LocalHashTable__) */
