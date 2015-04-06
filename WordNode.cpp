//
//  WordNode.cpp
//  SongSearch
//
//  Created by Alex King on 4/13/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#include "WordNode.h"
#include "FreqNode.h"

WordNode::WordNode() {
    
    theWord = "";
    FreqNode *tempFreq = new FreqNode[10];
    freqList = tempFreq;
    freqListLength = 0;
    
}

WordNode::~WordNode() {
    delete[] freqList;
    
}

void WordNode::setTheWord(string inWord) { theWord = inWord; }
void WordNode::setFreqListLength(int length) {
    
    freqListLength = length;
    
}

void WordNode::setFreqList(FreqNode *freqListToAdd) {
    
    freqList = freqListToAdd;
}

// addtoFreqList : Adds a frequency node for a given song to a word node
void WordNode::addToFreqList(FreqNode *toAdd, int index) {

    freqList[index] = *toAdd;
    freqListLength = index+1;
    
}
// Insertion Sort for FreqLists, sorted decreasing by frequency count
void WordNode::sortFreqList() {
    
    for (int index = 1; index < freqListLength; index++) {
        
        for (int place = index; place > 0; place--) {
            
            if (freqList[place].getWordPositions().size() <
                freqList[place-1].getWordPositions().size() ) break;
            
            else {
                
                FreqNode temp = freqList[place];
                freqList[place] = freqList[place-1];
                freqList[place-1] = temp;
            }
            
        }
        
    }
    
}
// printWordNode: Prints top results for the given word
void WordNode::printWordNode(SongDB *aDB) {
    
    for (int i = 0; i < freqListLength; i++) {
        
        freqList[i].printResults(aDB);
        
    }
    
    cout << "<END-OF-REPORT>" << endl;
    
}

string WordNode::getTheWord() { return theWord; }
FreqNode * WordNode:: getFreqList() { return freqList; }
int WordNode::getFreqListLength() { return freqListLength; }

WordNode::WordNode(const WordNode &rightHandSide) {

    theWord = rightHandSide.theWord;
    freqListLength = rightHandSide.freqListLength;
    
    if (freqListLength==0) return;
    

    delete [] freqList;
    freqList = new FreqNode[10];
    
    for (int i=0;i<freqListLength;i++) {
        freqList[i] = rightHandSide.freqList[i];
    }
}

WordNode &WordNode::operator=(const WordNode &rightHandSide){
    if (this != &rightHandSide) {

        theWord = rightHandSide.theWord;
        freqListLength = rightHandSide.freqListLength;

        if (freqListLength == 0) {
            
            freqList = NULL; return *this;
            
        }
        
        delete [] freqList;
        
        freqList = new FreqNode[10];
        
        for (int i=0;i<freqListLength;i++) {
            freqList[i] = rightHandSide.freqList[i];
        }
    }
    return *this;
    
}