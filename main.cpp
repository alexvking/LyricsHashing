//
//  main.cpp
//  SongSearch
//
//  Created by Alex King on 4/9/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#include "Song.h"
#include "SongDB.h"
#include "WordHashTable.h"
#include <iostream>
#include "hashfunc.h"

using namespace std;

string alphaOnly(string s) {
    ostringstream ss;
    for (size_t i=0;i<s.length();i++) {
        if (isalnum(s[i])){
            ss << (char)(tolower(s[i]));
        }
    }
    return ss.str();
}

int main(int argc, char *argv[]){
    
    string filename;
    SongDB theDB;
    
    if (argc == 2) {

    theDB.import_lyrics(argv[1], false); // importing into master array
    WordHashTable theGlobalHashTable;
    theGlobalHashTable.loadGlobalHashTable(&theDB);
    // populating the full hash table
    theGlobalHashTable.search(&theDB); // search as much as wanted
        
    }
    
    else {
        cout << "Usage: songsearch database.txt\n";
    }
    return 0;
}
