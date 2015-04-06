Alex King
COMP 15
HW5 - Final Project

Purpose of Program:
The purpose of this program is to read in a text file of songs, organize the
information into two databases, and be able to quickly search for words that 
occur in the database with high frequency.

List of Files:
- main.cpp: This file specifies the text file to be read in, initializes and
  populates databases, then allows for searching of terms until the user
  enters "<BREAK>", in which case the program exits.
  
- Song.cpp, Song.h: The Song class, which is a structure containing information
  on artist, title and an array of lyric strings.
  
- SongDB.cpp, SongDB.h: The class representing an array of Songs, implemented
  as a dynamic array. When main() is called, the text file is imported into
  a SongDB.

- FreqNode.cpp, FreqNode.h: The class representing the frequency that a certain
  word occurs in a song. It contains the word in question, the index of the 
  song in the SongDB array, and a vector of ints for the index of each time the
  word appears in the lyric array.
  
- LocalHashTable.cpp, LocalHashTable.h: The class representing an array of
  FreqNodes, implemented as a hash table. For each song in the SongDB, a
  LocalHashTable is made to keep track of each word in the song and in what
  position each word appears.
  
- WordNode.cpp, WordNode.h: The class for a word's frequency in the entire 
  SongDB. It contains the word in question, and a list of 10 FreqNodes that
  represent the 10 songs where the word occurs most frequently.
  
- WordHashTable.cpp, WordHashTable.h: The class for the entire global hash
  table, which is made up of WordNodes. This data structure is created, and
  then searched.
  
- hashfunc.cpp, hashfunc.h: The provided hash function, used to hash FreqNodes
  and WordNodes to unique locations.

How to Compile:

To compile, type "make songsearch" at the terminal.

Outline of Algorithms and Data Structures:

This assignment represented a great design challenge. How does one create a
database that holds sequential information about 172,000 songs, but also makes
the database searchable so that high-occurring words can be returned in just a
few seconds? Thinking about this brought me to my design. The SongDB is a large
dynamic array that holds all song information imported from the text file. It
exists for the purpose of keeping only one copy of artist and title 
information, as well as being the single place where lyrics are kept
sequentially, which is necessary for generating context.

The SongDB contains all of the song information, but it is far from quick to
search. Because the user inputs single words for searching, a data structure
quick to search and based around strings needed to be used. I chose to use
a hash table for this. However, I did not want to read every word into a 
master hash table, keeping track of every word that appears in every song and
the frequency for all of them. This would take more memory, more time to sort,
and/or more time to search and return information at the end. It did not seem
like the best option available.

To remedy this, I chose to make a smaller "local" hash table for each song,
each holding a tally of word occurrences. The hash table is then very easy
to loop through, adding these Frequency Nodes to the global hash table if 
the tally is high enough to make it into the "top 10" list that's stored in
each WordNode within the WordHashTable. Though making these local tables surely
takes more time, the memory usage is only temporary, and it pays highly in
terms of overall database creation time as well as search time.

When the user searches for a word, the word is hashed and the WordHashTable is
searched (using linear probing if necessary) to find the correct WordNode.
The WordNode already contains the "top 10" information in its array of 10
FreqNodes. In each FreqNode, the song index is stored, allowing fast retrieval
of artist, title and lyrics information. A vector of lyric positions is also
stored. Therefore, it takes very little time once the WordNode is found to
output results. Because each location of the word is already known, it only
takes as much time as it takes to generate context and print.