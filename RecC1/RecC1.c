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


void FIFO_Scheduling(int ProcId, int CLOCK);

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

    double Average_Waiting = 0;
    double Average_Turnaround = 0;
    double Throughput = 0;

    printf("%s %s %s %s \n",argv[1] ,argv[2] ,argv[3] ,argv[4]);

    /* open file */
    //FILE *file = fopen("input1.txt", "r");
    FILE *file = fopen(argv[4], "r");
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
    printf("CPU Scheduling Alg : FIFO\n\n");


    /*Prints the Information*/
    node = Head;    
    while(node != NULL){
        
        /*     Print LinkList
        printf("%d %d %d\n"
            ,node->ProcId
            ,node->ProcPR
            ,node->CPUburst);
        */
        
        /*copy PCB->Reg[8] into CPUreg[8],
        suppose some work is done on CPU (e.g, increment each CPUreg by one),
        copy CPUreg[8] into PCB->Reg[8]
        */
        CPUreg[8] = node->Reg[8];
        CPUreg[8]++;
        node->Reg[8] = CPUreg[8];

        
        /*Data collection for performance metrics*/
        
        node->waitingTime = node->waitingTime + CLOCK - node->queueEnterClock;
        Total_waiting_time = Total_waiting_time + node->waitingTime ;
        CLOCK = CLOCK + node->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;

        /*Now implement a FIFO_Scheduling() function and call 
        it to print the order of completed processes.*/

        FIFO_Scheduling(node->ProcId, CLOCK);

        /*moves the LinlList to the next element*/   
        node = node->next;
    }
    
    /*print the perfromance metrics mentioned before: */
    Average_Waiting = (float) Total_waiting_time / Total_job;
    Average_Turnaround = (float) Total_turnaround_time / Total_job;
    Throughput = (float) Total_job / CLOCK;

    printf("\nAverage Waiting time =  %.2lf ms     (%d/%d)\n"
        ,Average_Waiting 
        ,Total_waiting_time
        ,Total_job);
    printf("Average Turnaround time = %.2lf ms  (%d/%d)\n"
        ,Average_Turnaround
        ,Total_turnaround_time 
        ,Total_job);
    printf("Throughput = %.2lf jobs per ms       (%d/%d)\n"
        ,Throughput
        ,Total_job
        ,CLOCK);


}

/*Print the information per process*/
void FIFO_Scheduling(int ProcId, int CLOCK){
    printf("Proces %d is completed at %d ms\n"
        ,ProcId
        ,CLOCK);
}

