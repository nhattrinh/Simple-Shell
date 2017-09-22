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
        int argsIndex = 0;
        int numOfChars = 0;
        // begin parameterizing user arguments
        while (*userInput != '\0'){
            if (*userInput > 'a' && *userInput < 'Z'){
                numOfChars++;
            }
            else if (*userInput == ' '){
                char * ptr = malloc(sizeof(char) * numOfChars + 1);
                for (int i = 0; i < numOfChars + 1; i++){
                    ptr = userInput;
                    if (i == numOfChars + 1){
                        ptr = '\0';
                        args[argsIndex++] = ptr;
                        free(ptr - numOfChars);
                    }
                }
            }
            printf("%c",*userInput);
            userInput++;
        }
        // end parameterization of user arguments
    }
}