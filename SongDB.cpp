//
//  SongDB.cpp
//  SongSearch
//
//  Created by Alex King on 4/11/14.
//  Copyright (c) 2014 Alex King. All rights reserved.
//

#include "SongDB.h"

SongDB::SongDB() {

    dbCapacity = 85; // factor that scales well to ~172,000
    Song *tempList = new Song[dbCapacity];
    songs = tempList;
    dbLength = 0;

}

SongDB::~SongDB() {

    delete[] songs;
    
}

Song* SongDB::getSongs() { return songs; }

int SongDB::getDBLength() { return dbLength; }

// Provided by Prof. Gregg:
void SongDB::import_lyrics(const char * filename, bool show_progress)
{
    
    ifstream in(filename);			// creates an input stream
    int song_count = 0;			// for progress indicator
	string artist, title, word;
    
    int j = 0;
    
	// -- While more data to read...
	while ( ! in.eof() )
	{
		// -- First line is the artist
		getline(in, artist);
		if (in.fail()) break;
		// -- Second line is the title
		getline(in, title);
		if (in.fail()) break;
        song_count++;
		if ( show_progress )
		{

			if (song_count % 10000 == 0) {
				cout << "At "       << song_count <<
                " Artist: " << artist     <<
                " Title:"   << title << endl;
			}
		}
        // Expanding if necessary
        if (song_count == dbCapacity) {

            Song* temp = new Song[dbCapacity*2];
            
            for (int i = 0; i < song_count-1; i++) {
                temp[i] = songs[i];
                
            }
            delete[] songs;
            songs = temp;
            dbCapacity = dbCapacity*2;
            
        }
        
        songs[j].setArtist(artist);
        songs[j].setTitle(title);
        
        int i = 0;
        
		// -- Then read all words until we hit the
		// -- special <BREAK> token
		while ( in >> word && word != "<BREAK>" ){
            
            songs[j].setLyrics(i, word); // add each word to the lyric array
            i++;
		}
		// -- Important: skip the newline left behind
        j++;
        in.ignore();
	}
    dbLength = song_count; // set the end length
    return;
}
