#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pagetable.h"
#include "phypages.h"
#include "part2.h"

/************************ main *****************************
argv[] contains (accept) the folowing information:
BytesOfPage SizeOfVirtualMemory SizeOfPhysicalMemory SequenceFile. 

First parameter BytesOfPage specifies the number of bytes in 
each physical frame and virtual page. The second parameter 
SizeOfVirtualMemory is the size of virtual memory in bytes. 
The third one SizeOfPhysicalMemory is the size of physical 
memory in bytes. The fourth one SequenceFile is the name 
of the file that contains the sequence of memory access 
logical addresses that need to be translated. 
**********************************************************/
int main(int argc, char *argv[]) {
   int **addrtrans ;
   int *frames;
   int faults, fdin, fdout, frame, lru, nodes;
   unsigned long offset, page, physaddr, virtaddr;
   node* top;
   int bytes, offsetsz, phyframes, physmem, virtmem, virtpages; //part 3 variables
   
   // Checks for correct input
   if (argc != 5) {
      printf("Usage: %s BytesOfPage SizeOfVirtualMemory SizeOfPhysicalMemory SequenceFile \n", argv[0]);
      exit(1);
   }
   // Checks for a valid file 
   if ((fdin = open(argv[4], O_RDONLY)) == -1) {
      perror("Main failed to open sequence file");
      exit(2);
   }
   
   // opens the output for write only and creates the file, therwise
   // it prints an error if it does not creates or opens for write
   if ((fdout = open("output-part3", O_WRONLY | O_CREAT, 0600)) == -1) {
      perror("Main failed to open output file");
      close(fdin);
      exit(2);
   }
   
   // Set the information to be readi to be executed
   bytes = atoi(argv[1]);
   virtmem = atoi(argv[2]);
   physmem = atoi(argv[3]);
   
   offsetsz = floor(log(bytes)/log(2));
   virtpages = virtmem / bytes;
   phyframes = physmem / bytes;
   
   addrtrans = initializeTable(&addrtrans, virtpages);
   frames = initializeFrames(&frames, phyframes);
   faults = 0;
   nodes = 0;
   top = NULL;
   
   // check that while the information still readible, the 
   // wile loop will be continuing
   while (read(fdin, &virtaddr, sizeof(virtaddr)) > 0) {
      printf("Virtual address: %#lx\n", virtaddr);
      
      offset = virtaddr & ((1 << offsetsz) - 1);
      printf("Offset: %#lx\n", offset);
      
      page = virtaddr >> offsetsz;
      
      if (nodes < phyframes - 1 && peer(page, &top) == -1) {
         faults++;
         push(page, &top);
         nodes++;
      }
      else if (nodes >= phyframes - 1 && peer(page, &top) > -1) {
         cut(page, &top);
         push(page, &top);
      }
      else if (peer(page, &top) == -1) {
         lru = cut(-1, &top);
         push(page, &top);
      }
      
      printf("Virtual page: %#lx\n", page);
      
      if (addrtrans[page][1] == v)
         frame = addrtrans[page][0];
      else {
         frame = findOpen(&frames, phyframes);
         if (frame == -1) {
            printf("Page fault\n");
            faults++;
            frame = addrtrans[lru][0];
            addrtrans[lru][0] = -1;
            addrtrans[lru][1] = i;
         }
      }
      
      addrtrans = pointPage(&addrtrans, page, frame);
      
      frames = reverseMap(&frames, frame, page);
      
      page = addrtrans[page][0];
      printf("Physical frame: %#lx\n", page);
      
      physaddr = page << offsetsz;
      printf("Shifted frame: %#lx\n", physaddr);
      
      physaddr += offset;
      printf("Physical address: %#lx\n", physaddr);
      
      tracestack(&top);
      
      // if the information is not writen, it will free the table
      // free the frame and also will free the stack
      if (write(fdout, &physaddr, sizeof(physaddr)) == -1) {
         perror("Main failed to write to output file");
         freeTable(&addrtrans, virtpages);
         free(frames);
         freestack(&top);
         close(fdin);
         close(fdout);
         exit(3);
      }
   }

   // Prints the total pages paults 
   printf("Total page faults: %d\n", faults);
   
   //Free the tables, frame and stack
   freeTable(&addrtrans, virtpages);
   free(frames);
   freestack(&top);
   
   close(fdin);
   close(fdout);
   
   return 0;
}

/******************************* push ******************************
void push(int page, node** top)
void push : adds a node to the top of the stack
parameters:
        int page
        node** top
*******************************************************************/
void push(int page, node** top) {
   if (*top == NULL) {
      *top = malloc(sizeof(node));
      (*top) -> pagenum = page;
      (*top) -> up = NULL;
      (*top) -> down = NULL;
      return;
   }
   node* below = *top;
   *top = malloc(sizeof(node));
   (*top) -> pagenum = page;
   (*top) -> up = NULL;
   (*top) -> down = below;
   below -> up = *top;
}

/******************************* pop ********************************
int pop(node** top)
int pop: returns the top's pagenum and removes it from the stack
parameters:
        node** top
********************************************************************/
int pop(node** top) {
   if (*top == NULL)
      return -1;
   
   int num = (*top) -> pagenum;
   
   if ((*top) -> down == NULL) {
      free(*top);
      return num;
   }
   
   node* temp = *top;
   *top = (*top) -> down;
   (*top) -> up = NULL;
   free(temp);
   
   return num;
}

/******************************* peek *****************************
int peek(node** top)
int peek: returns the top's page
parameters:
        node** top
******************************************************************/
int peek(node** top) {
      return (*top) -> pagenum;
}

/******************************* peer ****************************
int peer(int page, node** top)
int peer: searches the stack for a node with a pagenum of page
parameters:
        int page
        node** top
*****************************************************************/
int peer(int page, node** top) {
   node* cur = *top;
   int ret = -1;
   
   if (*top == NULL)
      return ret;

   do {
      if (cur -> pagenum == page) {
         ret = cur -> pagenum;
         break;
      }
      cur = cur -> down;
   } while (cur != NULL);
   return ret;
}

/****************************** cut *****************************
int cut(int page, node** top)
int cut: removes the node with the pagenum of page
parameters:
        int page
        node** top
****************************************************************/
int cut(int page, node** top) {
   node* cur = *top;
   int val;
   
   while (cur != NULL) {
      if (page == -1 && cur -> down == NULL) {
         val = cur -> pagenum;
         cur -> up -> down = NULL;
         free(cur);
         return val;
      }
      if (cur -> pagenum == page) {
         val = cur -> pagenum;
         if (cur == *top) {
            pop(top);
            return val;
         }
         if (cur -> down != NULL)
            cur -> down -> up = cur -> up;
         if (cur -> up != NULL)
            cur -> up -> down = cur -> down;
         free(cur);
         break;
      }
      cur = cur -> down;
   }
   return val;
}

/********************* tracestack ****************************
void tracestack(node** top)
void tracestack: prints out the stack
parameters:
        node** top
*************************************************************/
void tracestack(node** top) {
   node* cur = *top;
   
   printf("[ ");
   
   while (cur != NULL) {
      printf("%d ", cur -> pagenum);
      cur = cur -> down;
   }
   
   printf("]\n");
}

/********************* freestack ***************************
void freestack(node** top)
void freestack: frees the stack
parameters:
        node** top
***********************************************************/
void freestack(node** top) {
      node* next;
      
      while (*top != NULL) {
         next = (*top) -> down;
         pop(top);
         *top = next;
      }
}

