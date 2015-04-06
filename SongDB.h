//
//  SongDB.h
//  SongSearch
//
//  Created by Alex King on 4/11/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#ifndef __SongSearch__SongDB__
#define __SongSearch__SongDB__

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "Song.h"

using namespace std;

struct SongDB {
    
    SongDB();
    SongDB(int size);
    
    void import_lyrics(const char * filename, bool show_progress);
    void setDBLength(int length);
    
    Song* getSongs();
    int getDBLength();
    
    ~SongDB();
    
private:
    
    Song *songs;
    int dbLength;
    int dbCapacity;
    
};


#endif /* defined(__SongSearch__SongDB__) */
