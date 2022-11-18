//////////////////////////////////////////////////////////////////
//								//
//	The interface of utility functions is put here		//
//								//
//////////////////////////////////////////////////////////////////


#ifndef UTIL_H	// Header guard
#define UTIL_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 1024
#define WORD_FLAG "#"
#define LINE_FLAG "\n"

// Function to createa new object of struct Word
struct Word* create_word (const char *w, unsigned long off);

// Hash function to select a position in the hash table to insert a new word
int hash_word (unsigned char *w);

// Function to insert a word into the hash table
int insert_word (struct Word **hd, struct Word *wobject);

// Function to search a word in the hash table
struct Word* search_word (struct Word **hd, unsigned char *word);

// Function to read the input file, and get the meaing of word
int get_meaning (char *buf, struct Word* wobject, FILE *dict_file);

#endif
////////////////////////////////////////////////////////////////////////////

