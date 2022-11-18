//////////////////////////////////////////////////
//						//
//	The source of main program is put here	//
//						//
//////////////////////////////////////////////////

#include"util.h"
#include"hashtable.h"

char contents[MAX_LEN];

int main (void) {
	FILE 		*file_in, *file_out;
	char		buffer[MAX_LEN];
	char		temp[MAX_LEN];
	char	 	user_input[30];
	unsigned int 	line_num = 0;

	// Open file
	file_in = fopen("dictionary.txt", "r");
	// printf("this\n"); // ckdump: passed
	// If dictionary file were unavailable
	if (file_in == NULL) {
		printf("Dictionary file cannot be open");
		return -1;
	}

	// printf("this\n"); // ckdump: passed => No problems with file_in
	// Read file content
	// When it is not EOF
	while (fgets(contents, MAX_LEN, file_in) !=NULL) {

		// When encounter #, split contents at the newline character
		if (strstr(contents, WORD_FLAG)) {
			strtok(contents, LINE_FLAG);
			
			// Copy word name to temp (ignore '#')
			strcpy(temp, contents + 1);
			// printf("Temp: %s\n", temp);
			// Check dump: passed; check contents of temp: passed

			// Create new word via name in temp
			struct Word *new_word = create_word(temp, line_num + 1);
			//printf("[main] new_word is created successfully\n");
			//printf("\tWord name: %s\n", temp);		
			//printf("\tOffset in file: %d\n", line_num + 1);

			// Saving words to linked-list
			insert_word(hashdict, new_word);
			//printf("[main] word inserted\n"); //ckdump: passed 	
		}

		// Continue going down the file
		line_num++;
	}
	fclose(file_in);
	// Get user input
	printf("\n======================================================\n");
	printf("Hi sir! Please put the word you wanna search here: ");
	scanf("%s", user_input);
	// fgets(user_input, 30, stdin);
	// fgets(user_input, sizeof(user_input), stdin);
	// printf("[main] user_input: %s\n", user_input);
	// user_input checked: OK

	// Search input in dict_file
	struct Word *result = (struct Word*)malloc(sizeof(struct Word));
	result = search_word(hashdict, (unsigned char*)user_input);

	// Word not found => error warning => end app.
	if (result == NULL) {
		printf("Sorry. Your input is not contained in our dictionary.\nPlease try again later.\n");
		return -1;
	}
	// Word found => get meaning => display
	file_out = fopen("dictionary.txt", "r");
// check dump
	get_meaning((char *)buffer, result, file_out);
	printf("\n...\n");
	printf("In our dictionary, %s means %s", user_input, buffer);
	printf("Thank you for using the app!\n");
	// printf("Farewell!\n");
	fclose(file_out);
	return 0;
}


