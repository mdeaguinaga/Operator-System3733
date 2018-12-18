#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "myio.h"
/***********************************************
 Gets three command-line arguments: x y z.  It
 then asks user to enter x many integers, y many
 doubles, and z many lines. Everytime the program
 prints back the entered data on the stdout while
 printing error messages on stderr (if any). It also
 keeps track of the largest integer, double and the
 longest string. At the end, your program prints
 the largest intiger, double and the longest line
 .string that were entered.
 **********************************************/

int main(int argc, char *argv[]) {
    
    if(argc != 4){  // if statement that will check for wrong input
        fprintf(stderr, "Enter 3 command when runnin the program \n\n\t(example: ./driver1 5 3 4) \n\n1st command is for integers, 2nd command is for doubles and 3th command is for strings\n\n\tPLEASE TRY AGAIN\n\n");
    }
    
    // variables that will be getting the data
    int ints = atoi(argv[1]);       // int that comes from argv
    int doubles = atoi(argv[2]);    // double that comes from argv
    int lines = atoi(argv[3]);      // string that comes from argv
    int iArray[ints];               // int array
    int iIargest;                   // largest integer
    int x , i, j;                   // variables for for loops
    double dArray[doubles];         // array for double
    double dlargest;                // largest double
    char *s[lines];                 // string array
    char *longestString;            // longest String
    
    //for loop that will go through the integer array
    for(x = 0; x < ints; x++){
        iArray[x] = ReadInteger();
        printf("%d\n", iArray[x]);
    }
    iIargest = iArray[0];
    
    //for loop that checks fot the bigest value
    for (i = 1; i < ints; i++) {
        if (iIargest < iArray[i]) {
            iIargest = iArray[i];
        }
    }
    
    x = 0;  // bting x back to 0
    
    // for loop that will go trough all doubles
    for(x = 0; x < doubles; x++){
        dArray[x] = ReadDouble();
        printf("%.2f\n", dArray[x]);
    }
    dlargest = dArray[0];
    i = 1;
    
    // for loop that will check for the bigest value
    for (i = 1; i < doubles; i++)
    {
        if (dlargest < dArray[i]) {
            dlargest = dArray[i];
        }
    }
    
    // for loop that will be reading trough all the line
    for(j = 0; j < lines; j++){
        s[j] = ReadLine();
        printf("%s\n", s[j]);
    }
    longestString = "";
    i = 1;
    
    // for loop that will check for the longest string
    for(i = 1; i < lines; i++){
        if(strlen(longestString) < strlen(s[i])){
            longestString = s[i];
        }
    }
    
    // print the information once it was analyzed
    printf("\nlargest integer is %d\n", iIargest);
    printf("largest double is %.2f\n", dlargest);
    printf("longest string is %s\n", longestString);
}
