#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#include <os_project.h>

#define max_length 512


int  parse_func(char *commandLine, char **commands, const char *delim){

	/* This function returns the number of parses of the string named commandLine, 
	by the delim connst character.For every delim char in the string, the strtok 
	function parses the string into tokens and every token is stored in a different 
	place in the commands table. */
	
	char *token;	
	token = strtok (commandLine, delim);
	int i = 0;																	// contains the number of commands entered in the commandline
	while (token != NULL) {		
		commands[i]=token;
		token = strtok (NULL, delim);
		 i++;
	} 
	commands[i]=NULL;															// make sure that the string ends with a null character
	return i;
}

char *strstrip(char *s){

/*	This function "clean" the string s from the white-space character 
	that might exist in the beginning or the end of it. */
	
    size_t size;
    char *end;

    size = strlen(s);

    if (!size)
        return s;

    end = s + size - 1;															// the end pointer will contain the address of the string's final character 
    while (end >= s && isspace(*end))  											// isspace() checks if a character is a white-space one
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;

    return s;
}


int checkCommand_func (char *args){

/* chechCommand_func is created in order to check if the given command 
	is a quit or an exit command*/

	if ((strcmp(args, "quit") == 0) || (strcmp(args, "exit") == 0) || (strcmp(args, "QUIT") == 0) || \
	(strcmp(args, "EXIT") == 0) || (strcmp(args, "Quit")== 0) || (strcmp(args, "Exit") == 0) ){
		return 1;	
	} 
	return 0;
}
