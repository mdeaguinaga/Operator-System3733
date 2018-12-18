#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pagetable.h"
#include "phypages.h"
#include "part2.h"

/************************** main ************************************
In this part, the program  manage the content of the page table and 
handle the physical memory management. It two source programs files
files in this part: phypages.c and pagetable.c, and a part2.h. 
Here, phypages.c is used to manage the physical pages and pagetable.c 
will manage the page table for the process. 

The program assumes that the physical frame/page 0 is reserved for the 
OS, while other frames are freed initially. Initially, when there are
free frames, you should use a simple scheme and allocate the free 
physical frames sequentially, where the physical frames are allocated 
in the increasing order of frame number, starting from 1, 2, 3, ...... 
(that is, the page of the first logical address will get frame 1 as so 
on). If there are some physical pages that are available, the program
will always allocate from the free list at first. 
********************************************************************/
int main(int argc, char *argv[]) {
   int **addrtrans;
   int faults, fdin, fdout, frame, lru, nodes;
   int *frames;
   unsigned long offset, page, physaddr, virtaddr;
   node* top;
   // Checks for correct input
   if (argc != 2) {
      printf("Usage: %s <SEQUENCE FILE>\n", argv[0]);
      exit(1);
   }
   
   // Checks for a valid file 
   if ((fdin = open(argv[1], O_RDONLY)) == -1) {
      perror("Main failed to open sequence file");
      exit(2);
   }
   
   // opens the output for write only and creates the file, therwise
   // it prints an error if it does not creates or opens for write
   if ((fdout = open("output-part2", O_WRONLY | O_CREAT, 0600)) == -1) {
      perror("Main failed to open output file");
      close(fdin);
      exit(2);
   }
   
    // Set the information to be readi to be executed
    addrtrans = initializeTable(&addrtrans, 32);
    frames = initializeFrames(&frames, 8);
    faults = 0;
    nodes = 0;
    top = NULL;
   
    // check that while the information still readible, the 
    // wile loop will be continuing
    while (read(fdin, &virtaddr, sizeof(virtaddr)) > 0) {
        printf("Virtual address: %#lx\n", virtaddr);
      
        offset = virtaddr & 0x7F;
        printf("Offset: %#lx\n", offset);
      
        page = virtaddr >> 7;
      
        if (nodes < 7 && peer(page, &top) == -1) {
            faults++;
            push(page, &top);
            nodes++;
        }
        else if (nodes >= 7 && peer(page, &top) > -1) {
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
            frame = findOpen(&frames, 8);
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
      
        physaddr = page << 7;
        printf("Shifted frame: %#lx\n", physaddr);
      
        physaddr += offset;
        printf("Physical address: %#lx\n", physaddr);
      
        tracestack(&top);
        
        // if the information is not writen, it will free the table
        // free the frame and also will free the stack
        if (write(fdout, &physaddr, sizeof(physaddr)) == -1) {
            perror("Main failed to write to output file");
            freeTable(&addrtrans, 32);
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
    freeTable(&addrtrans, 32);
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
