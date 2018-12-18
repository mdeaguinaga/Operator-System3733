#include <stdio.h>
#include <stdlib.h>
#include "pslibrary.h"

/*************************************************
* This program takes exactly 7 integer command
* line parameters. It should check for the correct
* number of command line parameters, assume that
* all are integers, and then it willprint a line 
* containing your my name and a line containing
* the values of the parameters.
*
**************************************************/

int main(int argc, char *argv[]) {
   int iTotal;
   char *heading;
   char *s1, *s2;
   int iNumb[8];
   int i;
   
   if (argc != 8) {
      printf("Incorrect invocation %s.", argv[0]);
      printf("\nRun the program again and enter 7 integers, Example:"); 
      printf("\n\n\t ./assign1 0 2 4 6 7 8 9\n\n");
      exit(0);
   }
   for(i = 0; i<8; i++){
        iNumb[i] = atoi(argv[i]); 
   }
    
   printf("Assignment 1 program was written by Manuel I. De Aguinaga\ninputs:");
   
   
   for(i = 1; i<8; i++){
        printf(" %d",iNumb[i]);
        iTotal += iNumb[i];
   }

   printf("\n");

    for(i = 2; i<8; i++){
        iTotal += iNumb[i];
    } 
    
   if ((s1 = malloc(iTotal)) == NULL || (s2 = malloc(iTotal)) == NULL) {
      printf("Not enough memory\n");
      exit(2);
   }
   
   heading = "Part 0\n";
   
   part0(s1, s2);
   display(heading, s1, s2);
   
   return 0;
}
