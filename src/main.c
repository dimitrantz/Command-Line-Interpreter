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

int  main(int argc, char *argv[])
{
    char commandLine[max_length];   									// the user's input                  
    
	if (argc == 1) {   													// interactive mode
	
		while (1) { 
			
			printf("ntzioni_8209>");  									// display my prompt 

			if (gets(commandLine)==NULL) {   							// read in the command line from keyboard
				printf("\n");
				exit(EXIT_FAILURE);
			}
			myShell_func(commandLine);
		}
	 
	} else if (argc == 2) {  											// batch mode
		
		FILE * fp;
		fp = fopen (argv[1], "r");
		
		if (fp == NULL) {
			perror("Fail: fopen \n");
			exit(EXIT_FAILURE);
		}
		
		fseek (fp, 0, SEEK_END);   									    // moves to the end of file
		if (ftell(fp) == 0) {
			fprintf(stderr, "Empty batchfile\n");
			exit(0);
		}	
		fseek (fp, 0, SEEK_SET);										// moves to the beginning of the file
		
		while (fgets(commandLine, (max_length+1), fp)) {						
			
			if(strlen(commandLine) == (max_length+1)) {
			perror("The size of the line is exceeding the maximum length. \n . The shell will be now terminated. \n");
			exit(0);
			}
			
			myShell_func(commandLine);
		}
		
		fclose(fp);
		printf("The batchfile has no more commands. The shell will now be terminated. \n");
		
		 
	}
	
	return 0;
}







