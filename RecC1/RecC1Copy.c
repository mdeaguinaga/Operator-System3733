#define MAX_LINE_SIZE 20
#include<stdio.h>
#include<stdlib.h>

struct PCB {
    int ProcId; 
    int ProcPR; 
    int CPUburst; 
    int Reg[8]; 
    int queueEnterClock; 
    int waitingTime; 
    /* other info */ 
    struct PCB *next;
};

int main(int argc, char *argv[]){
    int CPUreg[8] = {0};
    struct PCB *Head=NULL;
    struct PCB *Tail=NULL;
    struct PCB *node = NULL;
    int ProcId, ProcPR, CPUburst;

    int CLOCK=0; 
    int Total_waiting_time=0; 
    int Total_turnaround_time=0; 
    int Total_job=0;

    /* open file */
    FILE *file = fopen("input1.txt", "r");
    if (file == NULL){

    }
    while(fscanf(file, "%d %d %d\n"
            ,&ProcId
            ,&ProcPR
            ,&CPUburst)==3){

        node = (struct PCB*)malloc(sizeof(struct PCB));

        node->ProcId = ProcId;
        node->ProcPR = ProcPR;
        node->CPUburst = CPUburst;
        node->Reg[8] = ProcId;
        node->queueEnterClock = 0;
        node->waitingTime = 0;

        /*
        printf("%d %d %d\n" 
            ,node->ProcId
            ,node->ProcPR
            ,node->CPUburst);
        */

        if(Head == NULL){
            Head = node;
            Head->next = NULL;
        }

        else if(Tail == NULL){
            Tail = node;
            Tail -> next = NULL;

            if(Head->next == NULL){ 
                Head->next = node;
            }
        }
        
        else{
            struct PCB *temp = Tail;
            Tail = node;
            node = temp;
            node->next = Tail;
            Tail->next = NULL;
        }
    }
    fclose(file);

    printf("Student Name: Manuel I. De Aguinaga\n");
    printf("Input File Name : input1.txt\n");


    /*Prints the Information*/
    node = Head;    
    while(node != NULL){
        printf("%d %d %d\n"
            ,node->ProcId
            ,node->ProcPR
            ,node->CPUburst);
            /*moves the LinlList to the next element*/   
            node = node->next;
    }
}

