//////////////////////////////////////////////////////////////////
//								//
//	The interface of the hashtable is put here		//
//								//
//////////////////////////////////////////////////////////////////

//header-guard to prevent header file from being included more than once
#ifndef HASHTABLE_H 
#define HASHTABLE_H

// Define the size of hash table to 63 
#define HASH_SIZE 63 
// 26 uppercases + 26 lowercases + 10 numbers + other letters.

// Define the basic Data Structure
struct Word {
	unsigned char *word;	// word name
	unsigned long offset;	// offset of word meaning in the dict_file
	struct Word   *next;	// link to the next word object
};


// Declare an array of size HASHSIZE Word pointer, and use it as the hashtable
	extern struct Word* hashdict[HASH_SIZE];

#endif
/////////////////////////////////////////////////////////////////////////////

