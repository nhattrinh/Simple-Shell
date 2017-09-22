#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAXLINE 80

char * readInput(){
    char * input;
    char buffer[256];
    
    input = fgets(buffer,256,stdin);
    return input;
}

int main(void){
    char *args[MAXLINE/2 + 1];
    int should_run = 1;
    printf("CS149 Shell from Nhat Trinh\n");
    while(should_run){
        printf("Nhat-645> ");
        fflush(stdout);
        char * userInput = readInput();
        char * ptr;
        int numOfChars = 0;
        // begin parameterizing user arguments
        while (*userInput != '\0'){
            if (*userInput > 'a' && *userInput < 'Z'){
                
            }
            else if (*userInput == ' '){
                
            }
            
        }
        // end parameterization of user arguments
    }
}