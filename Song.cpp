//
//  Song.cpp
//  SongSearch
//
//  Created by Alex King on 4/9/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#include "Song.h"

using namespace std;

Song::Song() {
    
    title = "";
    artist = "";
    lyricsCapacity = 200;
    string *templyrics = new string[lyricsCapacity];
    lyrics = templyrics;
    lyricsLength = 0;
    
}

Song::~Song(){

    delete [] lyrics;
}

string Song::getArtist() { return artist; }
string Song::getLyrics(int index) { return lyrics[index]; }
string Song::getTitle() { return title; }

string* Song::getAllLyrics() { return lyrics; }

void Song::setArtist(string inartist) { artist = inartist; }

// setLyrics : adds a given string to a location in a lyric array
void Song::setLyrics(int place, string word) {
        // expanding if necessary
        if (place == lyricsCapacity) {
            string* temp = new string[lyricsCapacity*2];
            for (int i = 0; i < lyricsLength; i++) {
                temp[i] = lyrics[i];
            }

                delete [] lyrics;

            lyrics = temp;
            lyricsCapacity = lyricsCapacity*2;
        }
    lyrics[place] = word; // Add word at position specified
    lyricsLength++; // increment the length
}

// makeContext : Generates context of word in question by making string
// of nearby words in the song
string Song::makeContext(int inWordIndex) {
    
    string theContext = "";
    
    if (lyricsLength < 6) {
        
        for (int i = 0; i < lyricsLength; i++)
            theContext = theContext + lyrics[i] + " ";
        
    }
    else if (inWordIndex < 5) { // beginning of song
        
        for (int i = 0; i < inWordIndex+6; i++)
            theContext = theContext + lyrics[i] + " ";
        
    }
    
    else if (lyricsLength-1-inWordIndex < 5) { // end of song
        for (int i = inWordIndex-5; i < lyricsLength; i++){
            theContext = theContext + lyrics[i] + " ";
        }
    }
    
    else { // somewhere in the middle of the song, so five before and five after
        
        for (int i = inWordIndex-5; i < inWordIndex+6; i++) {
            theContext = theContext + lyrics[i] + " ";
        }
    }
    return theContext;
}

int Song::getLyricsCapacity() { return lyricsCapacity; }

void Song::setTitle(string intitle) { title = intitle; }

int Song::getLyricsLength() { return lyricsLength; }

void Song::setLyricsLength(int inlength) { lyricsLength = inlength; }

Song::Song(const Song &rightHandSide) {

    lyricsCapacity = rightHandSide.lyricsCapacity;
    lyricsLength = rightHandSide.lyricsLength;
    artist = rightHandSide.artist;
    title = rightHandSide.title;
    //lyrics = NULL;
    
    if (lyricsLength==0) return;
    
    //if (lyrics != NULL) delete [] lyrics;
    lyrics = new string[lyricsCapacity];
    
    for (int i=0;i<lyricsLength;i++) {
        lyrics[i] = rightHandSide.lyrics[i];
    }
}

Song &Song::operator=(const Song &rightHandSide){
    if (this != &rightHandSide) {

        title = rightHandSide.title;
        artist = rightHandSide.artist;
        lyricsLength = rightHandSide.lyricsLength;
        lyricsCapacity = rightHandSide.lyricsCapacity;
        
        if (lyricsCapacity == 0) {
            
            lyrics = NULL; return *this;
            
        }
        
        lyrics = new string[lyricsCapacity];
        
        for (int i=0;i<lyricsLength;i++) {
            lyrics[i] = rightHandSide.lyrics[i];
        }
    }
    return *this;
    
}
