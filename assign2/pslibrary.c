#include <stdio.h>
#include <string.h>

#define READY  0
#define RUNNING  1
#define WAITING  2
#define DONE  3

static char stateChars[] = {'r','R','w',0};

/*  1) handle state changes:
        running process completes CPU burst
        running process has quantum expire
        IO complete
    2) do context switch if necessary
        both ready
        one ready and CPU free
    3) append appropriate characters to character arrays
        avoid putting in multiple string terminators
*/
/* assume s1 and s2 point to buffers with enough space to hold the result */
/* assume that the int parameters are strictly greater than 0 */

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
    Function that insert 
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


void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
            }  
        else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0) {
                state2 = DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = WAITING;
        }  
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }  
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }  
        /* if both ready, depends on algorithm */
        if ((state1 == READY) && (state2 == READY)){ 
            state1 = RUNNING;
        }  
        /* handle one ready and CPU available */
        else if ((state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
        }  
        else if ((state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
        }  
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
        }/* end of main for loop */
}

void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
            }  
            else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
                if (ioLeft2 == 0) {
                    state2 = DONE;
                    s2[i] = stateChars[state2];
                }
                else
                    state2 = WAITING;
            }  
            /* handle IO complete */
            if ((state1 == WAITING) && (ioLeft1 == 0)) {
                state1 = READY;
                cpuLeft1 = z1;
            }  
            if ((state2 == WAITING) && (ioLeft2 == 0)) {
                state2 = READY;
                cpuLeft2 = z2;
            }  
            /* if both ready, depends on algorithm */
            if ( (state1 == READY) && (state2 == READY)) {
                if (cpuLeft1 <= cpuLeft2)
                    state1 = RUNNING;
                else
                    state2 = RUNNING;
            }  
            /* handle one ready and CPU available */
            else if ( (state1 == READY) && (state2 != RUNNING)) {
                state1 = RUNNING;
            }  
            else if ( (state2 == READY) && (state1 != RUNNING)) {
                state2 = RUNNING;
            }
            /* insert chars in string, but avoid putting in extra string terminators */
            if (state1 != DONE)
                s1[i] = stateChars[state1];
            if (state2 != DONE)
                s2[i] = stateChars[state2];
            /* decrement counts */
            if (state1 == RUNNING)
                cpuLeft1--;
            if (state1 == WAITING)
                ioLeft1--;
            if (state2 == RUNNING)
                cpuLeft2--;
            if (state2 == WAITING)
                ioLeft2--;
        }                                               /* end of main for loop */
    }

void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
        }  
        else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0) {
                state2 = DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = WAITING;
        }  
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }  
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }  
        /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY)) {
            if (cpuLeft1 <= cpuLeft2)
                state1 = RUNNING;
            else
                state2 = RUNNING;
        }
        /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
        }  
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
        }
        /* handle preemption */
        else if ( (state1 == READY) && (cpuLeft1 < cpuLeft2)) {
            state2 = READY;
            state1 = RUNNING;
        }
        else if ( (state2 == READY) && (cpuLeft2 < cpuLeft1)) {
            state1 = READY;
            state2 = RUNNING;
        }
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    }   /* end of main for loop */
}

void rr(char *s1, char *s2, int q, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
    int qleft;                                         /* quantum remaining */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
        }  
        else if ((state2 == RUNNING) && (cpuLeft2 == 0)) {
            if (ioLeft2 == 0) {
                state2 = DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = WAITING;
        }  
        /* running process has quantum expire */
        if ((state1 == RUNNING) && (qleft == 0) ) {
            state1 = READY;
            qleft = q;
            if (state2 == READY)
                state2 = RUNNING;
        }  
        if ((state2 == RUNNING) && (qleft == 0) ) {
            state2 = READY;
            qleft = q;
            if (state1 == READY)
                state1 = RUNNING;
        }  
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }  
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }  
        /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY)) {
            state1 = RUNNING;
            qleft = q;
        }  
        /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
            qleft = q;
        }  
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
            qleft = q;
        }  
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        qleft--;                   /* OK to decrement even if nothing running */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    }   /* end of main for loop */
}

