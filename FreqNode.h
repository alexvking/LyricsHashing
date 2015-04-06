//
//  FreqNode.h
//  SongSearch
//
//  Created by Alex King on 4/13/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#ifndef __SongSearch__FreqNode__
#define __SongSearch__FreqNode__

#include <iostream>
#include "Song.h"
#include "SongDB.h"
#include <vector>

struct FreqNode {
    
    FreqNode();

    void setSongIndex(int index);
    void addPosition(int lyricIndex);
    void setTheWord(string inword);
    
    void printResults(SongDB *theDB);
    
    int getIndex();
    vector<int> getWordPositions();
    string getTheWord();
    
private:
    
    string theWord;
    int songIndex; // from this, easy to grab Artist/Title info
    vector<int> wordPositions; // a list of every index where the word occurs
    
};

#endif /* defined(__SongSearch__FreqNode__) */
