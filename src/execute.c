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


void  execute_func(char **commands, int numCom)
{

/* This function creates as many children as needed in order to execute
	each command seperately. Every child has to execute a command. 
	Every time, the shell checks if there is a quit command entered. If so, 
	the child process communicates with the parent process through a pipeline*/


    pid_t pid;
    int status,i,numArgs, signalReceiv, pd[2];
	char *buf= "The command is quit. \n";
	char readbuf[max_length];
	
	signalReceiv= getpid(); 											// pid of the parent process
	
	if (pipe(pd) < 0) perror ("Fail: pipeline cannot be opened \n");
	
	for ( i=0; i<numCom; i++) {
		
		if ((pid = fork()) < 0) {    
			perror("fork");
			exit(EXIT_FAILURE);   
		} 
		
		if (pid == 0) {
			
			int flagQuit, index=i;
			char *args[max_length];   									// arguments for the execvp function
				
			commands[index] = strstrip (commands[index]);
			
			numArgs=parse_func(commands[index], args," ");

			flagQuit = checkCommand_func (* commands);						// check if there is a quit command
			
			if (flagQuit !=0){
			
				close(pd[0]); 											// close the read end 
				write(pd[1], buf, (strlen(buf)+1)); 
				close(pd[1]);  											// close the write end 
				
				exit(0);	
			}	
			close(pd[0]);									 			// close the read end 
			close(pd[1]); 												// close the write end 
				
			if (execvp(*args, args) < 0) {   							// if the command is not quit, it is executed by execvp  
				perror("Child process could not do execvp");
				exit(EXIT_FAILURE);
			}	
			
			exit(EXIT_FAILURE); // further check
		}
	}
	
	if (pid > 0) {   													// parent process
        while (wait(&status) != pid)   									// wait for completion 
            ;
			
		close(pd[1]);													// close the write end 
		if ( read(pd[0], readbuf, max_length) > 0) {
			close(pd[0]); 												// close the read end 
			printf("A quit command was entered. \nThe shell will be now terminated.\n");
			exit(0);
		}else{
		close(pd[0]); 													// close the read end 
		
		}
    }
		
    
}

void myShell_func(char *commandLine){

/*	This function creates a double pointer in which the multiple 
	(if there are more than one) commands will be stored. Firstly, 
	the parsing takes place and then the execute function is called
	for running the commands. */
	
			char **commands;  											// store the commands entered in command line 
			int numCom;
			
			commands=(char**)malloc(sizeof(char*)*max_length);			// allocate memory so as to parse the commands entered
			numCom = parse_func(commandLine, commands,";");   			// parse the command line to commands 
			if (numCom!=0) execute_func(commands, numCom);   			// execute the commands 	
			
			free(commands);												// free the table of the commands entered
}

