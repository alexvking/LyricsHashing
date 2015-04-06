//
//  LocalHashTable.cpp
//  SongSearch
//
//  Created by Alex King on 4/15/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#include "LocalHashTable.h"
#include "hashfunc.h"
#include "FreqNode.h"


LocalHashTable::LocalHashTable(){
    
    HTCapacity = 821; // A good starting prime
    HTLength = 0;
    FreqNode* tempNodes = new FreqNode[HTCapacity];
    freqNodes = tempNodes;
    
}

LocalHashTable::~LocalHashTable() {
    delete[] freqNodes;
    
}

int LocalHashTable::getHTCapacity() { return HTCapacity; }

FreqNode* LocalHashTable::getFreqNodes() { return freqNodes; }

void LocalHashTable::expandLocalHashTable() {
        int newCap = (HTCapacity*2)-1; // effectively doubling, but keeping odd
        FreqNode* temp = new FreqNode[newCap];
        for (int i = 0; i < HTCapacity; i++) {
            // if you find a word node, rehash the word and set the new location
            string iterword = freqNodes[i].getTheWord();
            
            if (iterword != "") {
                uint32_t hashPosition = hash_string(alphaOnly(iterword));
                hashPosition = hashPosition % (uint32_t) newCap;
                
                while (hashPosition < (uint32_t) newCap) {
                    
                    if (temp[hashPosition].getTheWord() == "") {
                        
                        temp[hashPosition] = freqNodes[i];
                        break;
                    }
                    hashPosition++;
                }
            }
        }
    delete[] freqNodes;
    freqNodes = temp;
    HTCapacity = newCap;
}

// makeLocalHashTable: Loop through a song's lyrics, making an association
// list with information about how many times each word appears.
void LocalHashTable::makeLocalHashTable(Song *aSong, int inIndex) {
    string lyricToAdd; uint32_t hashCode; uint32_t hashPosition;
    for (int j = 0; j < aSong->getLyricsLength(); j++) { // for all lyrics,
        // expanding if load factor exceeds ~.8
        if (HTLength > (HTCapacity/1.2)) expandLocalHashTable();
        lyricToAdd = alphaOnly(aSong->getLyrics(j)); //strip lyric of formatting
        hashCode = hash_string(lyricToAdd); // find hashposition
        hashPosition = hashCode % (uint32_t) HTCapacity;
        
        uint32_t iter = hashPosition;
        
        while ((iter % (uint32_t) HTCapacity) < (uint32_t) HTCapacity) {
            
            iter = iter % (uint32_t) HTCapacity;
            
            if (freqNodes[iter].getTheWord() == "") { //empty node, initializing
                freqNodes[iter].setTheWord(lyricToAdd);
                freqNodes[iter].setSongIndex(inIndex);
                freqNodes[iter].addPosition(j);
                HTLength++;
                break;
            }
            if (freqNodes[iter].getTheWord() == lyricToAdd) {
                freqNodes[iter].addPosition(j); // a match has been found
                break;
            }
            iter++;
        }
    }
}

// alphaOnly() strips off non-alphabetic and non-digit characters
// and returns a string with just the alphas and digits.
string LocalHashTable::alphaOnly(string s) {
    ostringstream ss;
    for (size_t i=0;i<s.length();i++) {
        if (isalnum(s[i])){
            ss << (char)(tolower(s[i]));
        }
    }
    return ss.str();
}
