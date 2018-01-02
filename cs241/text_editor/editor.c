#include "editor.h"
#include "document.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

char *get_filename(int argc, char *argv[]) {
  if(argc <= 1) {
		return NULL;
	}
  else { 
  	return argv[1];
  }
}


// Handling the p commands
void handle_display_command(Document *document, const char *command) {
  	if(Document_size(document) == 0) {										// If the Document is empty you want to print out an error that nothing is there.
  		print_document_empty_error();
  		return;
  	}
  	if(strlen(command) == 1) {												// Printing out the entire document since at this point the only command will be p
  		size_t i;
  		for(i = 0; i < Document_size(document); i++) {
  			print_line(document, i);
  		}
  	}
  	else {																	// This is now the case of when we need to print at a certain line number.
  		char current_command[10];
  		size_t line_number;
  		size_t i;															// incrementer throughout the entire program.

  		sscanf(command, "%s %zd", current_command, &line_number);			// Breaking up the given input.

  		if(line_number < 1 || line_number > Document_size(document)) {		// Invalid line numbers.
  			invalid_line();
  			return;
  		}
  		if( 5 < line_number) {												// All the various cases that you can have when having to print the 5 lines before and after the specified line number.
  			if(line_number + 5 <= Document_size(document)) {
  				for( i = line_number - 6; i < line_number + 5; i++) {
  					print_line(document, i);
  				}
  			}
  			else {
  				for (i = line_number - 6; i < Document_size(document); i++) {
  					print_line(document, i);
  				}
  			}
  		}
  		else {
  			if(line_number + 5 <= Document_size(document)) {
  				for(i = 0; i < line_number; i++) {
  					print_line(document, i);
  				}
  			}
  			else {
  				for(i = 0; i < Document_size(document); i++) {
  					print_line(document, i);
  				}
  			}
  		}
  	}
	
}

// Handling the w commands
void handle_write_command(Document *document, const char *command) {
	size_t line_number;													// This will store what line number we need to append to.
	char current_command[2];
	char * var;
	size_t i;
	size_t offset;
	offset = 0;
	
	sscanf(command, "%s %zd", current_command, &line_number);			// Scanning the command here and storing into appropiate variables
	
	for(i = 2; i < strlen(command); i++) {								// This is getting the text after the command.
		if(isspace(command[i])) {
			offset = i + 1;
			break;
		}
	}
	var = (char*)malloc(strlen(command)-offset+1);						// This is mallocing according to the string size.
	for(i = 0; i < (strlen(command)-offset); i++) {
		var[i] = command[i+offset];
	}
	var[strlen(command)-offset] = '\0';

	// The following doesn't work for empty cases because I didn't malloc properly.
	// size_t j, i = 0, finalj = 0;													// j is for the command and i is for the variable
	// int flag_to_copy_alpha = 0;											
	// int flag_to_copy_space = 0;
	// for(j = 1; j < strlen(command); j++) {
	// 	if(isalpha(command[j])) {
	// 		flag_to_copy_alpha = 1;
	// 		finalj = j;
	// 	}
	// 	if(isspace(command[j])) {
	// 		flag_to_copy_space = 1;
	// 		finalj = j;
	// 	}
	// 	if(flag_to_copy_alpha && flag_to_copy_space) {
	// 		var[i] = command[j];
	// 		i++;
	// 	}
	// }
	// if(flag_to_copy_space && !flag_to_copy_alpha) {
	// 	for(j = finalj; j < strlen(command); j++) {
	// 		var[i] = command[j];
	// 		i++;
	// 	}
	// }

	if(line_number < 1) {
		invalid_line();
		return;
	}
	
	char* token = strsep(&var, "$");									// This is giving tokens based on what is inbetween each $ because the $ indicates a new line.
	int multiple = 0;													// This is a flag to let us know that we have multiple lines to add in.
	
	for( i = 0; i < strlen(var); i++) {									// Going through the variable that is holding the string and seeing if we have a $ to deal with.
		if(var[i] == '$') {
			multiple = 1;												// Setting the flag that we have multiple lines to handle in the program
		}
	}
	
	Document_set_line(document, line_number-1, token);

	while(var) {
		token = strsep(&var, "$");
		Document_insert_line(document, line_number, token);
		line_number++;
	}
	free(var);

  
}


// Handling the a commands
void handle_append_command(Document *document, const char *command) {
  	size_t linenum;
	char current_command[2];
	size_t offset;
	char * var;

	sscanf(command, "%s %zd", current_command, &linenum);
	
	if(linenum < 1) {													// Checking base case.
		invalid_line();
		return;
	}

	offset = 0;															// Creating an offset by which the content starts at in the command
	
	for(size_t i = 2; i < strlen(command); i++) {
		if(isspace(command[i])) {
			offset = i+1;
			break;
		}
	}
	
	var = (char*)malloc(strlen(command)-offset+1);						// Allocating proper space according to the size of the content.
	
	for(size_t i = 0; i < (strlen(command)-offset); i++) {
		var[i] = command[i+offset];
	}
	
	var[strlen(command)-offset] = '\0';
	
	char* token;
	char* newline;
	
	token = strsep(&var, "$");											// Accounting for multiple lines.
	
	if(linenum-1 >= Document_size(document)) {
		newline = (char*)malloc(strlen(command));						// Allocating space for the new line.
		strcpy(newline, token);
	} else {
		newline = (char*)malloc(strlen(command) + strlen(Document_get_line(document, linenum-1)));
		strcpy(newline, Document_get_line(document, linenum-1));
		strcat(newline, token);
	}
	
	Document_set_line(document, linenum-1, newline);
	
	while(var) {														// Inserting each line by division of $ in the string.
		token = strsep(&var, "$");
		Document_insert_line(document, linenum, token);
		linenum++;
	}
	free(var);
	free(newline);
}


// Handling the d commands.
void handle_delete_command(Document *document, const char *command) {
  	size_t line_number; 												// This will store what the line number is.
	char current_command[10]; 											// This will hold the command that we are executing
	
	sscanf(command, "%s %zd", current_command, &line_number); 			// Scanning the command here
	if(line_number < 1 || line_number > Document_size(document)) {
		invalid_line();
		return;
	}
	Document_delete_line(document, line_number-1);						// Deleting the line from the document and shifts things up by itself
}


// Handling the / commands
void handle_search_command(Document *document, const char *command) {
  	char* var;
  	var = (char*)malloc(strlen(command));								// Allocating space for the content that we are looking for in the program. 
	
	size_t i;
	for(i = 0; i < strlen(command) - 1; i++) {
		var[i]= command[i+1];											// Storing the content in the variable.
	}
	
	var[strlen(command)-1] = '\0';
	
	for (i = 0; i < Document_size(document); i++) {
		char* start = strstr(Document_get_line(document, i), var);
		
		if(start != NULL) {
			print_search_line(i+1, Document_get_line(document, i), start, var);		// Printing the line that has the content we are looking for.
		}
	}
	free(var);
}


// Handling the s commands
void handle_save_command(Document *document, const char *filename) {
  Document_write_to_file(document, filename);							// Simple call to the document write to file.
}
