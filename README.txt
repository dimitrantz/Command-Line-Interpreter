# My_Shell  
Operating System Project (7th semester Oct 2016 - Jan 2017)

version 1.0 last update: 20/1/2017

Aristotle University of Thessaloniki
Electrical and Computer Engineering Science
-----------------------------------------------------------------------------------------------------

My_Shell - Operating System Project 2016-2017 is an effort to implement a shell or a command line 
interpreter. This shell is made to work in interactive and in batch mode both and it is up to the 
user to choose between these two modes. The programming language is C. 


## Code Files

Containing files in OS_project.rar: 
 
Makefile for compiling the code, 
os_project.h (/include), 
main.c (/src), execute.c (/src), helpers.c (/src),
batchfile.bat (/bin)


## Files' analysis

os_project.h: It is a header that contains all the functions used in this program except main().


main.c: 
	int  main(int argc, char *argv[]);
	** In this function, the program differentiates the two modes (interactive, batc) and 
	then the appopriate functions are called.

	- interactive mode: the user enters the commands from keyboard 
	( Ability to enter more than one at a time using ';' to separate them )
	- batch mode: the user writes the commands in a batch file and then enters this file to 
	be executed.


execute.c:
	It includes the main functions to run the commands entered.

	
	void myShell_func(char *commandLine);
	** This function creates a double pointer in which the multiple (if there are more) 
	commands will be stored. Firstly, the parsing takes place and then the execute function 
	is called for running the commands.


	void  execute_func(char **commands, int numCom);
	** This function creates as many children as needed to execute	each command 
	separately. Every child has to execute a command. Every time, each child parses the 
	command at " " and checks if there is a quit command entered. If so, the child process 
	communicates with the parent process through a pipeline. Otherwise the execvp() is called.

helpers.c: 
	This code file contains some helpful functions for the commands' execution.

	int  parse_func(char *commandLine, char **commands, const char *delim);
	** This function returns the number of parses of the string named commandLine, by the delim 
	connst character.For every delim char in the string, the strtok function parses the string 
	into tokens and every token is stored in a different place in the commands table.


	char *strstrip(char *s);
	** This function "clean" the string s from the white-space character that might exist in the
	beginning or the end of it.


	int checkCommand_func (char *args);
	** This function is created in order to check if the given command is a quit or an exit 
	command.


## Compile-Run


In order to compile and run this project, a Linux terminal is needed. Follow the steps below to run 
the My_Shell project.

Step 1: extract all the directories and files in a directory on your PC
Step 2: open a Linux terminal
Step 3: enter the 'cd' command and type the directory's path where you extracted the files
Step 4: enter the command 'make' to the command line 
	**In that step the object files( main.o, execute.o, helpers.o ) will be created automatically 
	in the build directory and the executable file ( My_Shell.exe ) in the bin directory
Step 5: enter 'cd bin' to the command line
Step 6: type ./My_Shell.exe to run the program in interactive mode OR
	./My_Shell.exe batchfile.bat to run the program in batch mode

## Author: Ntzioni Dimitra
Academic ID: 8209
Contact info: dntztioni@ee.auth.gr
