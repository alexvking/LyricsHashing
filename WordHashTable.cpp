//
//  WordHashTable.cpp
//  SongSearch
//
//  Created by Alex King on 4/14/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#include "WordHashTable.h"
#include "hashfunc.h"
#include "WordNode.h"
#include "LocalHashTable.h"

using namespace std;

WordHashTable::WordHashTable() {

    HTCapacity = 1661;
    WordNode *tempWords = new WordNode[HTCapacity];
    wordNodes = tempWords;
    HTLength = 0;
}

WordHashTable::~WordHashTable() {
    
    delete[] wordNodes;
    
}

WordNode* WordHashTable::getWordNodes() { return wordNodes; }

// loadGlobalHashTable: Create list of words with occurrences of popular songs
// from the SongDB of all Song structures that were read in
void WordHashTable::loadGlobalHashTable(SongDB *aDB) {
    
    string lyricToAdd;
    
    // looping through the entire SongDB array
    for (int i = 0; i < aDB->getDBLength(); i++) {
        
        LocalHashTable songHT; // first make a local hash table
        songHT.makeLocalHashTable(&aDB->getSongs()[i], i);
        
        // Then, conditionally add its entries to the global table if word
        // frequencies were high enough to "make it into the top 10"
        for (int j = 0; j < songHT.getHTCapacity(); j++) {
            
            if (songHT.getFreqNodes()[j].getTheWord() != "") { // found a node
                
                // Expansion takes place if the load factor exceeds .5
                if (HTLength > (HTCapacity/2)) expandGlobalHashTable();
    
                addToHT(&songHT.getFreqNodes()[j]); // conditionally add it
            }
        }
    }
}

WordNode WordHashTable::getWordNode(int index) { return wordNodes[index]; }

int WordHashTable::getHTCapacity() { return HTCapacity; }

// addToHT: Takes in a frequency node from a song's "local" hash table and
// a songIndex to access song information. It looks for each the word in the
// global hash table, and once found, checks to see if the occurrence in
// question is high enough to be saved in the top 10 list.
void WordHashTable::addToHT(FreqNode *freqNodeToAdd) {
    // First find the hash position based on table size
    uint32_t hashCode = hash_string(freqNodeToAdd->getTheWord());
    uint32_t hashPosition = hashCode % (uint32_t) HTCapacity; // mod it by the capacity
    string toAdd = freqNodeToAdd->getTheWord();
    uint32_t iter = hashPosition % (uint32_t) HTCapacity;
// Loop will circle back to the beginning of the hash table if it hits the end
        while ((hashPosition % (uint32_t) HTCapacity) < (uint32_t) HTCapacity) {
            iter = iter % (uint32_t) HTCapacity;
            string searchWord = wordNodes[iter].getTheWord();
            if (searchWord == "") { // Word has yet to be added to global hash
                // table, so we can set the word and occurrence and end.
                wordNodes[iter].setTheWord(toAdd);
                wordNodes[iter].addToFreqList(freqNodeToAdd, 0);
                HTLength++;
                return; }
            else if (searchWord == toAdd) break;
            iter++; }
    hashPosition = iter;
    int listLength = wordNodes[hashPosition].getFreqListLength();
    if (listLength < 10) { // adding at the end
        wordNodes[hashPosition].addToFreqList(freqNodeToAdd, listLength);
        wordNodes[hashPosition].sortFreqList();
    } // else: Case where list is already full
    else if (freqNodeToAdd->getWordPositions().size() >
        wordNodes[hashPosition].getFreqList()[9].getWordPositions().size() ) {
        wordNodes[hashPosition].addToFreqList(freqNodeToAdd, 9);
        wordNodes[hashPosition].sortFreqList();
    }
}

void WordHashTable::expandGlobalHashTable() {
    int newCap = (HTCapacity*2)-1; // effectively doubling, but keeping odd
    WordNode* temp = new WordNode[newCap];
    for (int i = 0; i < HTCapacity; i++) {
        // if you find a word node, rehash the word and set the new location
        string iterword = wordNodes[i].getTheWord();
        if (iterword != "") {
            uint32_t hashPosition = hash_string(alphaOnly(iterword));
            hashPosition = hashPosition % (uint32_t) newCap; // creating new location
            while (hashPosition < (uint32_t) newCap) {
                
                if (temp[hashPosition].getTheWord() == "") { // finding a spot
                    
                    temp[hashPosition] = wordNodes[i]; // copy data
                    break;
                }
                hashPosition++;
            }
        }
    }
    delete[] wordNodes;
    wordNodes = temp;
    HTCapacity = newCap;
}

void WordHashTable::search(SongDB *aDB){
    string searchTerm;
    cin >> searchTerm;
    while (searchTerm != "<BREAK>") {
        string lowerSearch;
        lowerSearch = alphaOnly(searchTerm);
        uint32_t hashCode = hash_string(lowerSearch);
        uint32_t hashPosition = hashCode % (uint32_t) HTCapacity;
        
        uint32_t iter = hashPosition;
        bool found = false;
        while (getWordNodes()[iter].getTheWord() != "") { // until empty element
            if (lowerSearch == "") break; // empty string => empty results
            if (getWordNodes()[iter].getTheWord() == lowerSearch) {

                getWordNodes()[iter].printWordNode(aDB);
                found = true;
                break;
            }
            iter++;
        }
        if (!found) cout << "<END-OF-REPORT>" << endl;
        cin >> searchTerm;
    }
}

// alphaOnly() strips off non-alphabetic and non-digit characters
// and returns a string with just the alphas and digits.
string WordHashTable::alphaOnly(string s) {
    ostringstream ss;
    for (size_t i=0;i<s.length();i++) {
        if (isalnum(s[i])){
            ss << (char)(tolower(s[i]));
        }
    }
    return ss.str();
}
