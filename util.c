//////////////////////////////////////////////////////////////////////////
//									//
//	The implementation of utility functions will be put here	//
//									//
//////////////////////////////////////////////////////////////////////////


#include"util.h"
#include"hashtable.h"

extern char contents[MAX_LEN];
// Function to create a new object of struct Word
struct Word* create_word (const char *w, unsigned long off) {

	// Create a struct Word object in Heap Memory
	struct Word *word = (struct Word*)malloc(sizeof(struct Word));
	// Allocate memory for word field <- w
	word->word = (unsigned char*)malloc(strlen(w) + 1);

	// Copy the passed w content to object's word field
	strcpy ((char*)word->word, w);	
	// printf("[create_word] word name: %s.\n", word->word);

	// Copy the parameter off to object's offset field
	word->offset = off;
	// printf("[create_word] word offset: %ld.\n", word->offset);

	// The object's next field is still not assigned (not linked yet)
	
	// Return the object
	return word;
} 

// Hash funtion to select the position to which word object to be inserted in the hashtable
int hash_word (unsigned char *w) {

	//  key <- the ASCII code of the first letter of parameter w 
	int key = *w;

	// Generate hashcode based on key
	int hashcode;
	if ((key >= 48) && (key <= 57)) {
		hashcode = key % 48;
	}
	else if ((key >= 65) && (key <= 90)) {
		hashcode = key % 55;
	}
	else if ((key >= 97) && (key <= 122)) {
		hashcode = key % 61; 
	}
	else hashcode = 62;

	return hashcode; 
}

// Function to insert a word into the hash table
// insert_word uses temp1
int insert_word (struct Word **hd, struct Word *wobject) {
	
	/*
	// Check if the word were already exist => skip the insertion
	if (search_word(hd, wobject->word) != NULL) {
		printf("Word already existed.\n");
		return 0;
	}	// this block is buggy  
	*/

	// Ground the end of the list
	wobject->next = NULL;
	// printf("wobject: grounded\n"); check dump: passed

	// Get the position index for the insertion
	int hash_idx = hash_word(wobject->word);
	// printf("[insert] Index %d\n", hash_idx);
	// Check dump: passed 

	// Inserting by linked-list tail insertion method
	struct Word *temp1 = (struct Word*)malloc(sizeof(struct Word));
	// printf("temp node created\n");
	temp1 = hd[hash_idx];
	// printf("temp node: linked\n");
	// Check dump: passed
	
	// If hd[idx] is empty then link the wobject directly
	if (temp1 == NULL) {
		hd[hash_idx] = wobject;
		// printf("[insert] hd[idx] is empty, link the wobject directly\n");
	}
	else {
		while (temp1->next != NULL) {
			 temp1 = temp1->next;
		}
		temp1->next = wobject;
	} 

	return 1;
}

// Function to search a word in the hash table
// search_word uses temp2
struct Word* search_word (struct Word **hd, unsigned char *w) {
	
	// Create a temp object
	// Core dumped: eliminated
	struct Word *temp2 = (struct Word*)malloc(sizeof(struct Word));
	// printf("[search] temp2 created\n");

	// Get search index
	int hash_idx = hash_word(w);
	// printf("[search] temp2 index: %d\n", hash_idx);
	// Search index test: PASSED
	
	// Set the temp node at the beginning of the list at search index
	temp2 = hd[hash_idx];
	// printf("[search] temp2 linked to hashtable\n");

	// Scan the list, if temp matches input then return temp
	while (temp2 != NULL) {
		// printf("[search] entered comparing loop\n");
		// printf("[search]\treceived user_input: %s\n", w);
		// printf("[search]\ttarget: %s\n", temp2->word);
		if (!strcmp((char*)w, (char*)temp2->word)) {
			// printf("[search] user_input: matched\n");
			// this line not printed => not meet if condition
			return temp2;
		}
		// printf("[search] Result of strcmp: %d\n", strcmp((char*)w, (char*)temp2->word));

		temp2 = temp2->next;
	}

	// printf("[search] cannot find in search_word\n");		// bug here
	// If still cannot find => no exist => return NULL
	return NULL;
}

// Function to read the input file and get the meaning of the word
int get_meaning (char *buf, struct Word *wobject, FILE *dict_file) {
	// Init a line count variable
	unsigned int n_line = 0;

	// While it is not EOF => go down to offset line
	while (fgets(contents, MAX_LEN, dict_file) != NULL) {
		if (n_line == wobject->offset) {

			// Copy content to buffer and quit
			// the first 'tab' is ignored
			strcpy(buf, contents + 1);
			return 1;
		}
		if (strstr(contents, LINE_FLAG)) {
			n_line ++;
		}
	}
	// if EOF were reached
	return 0;	
}
//////////////////////////////////////////////////////////////////////////////////

