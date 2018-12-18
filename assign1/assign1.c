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
   int iTotal;      //variable for total input
   char *heading;   //String for heading
   char *s1, *s2;   //proses 1 and 2
   int iNumb[8];    //Array for inputs
   int i;           //variable for the forloop
   
   // Error for incorrect input
   if (argc != 8) {
      printf("Incorrect invocation %s.", argv[0]);
      printf("\nRun the program again and enter 7 integers, Example:"); 
      printf("\n\n\t ./assign1 0 2 4 6 7 8 9\n\n");
      exit(0);
   }

   // Forloop that assign valuesto array
   for(i = 0; i<8; i++){
        iNumb[i] = atoi(argv[i]); 
   }

   // Print the autor's name
   printf("Assignment 1 program was written by Manuel I. De Aguinaga\ninputs:");
   
   // Print the inputs
   for(i = 1; i<8; i++){
        printf(" %d",iNumb[i]);
        iTotal += iNumb[i];
   }

   // New line
   printf("\n");

   // Creating memory allocation for s1 and s2
   if ((s1 = malloc(iTotal)) == NULL || (s2 = malloc(iTotal)) == NULL) {
      printf("Not enough memory\n");
      exit(2);
   }

   //Heading that will be printed
   heading = "Part 1\n";

   // Calling fcfsa function
   fcfsa(s1, s2, iNumb[2], iNumb[3], iNumb[4], iNumb[5], iNumb[6], iNumb[7]);

   // Calling display function
   display(heading, s1, s2);
   
   return 0;
}
