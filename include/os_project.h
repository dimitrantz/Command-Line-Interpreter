/* allocates the memory needed for the multiple commads and calls the parce_func() and the execute_func() */
void myShell_func(char *commandLine);

/* parse the commandLine into commands using the delim character and return the number of parses */
int  parse_func(char *commandLine, char **commands, const char *delim);

/* remove the white-space characters from the beginning and the ending of a string */
char *strstrip(char *s);

/* check if the command is quit or exit */
int checkCommand_func (char *args);

/* execute the commands in parallel by multiple children */
void  execute_func(char **commands, int numCom);
