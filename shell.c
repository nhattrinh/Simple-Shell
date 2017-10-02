/*
Student: Nhat Trinh
Class:	CS 149 Fall 2017
SID:	011227645
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include<sys/types.h>
#define MAXLINE 80

//function to read user input and return a pointer to char array
char * readInput(){
    // declare pointer to input
    char * input;
    // declare char buffer for fgets()
    char buffer[300];
    
    // set input pointer to what fgets() returns
    input = fgets(buffer,500,stdin);
    return input;
}

int main(void){
    // array to be inserted into excecvp()
    char *args[MAXLINE/2 + 1];
    int should_run = 1;
    
    // print only once the message
    printf("CS149 Shell from Nhat Trinh\n");
    while(should_run){
        // print the cli interface message
        printf("Nhat-645>");
        fflush(stdout);
        
        // boolean to let parent process wait for child process
        // default is true
	int parentWait = 1;
        // walker to 
	int argsIndex = 0;
        
        // userInput is the input read from the command line
        char * userInput = readInput();
        
        // fgets() in readInput() returns a string ..
        // .. with a trailing newline, strchr removes that newline
        char * nl = strchr(userInput,'\n');
        if (nl != NULL)
            *nl = 0;
        
        //tokenize the user input based on spaces
        char * charTokens = strtok(userInput," ");
        
        // strchr() gets rid of the newline that strtok() puts
        // strchr() returns a pointer to where the character is
        // then assign the character with a string terminator
        nl = strchr(charTokens,'\n');
        if (nl != NULL)
            *nl = 0;
        
        // after removing newline from tokenized char
        // assign the token to the args array
        args[argsIndex++] = charTokens;
        while (charTokens != 0){
            /* while charTokens is not NULL
             * tokenize using strtok()
             * assign token to args[] with argsIndex
             */
            charTokens = strtok(NULL," ");
            args[argsIndex++] = charTokens;
        }
        
        // if user specifies ampersand behind the command, parent process does not wait for child to exit
        if (*args[argsIndex - 2] == '&'){
            parentWait = 0;
            args[argsIndex - 2] = NULL;
            args[argsIndex - 1] = NULL;
        }
        
        // terminate the array with a NULL index, as needed by exec() system call
        //args[argsIndex] = (char *)0;
        
        // fork() creates a copy of the parent process
        // and fork() returns a pid of type pid_t
        pid_t pid = fork();
        // status to be read by parent process from child
        int * status;
        
        // parent process gets in this block and wait
        if (pid > 0 && parentWait){
            wait(status);
            if (*status > 256)
                should_run = 0;
        }
        
        // child process gets in this block and execute command
        else if (pid == 0){
            // since exit is a builtin bash command
            // this command must be built into this shell
            if (strcmp(args[0],"exit") == 0)
                exit(-1);
            
            // if execvp() returns -1 then that means command not found/valid
            // post EXIT_FAILURE status for parent process to see
            else if (execvp(args[0],args) == -1){
                printf("Unable to execute your command.\n");
                exit(EXIT_FAILURE);
            }
            
            // if execvp() system call successful, post EXIT_SUCCESSFUL status
            // .. for parent to see
            exit(0);
        }
        
        // if pid_t pid is not greater or equal to zero ..
        // parent has not created a child process
        else if (pid < 0)
            printf("Unable to create child process.\n");
    }
    return 0;
}
