//
//  WordNode.h
//  SongSearch
//
//  Created by Alex King on 4/13/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#ifndef __SongSearch__WordNode__
#define __SongSearch__WordNode__

#include <iostream>
#include "Song.h"
#include "SongDB.h"
#include "FreqNode.h"

using namespace std;

struct WordNode {
    
    WordNode();
    WordNode(const WordNode &rightHandSide);
    WordNode &operator=(const WordNode &rightHandSide);

    void setTheWord(string inWord);
    void addToFreqList(FreqNode *toAdd, int index);
    void setFreqListLength (int length);
    void setFreqList(FreqNode *freqListToAdd);
    void sortFreqList();
    WordNode* getNextNode();
    
    void printWordNode(SongDB *aDB);
    
    string getTheWord();
    FreqNode * getFreqList();
    int getFreqListLength();
    
    ~WordNode();
    
    
private:
    
    string theWord;
    FreqNode * freqList;
    int freqListLength;
    
};


#endif /* defined(__SongSearch__WordNode__) */
