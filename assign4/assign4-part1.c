//Manuel I. DE Aguinaga
//uyi362
#include<stdio.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>

void creatPhilosophers(int nthreads);
void *philosopherThread(void *arg);

/****************************************************************
                        main

****************************************************************/
int main(int argc, char *argv[]){

    int nthreads;       // Total of philosofers (threads)
    if(argc != 2){      // checks for wrong parameters 
        printf("User %s #-of-interactions.", argv[0]);
        return 0;
    }
    else
        nthreads = atoi(argv[1]);
    // Prints header
    printf("Assignment 4: # of threads = %d\n", nthreads);
    // call creatPhilosophers function 
    creatPhilosophers(nthreads); 
}

/*****************************************************************
                        creatPhilosophers

*****************************************************************/
void creatPhilosophers(int nthreads){
    pthread_t tid[nthreads];    // array for threads
    int i, j;                   //initial values for forloops
    int error;                  //error check
    int t_num[nthreads];        //array for threads 

    /* create threads representing dinning philosopher */ 
    for (i = 0; i < nthreads; i++) 
    {
        t_num[i] = i;   
        if(error = pthread_create (tid+i ,NULL, philosopherThread ,(void *)&t_num[i]))
        { 
            fprintf (stderr, "Fail to create thread %s.", strerror(error)); 
            return ; 
        }
    } 
                                                                                
    /* wait for the join of threads */  
    for (j = 0; j < nthreads; j++) 
    { 
        if(error = pthread_join(tid[j], NULL )) 
        { 
            fprintf (stderr, "Fail to join thread %s\n.", strerror(error));
            return; 
        } 
    }
    printf("%d threads have been completed/joined successfully!\n" ,nthreads);
}

/*****************************************************************
                    philosopherThread

*****************************************************************/
void *philosopherThread(void *arg){
    printf("This is philosopher %d\n",  *(int *) arg);
    return NULL;
}
