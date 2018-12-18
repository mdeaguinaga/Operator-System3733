#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "myio.h"
/***************************************************************
 * Function: ReadInteger
 * Usage: i = ReadInteger();
 * ReadInteger reads a line of text from standard input and scans
 * it as an integer.  The integer value is returned.  If an
 * integer cannot be scanned or if more characters follow the
 * number, the user is given a chance to retry.
 ***************************************************************/

int ReadInteger(void){
    char *input = NULL;     // variable for input
    char *charptr;          // variable for charaxter
    size_t inputSize;       // size of input
    ssize_t charsRead = 0;  // size for string
    int ifinal;         // variable for value
    
    // printing information
    printf("Enter an integer: ");
    
    // while loop that will occure to read the input
    while((charsRead = getline(&input, &inputSize, stdin)) > 0){
        int stop = 0;
        int i;
        for(i = 0; i < charsRead; i++){
            if(input[charsRead - 1] == '\n'){
                input[charsRead - 1] = '\0';
                charsRead--;
            }
            //check if they're all digits
            if(isdigit(input[i]) || input[i] == '\0') {
                continue;
            }else{
                stop = 1;
                break;
            }
        }
        //if something fails, prompt user again for an integer
        if(stop == 1){
            fprintf(stderr, "Not valid, please enter an integer: ");
            continue;
        }
        
        // converts to integer and assign the value to finalvalue
        ifinal = (int)strtol(input, &charptr, 10);
        free(input);
        return ifinal;
    }
}

/***************************************************************
 * Function: ReadDouble
 * Usage: x = ReadDouble();
 * ReadDouble reads a line of text from standard input and scans
 * it as a double.  If the number cannot be scanned or if extra
 * characters follow after the number ends, the user is given
 * a chance to reenter the value.
 ***************************************************************/

double ReadDouble(void){
    char *input = NULL;     // variable for input
    char *charptr;          // variable for charactes
    size_t inputSize;       // size of input
    ssize_t charsRead = 0;  // size of array
    double dfinal;          // value that will be retuned
    
    printf("Enter a double: ");
    
    // while loop that will occure wile the information is entered
    while((charsRead = getline(&input, &inputSize, stdin)) > 0){
        int stop = 0;
        int periodCount = 0;
        int i;
        for(i = 0; i < charsRead; i++) {
            if (input[charsRead - 1] == '\n') {
                input[charsRead - 1] = '\0';
                charsRead--;
            }
            //check for how many periods, we only want one
            if (input[i] == '.') {
                periodCount++;
                if(periodCount > 1){
                    stop = 1;
                    break;
                }
                
            }
            //check if they're all digits
            if (isdigit(input[i]) || input[i] == '\0' || input[i] == '.') {
                continue;
            } else{
                stop = 1;
                break;
            }
        }
        //if something fails, prompt user again for a double
        if(stop == 1 || periodCount == 0){
            fprintf(stderr, "Not valid, please enter a double: ");
            continue;
        }
        
        dfinal = strtod(input, &charptr);
        free(input);
        return dfinal;
    }
}


/***************************************************************
 * Function: ReadLine
 * Usage: s = ReadLine();
 * ReadLine reads a line of text from standard input and returns
 * the line as a string.  The newline character that terminates
 * the input is not stored as part of the string.
 ***************************************************************/

char *ReadLine(void){
    printf("Enter some text: ");
    
    // returning the info that ReadLineFile function returnes
    return (ReadLineFile(stdin));
}

/***************************************************************
 * Function: ReadLine
 * Usage: s = ReadLine(infile);
 * ReadLineFile reads a line of text from the input file which
 * is already open and pointed by infile. It then reads the line,
 * dynamically allocates space, and returns the line as a string.
 * The newline character that terminates the input is not stored
 * as part of the * string.
 * The ReadLine function returns NULL if infile is at the
 * end-of-file position.
 ***************************************************************/

char *ReadLineFile(FILE *infile){
    
    char *input = NULL;     // input character
    size_t inputSize;       // size of input
    ssize_t line;           // size of array
    
    // reading input
    line = getline(&input, &inputSize, infile);
    
    if(input[line - 1]  == '\n'){
        input[line - 1] = '\0';
    }
    return input;
    
}

