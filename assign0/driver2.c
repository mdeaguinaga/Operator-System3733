#include <ctype.h>
#include <stdio.h>
#include "myio.h"
/***********************************************************
 *  gets two command-line arguments: a text file containig
 *  many lines. Reads each line and removes the extra space
 *  characters between the words and prints the new line into
 *  output_file.txt. So there will be at most one space character
 *  between the words in output_file.txt.
 * @param argc
 * @param argv
 * @return
 **********************************************************/

int main(int argc, char *argv[]) {
    
    if(argc != 3){
        fprintf(stderr, "requires input and output file");
    }
    
    // variables that will be used
    FILE *file;                     // file to be reader
    FILE *file2;                    // file to be created
    char *line;                     // line that is being input
    char *outLine;                  // data that will be output
    int true = 1;                   // boolean integer
    
    // opening file that will be readed
    file = fopen(argv[1], "r");
    
    // opening files that will be writhed
    file2 = fopen(argv[2], "w");
    
    // loop that will be occurring until true become 0
    while(true){
        line = ReadLineFile(file);
        outLine = line;
        int i = 0;      // variable for array
        int j = 0;      // variable for array
        
        // while loop that will be reading the input and will
        // be cheking for spaces
        while(line[i] != '\0'){
            i++;    // adding 1 to i
            // if statement that will be checking for spaces
            if((line[i] == ' ') && (line[i - 1] == ' ')){
                continue;
            }
            
            j++;    // adding 1 to j
            outLine[j] = line[i];
        }
        outLine[j] = '\0';
        fprintf(file2, "%s\n", outLine);
        // if file finish the wile loop will be finished
        if(feof(file)) {
            break;
        }
    }
    
    fclose(file);       // closing file for input
    fclose(file2);      // closing file for output
}
