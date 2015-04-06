//
//  Song.h
//  SongSearch
//
//  Created by Alex King on 4/9/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#ifndef __SongSearch__Song__
#define __SongSearch__Song__

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

struct Song {
    
    Song();
    Song(string title, string artist, string lyrics);
    Song(const Song &rightHandSide);
    Song &operator=(const Song &rightHandSide);
    
    string alphaOnly(string s);
    void import_lyrics(const char * filename, bool show_progress);
    
    void setTitle(string intitle);
    void setArtist(string inartist);
    void setLyrics(int place, string word);
    void setLyricsLength(int inlength);
    
    string getTitle();
    string getArtist();
    string getLyrics(int index);
    string* getAllLyrics();
    int getLyricsLength();
    int getLyricsCapacity();
    
    string makeContext(int inWordIndex);
    
    ~Song();
    
private:
    
    string title;
    string artist;
    string *lyrics;
    int lyricsLength;
    int lyricsCapacity;
    
};

#endif /* defined(__SongSearch__Song__) */
