#include <stdio.h>
#include <string.h>

/**

**/
void part0(char *s1, char *s2) {
   char *p0str1 = "RRwwwwwRRRRRRRRR";
   char *p0str2 = "rrRRRRwwwwwwwwrrRRRRRRR";
   
   memcpy(s1, p0str1, 17);
   memcpy(s2, p0str2, 24);


   return;
}


/**
Print a blank line to standard output.
Print the heading.
Print the first string on its own line.

The first string is the second parameter to display. 
You may assume that the heading ends with a new line
so that the first string is printed at the start of 
a line. After printing this string, print a newline so 
that next string starts directly below it.

Print the second string on its own line.
After writing the string to standard output, output a newline.
Print 4 numeric values all on a single line, separating consecutive 
values with a single blank.
The number of 'r' characters in the second parameter.
The number of 'r' characters in the third parameter.
The average of these two number, displayed with one decimal place.
A floating point number number displayed with 5 decimal places. 
This values is the total number of 'R' characters in the second 
and third parameters divided by the length of the longer of these two parameters.
Run Part 0 and save the output generated as output-part0.txt 

**/

void display(char *heading, char *s1, char *s2) {
   int length, l1, l2, r1, r2, totR, x; // initialising variables that will be used
   
   printf("\n%s", heading); //prints Heading
   printf("%s\n", s1);      //prints the prosses 1
   printf("%s\n", s2);      //prints the prosses 2
   
   // set variables to zero
   l1 = 0;
   l2 = 0;
   r1 = 0;
   r2 = 0;
   totR = 0;
   
   x = 0;   //sets x to zero
   // add one to the process if is ready otherwise add 1 to CPU
   while (s1[x] != '\0') {
      if (s1[x] == 'r')
         r1++;
      else if (s1[x] == 'R')
         totR++;
      l1++;
      
      x++;
   }
   
   x = 0;   //sets x to zero
   while (s2[x] != '\0') {
      if (s2[x] == 'r')
         r2++;
      else if (s2[x] == 'R')
         totR++;
      l2++;
      
      x++;
   }
   
   if (l1 > l2)
      length = l1;
   else
      length = l2;
   
   printf("%d ", r1);
   printf("%d ", r2);
   printf("%.1f ", (double)(r1+r2)/2);
   printf("%.5f\n", (double)totR/length);
}



/**
    Function that insertready depending the arguments
    that were passed
**/
void insert(char *s, int pos, char rep) {
   int x, len;
   if (s == NULL)
      printf("Passing null to strlen\n");
   len = strlen(s);
   
   for (x = len; x >= pos; x--)
      s[x+1] = s[x];
   s[pos] = rep;
}


/**
Takes two string parameters and 6 integer parameters. 
It fills in the strings for the first two parameters as
described as follows. Suppose the function is called with
fcfsa(s1, s2, x1, y1, z1, x2, y2, z2);
The first string, s1, will consist of a x1 R's, followed 
by y1 w's, followed by 0 or more r's, followed by z1 R's.    
**/
void fcfsa(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
   int x, s1l, s2l;
   
   s1l = x1+y1+z1;      //variable for prosses one
   s2l = x1+x2+y2+z2;   //variable for process two

   x = 0;               //setting x iqual to zero

   // checking for the Running CPU prosses 1
   while (x != -1) {
      if (x1 != 0) {
         s1[x] = 'R';
         s2[x] = 'r';
         
         x1--;
      }
      
      // I/O for prosses 1 and and CPU
      else {
         if (y1 != 0) {
            s1[x] = 'w';
            y1--;
         }
         else if (z1 != 0) {
            s1[x] = 'R';
            z1--;
         }
         else if (z2 == 0)
            x = -2;
         
         
         if (x2 != 0) {
            s2[x] = 'R';
            x2--;
         }
         else if (y2 != 0) {
            s2[x] = 'w';
            y2--;
         }
         else if (z2 != 0) {
            s2[x] = 'R';
            z2--;
         }
         else if (z1 == 0)
            x = -2;
      }
      x++;
   }
   
   s1[s1l] = '\0';
   s2[s2l] = '\0';
   
   x = 0;
   // Ready status for prosses 1 and prosses 2
   while(s1[x] != '\0' && s2[x] != '\0') {
         if (s1[x] == 'R' && s2[x] == 'R') {
            if (s2[x] == s2[x-1])
               insert(s1, x, 'r');
            else
               insert(s2, x, 'r');
         }
         x++;
     }
}
