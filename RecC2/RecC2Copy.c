#define MAX_LINE_SIZE 20
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void FIFO_Scheduling(struct PCB *node, int CPUreg[8]);
void SJF_Scheduling(struct PCB *node, int CPUreg[8]);
void PR_Scheduling(struct PCB *node, int CPUreg[8]);
void RR_Scheduling(struct PCB *node, struct PCB *Tail, int CPUreg[8], int quantum);
struct PCB *bubbleSort(struct PCB *start);
struct PCB *swap(struct PCB *a, struct PCB *b);
struct PCB *bubbleSort2(struct PCB *start);

int main(int argc, char *argv[]){
    int CPUreg[8] = {0};
    struct PCB *Head=NULL;
    struct PCB *Tail=NULL;
    struct PCB *node = NULL;
    int ProcId, ProcPR, CPUburst;

    if(strcmp(argv[2],"FIFO")== 0 
        || strcmp(argv[2],"SJF")== 0
        || strcmp(argv[2],"PR")== 0){

        
        /* open file */
        FILE *file = fopen(argv[4], "r");
        if (file == NULL){
            printf("file not found\n");
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
        printf("Input File Name : %s\n" , argv[4]);
        printf("CPU Scheduling Alg : %s\n\n", argv[2]);
    } 
    /*Prints the Information*/ 
    if(strcmp(argv[2],"FIFO")== 0){
        FIFO_Scheduling(Head , CPUreg);
    }
    else if(strcmp(argv[2],"SJF")== 0){
        SJF_Scheduling(Head , CPUreg);
    }
    else if(strcmp(argv[2],"PR")== 0){
        PR_Scheduling(Head , CPUreg);
    }
    else if(strcmp(argv[2],"RR")== 0){

        FILE *file = fopen(argv[5], "r");
        if (file == NULL){
            printf("file not found\n");
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
        printf("Input File Name : %s\n" , argv[5]);
        printf("CPU Scheduling Alg : %s\n\n", argv[2]);

        RR_Scheduling(Head ,Tail ,CPUreg ,atoi(argv[3]));
    }

    printf("\n\n");
    return 0;    
}


/****************FIFO_Scheduling*******************
void FIFO_Scheduling(struct PCB *node, int CPUreg[8])

**************************************************/
void FIFO_Scheduling(struct PCB *node, int CPUreg[8]){

    int CLOCK=0; 
    int Total_waiting_time=0; 
    int Total_turnaround_time=0; 
    int Total_job=0;
    
    double Average_Waiting = 0;
    double Average_Turnaround = 0;
    double Throughput = 0;
    while(node != NULL){

        /*copy PCB->Reg[8] into CPUreg[8],
        suppose some work is done on CPU (e.g, increment each CPUreg by one),
        copy CPUreg[8] into PCB->Reg[8]
        */
        CPUreg[8] = node->Reg[8];
        node->Reg[8] = CPUreg[8];



        /*Data collection for performance metrics*/
          
        //node->queueEnterClock = 0;        
        node->waitingTime = node->waitingTime + CLOCK - node->queueEnterClock;


        
        printf("node->waitingTime  %d CLOCK %d node->queueEnterClock %d\n",node->waitingTime, CLOCK, node->queueEnterClock);
        
        Total_waiting_time = Total_waiting_time + node->waitingTime ;
        CLOCK = CLOCK + node->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;

        /*Now implement a FIFO_Scheduling() function and call 
        it to print the order of completed processes.*/
        printf("Proces %d is completed at %d ms\n"
            ,node->ProcId
            ,CLOCK);
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


/******************SJF_Scheduling**********************
void SJF_Scheduling(struct PCB *node, int CPUreg[8])

*****************************************************/
void SJF_Scheduling(struct PCB *node, int CPUreg[8]){
    
    int CLOCK=0; 
    int Total_waiting_time=0; 
    int Total_turnaround_time=0; 
    int Total_job=0;
    
    double Average_Waiting = 0;
    double Average_Turnaround = 0;
    double Throughput = 0;

    //sort the linked list
    node = bubbleSort(node);

    while(node != NULL){
        
        /*copy PCB->Reg[8] into CPUreg[8],
        suppose some work is done on CPU (e.g, increment each CPUreg by one),
        copy CPUreg[8] into PCB->Reg[8]
        */
        CPUreg[8] = node->Reg[8];
        node->Reg[8] = CPUreg[8];

        /*Data manipulation for performance metrics*/        
        node->waitingTime = node->waitingTime + CLOCK - node->queueEnterClock;
        Total_waiting_time = Total_waiting_time + node->waitingTime ;
        CLOCK = CLOCK + node->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;
        //Print Proces and complete
        printf("Proces %d is completed at %d ms\n"
            ,node->ProcId
            ,CLOCK);
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


/******************PR_Scheduling*********************
void PR_Scheduling(struct PCB *node, int CPUreg[8])

*****************************************************/
void PR_Scheduling(struct PCB *node, int CPUreg[8]){

    int CLOCK=0; 
    int Total_waiting_time=0; 
    int Total_turnaround_time=0; 
    int Total_job=0;
    
    double Average_Waiting = 0;
    double Average_Turnaround = 0;
    double Throughput = 0;

    node = bubbleSort2(node);

    while(node != NULL){
        
        /*copy PCB->Reg[8] into CPUreg[8],
        suppose some work is done on CPU (e.g, increment each CPUreg by one),
        copy CPUreg[8] into PCB->Reg[8]
        */
        CPUreg[8] = node->Reg[8];
        node->Reg[8] = CPUreg[8];

        
        /*Data collection for performance metrics*/
        
        node->waitingTime = node->waitingTime + CLOCK - node->queueEnterClock;
        Total_waiting_time = Total_waiting_time + node->waitingTime ;
        CLOCK = CLOCK + node->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;

        /*Now implement a FIFO_Scheduling() function and call 
        it to print the order of completed processes.*/
        printf("Proces %d is completed at %d ms\n"
            ,node->ProcId
            ,CLOCK);
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


/****************RR_Scheduling***********************
void RR_Scheduling(struct PCB *node, int CPUreg[8])

*****************************************************/
void RR_Scheduling(struct PCB *node, struct PCB *Tail, int CPUreg[8], int quantum){

    int CLOCK=0; 
    int Total_waiting_time=0; 
    int Total_turnaround_time=0; 
    int Total_job=0;
    struct PCB *holder = node; 
    double Average_Waiting = 0;
    double Average_Turnaround = 0;
    double Throughput = 0;
    while(node != NULL){
    
//        printf("Tail ProcesID: %d CPU: %d \n\n", Tail->ProcId ,Tail->CPUburst);

        /*copy PCB->Reg[8] into CPUreg[8],
        suppose some work is done on CPU (e.g, increment each CPUreg by one),
        copy CPUreg[8] into PCB->Reg[8]
        */
        CPUreg[8] = node->Reg[8];
        node->Reg[8] = CPUreg[8];
        
        /*Data collection for performance metrics*/
        if(node->CPUburst <= quantum){  
            if(node->ProcId == 0) 
                break;

            printf("Proces %d is completed at ",node->ProcId);
            node->waitingTime = node->waitingTime + CLOCK - node->queueEnterClock;
            Total_waiting_time = Total_waiting_time + node->waitingTime ;
            CLOCK = CLOCK + node->CPUburst;
            Total_turnaround_time = Total_turnaround_time + CLOCK;
            Total_job = Total_job + 1;
            
            holder = node->next;
            node->next = NULL;
            free(node);
            node = holder;

            printf("%d ms\n",CLOCK);
            
            if(node == NULL) 
                break;
        }
        else if (node->CPUburst > quantum){
            node->waitingTime = node->waitingTime + CLOCK - node->queueEnterClock;
            CLOCK = CLOCK + quantum;
            node->CPUburst = node->CPUburst - quantum;
            node->queueEnterClock = CLOCK;
            //insert linked list to the end 
            holder = Tail; 
            Tail = node;
            node = node->next;
            holder->next = Tail;
            Tail->next = NULL;
        }
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


/**************** bubbleSort2 **************************

********************************************************/
struct PCB *bubbleSort(struct PCB *start){
    struct PCB *p, *q, *top;
    int changed = 1;

    /*
    * We need an extra item at the top of the list just to help
    * with assigning switched data to the 'next' of a previous item.
    * It (top) gets deleted after the data is sorted.
    */
    top =(struct PCB*)malloc(sizeof(struct PCB));
    if(top  == NULL) {
        fprintf( stderr, "Memory Allocation error.\n" );
        // In Windows, replace following with a return statement.
        exit(1);
    }

    top->next = start;
    if( start != NULL && start->next != NULL ) {
        /*
        * This is a survival technique with the variable changed.
        * Variable q is always one item behind p. We need q, so
        * that we can make the assignment q->next = list_switch( ... ).
        */
        while( changed ) {
        changed = 0;
        q = top;
        p = top->next;
        while( p->next != NULL ) {
            /* push bigger items down */
            if( p->CPUburst > p->next->CPUburst ) {
                q->next = swap( p, p->next );
                changed = 1;
            }
            q = p;
            if( p->next != NULL )
                p = p->next;
            }
        }
    }
    p = top->next;
    free( top );
    return p;
}

/********************* swap ****************************
struct PCB *swap(struct PCB *l1, struct PCB *l2)


********************************************************/
struct PCB *swap(struct PCB *l1, struct PCB *l2){
    l1->next = l2->next;
    l2->next = l1;
    return l2;
}

/***************** bubbleSort2 *************************
struct PCB *bubbleSort2(struct PCB *start)

*******************************************************/
struct PCB *bubbleSort2(struct PCB *start){
    struct PCB *p, *q, *top;
    int changed = 1;

    /*
    * We need an extra item at the top of the list just to help
    * with assigning switched data to the 'next' of a previous item.
    * It (top) gets deleted after the data is sorted.
    */
    top =(struct PCB*)malloc(sizeof(struct PCB));
    if(top  == NULL) {
        fprintf( stderr, "Memory Allocation error.\n" );
        // In Windows, replace following with a return statement.
        exit(1);
    }

    top->next = start;
    if( start != NULL && start->next != NULL ) {
        /*
        * This is a survival technique with the variable changed.
        * Variable q is always one item behind p. We need q, so
        * that we can make the assignment q->next = list_switch( ... ).
        */
        while( changed ) {
        changed = 0;
        q = top;
        p = top->next;
        while( p->next != NULL ) {
            /* push bigger items down */
            if( p->ProcPR < p->next->ProcPR ) {
                q->next = swap( p, p->next );
                changed = 1;
            }
            q = p;
            if( p->next != NULL )
                p = p->next;
            }
        }
    }
    p = top->next;
    free( top );
    return p;
}

