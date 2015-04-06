#
# Makefile for SongSearch, Assignment 5
#
CXX = clang++
FLAGS = -Wall -Wextra -Wconversion -g

songsearch: main.cpp SongDB.cpp SongDB.h Song.cpp Song.h FreqNode.cpp \
	 FreqNode.h WordNode.cpp WordNode.h WordHashTable.cpp WordHashTable.h \
	 LocalHashTable.cpp LocalHashTable.h hashfunc.cpp hashfunc.h
	 ${CXX} ${FLAGS} -o songsearch main.cpp SongDB.cpp Song.cpp FreqNode.cpp \
	 WordNode.cpp WordHashTable.cpp LocalHashTable.cpp hashfunc.cpp
	
clean:
	rm -f songsearch

provide_design:
	provide comp15 hw5_design songsearch_design.txt

provide:
	provide comp15 hw5 Makefile readme.txt main.cpp SongDB.cpp\
	 SongDB.h Song.cpp Song.h FreqNode.cpp FreqNode.h WordNode.cpp\
	 WordNode.h WordHashTable.cpp WordHashTable.h LocalHashTable.cpp\
	 LocalHashTable.h hashfunc.cpp hashfunc.h