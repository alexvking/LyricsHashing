//
//  FreqNode.cpp
//  SongSearch
//
//  Created by Alex King on 4/13/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#include "FreqNode.h"

FreqNode::FreqNode() {
    
    theWord = "";
    songIndex = 0;
    
}

void FreqNode::setSongIndex(int index) { songIndex = index; }

void FreqNode::addPosition(int lyricIndex) {
    
    wordPositions.push_back(lyricIndex); // push position onto vector
    
}

vector<int> FreqNode::getWordPositions() { return wordPositions; }

void FreqNode::setTheWord(string inword) { theWord = inword; }


int FreqNode::getIndex() { return songIndex; }

string FreqNode::getTheWord() { return theWord; }

// printResults : Print every occurrence of a word in the given frequency node
void FreqNode::printResults(SongDB *theDB) {
    
    string theTitle = theDB->getSongs()[songIndex].getTitle();
    string theArtist = theDB->getSongs()[songIndex].getArtist();
    
    // A loop for each time the word appears in the song (10 at most)
    for (size_t i = 0; i < wordPositions.size(); i++) {
        
        string theContext =
        theDB->getSongs()[songIndex].makeContext(wordPositions[i]);
        
        cout << "Title: " << theTitle << endl;
        cout << "Artist: " << theArtist << endl;
        cout << "Context: " << theContext << endl << endl;
        if (i == 9) break; // only print up to 10 occurrences with context
        
    }
    
}