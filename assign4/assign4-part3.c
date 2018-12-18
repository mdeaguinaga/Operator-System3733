//Manuel I. De Aguinaga
//uyi362
#include<stdio.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include"assign4-part2.h"

#define LEFT (threadIndex + pN-1) % pN
#define RIGHT (threadIndex + 1) % pN
int pN = 0;             //number of philosofer
pthread_cond_t *S;     //mutex for threads
pthread_mutex_t mutex;
int *state;             //array to check status
int *number_of_ph;
int p_test = 1;
time_t t;
/****************************************************************
                        main

****************************************************************/
int main(int argc, char *argv[]){
    

    int nthreads;       // Total of philosofers (threads)
    if(argc != 2){      // checks for wrong parameters 
        printf("User %s #-of-interactions.", argv[0]);
        return 0;
    }
    
    nthreads = atoi(argv[1]);

    pN = nthreads;
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
    
    //initialisatin of state and S
    S = (pthread_cond_t *) malloc(nthreads * sizeof(pthread_cond_t));    
    state = (int*) malloc(nthreads * sizeof(int));
    number_of_ph = (int*) malloc(nthreads * sizeof(int));

    // Initialize to Unlocked mutex
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < nthreads; i++){
        pthread_cond_init(&S[i], NULL);
        state[i] = THINKING;
        number_of_ph[i] = i+1;
    }

    /* create threads representing dinning philosopher */ 
    for (i = 0; i < nthreads; i++){
        t_num[i] = i;   
        if(error = pthread_create (&tid[i] ,NULL, philosopherThread ,&t_num[i])){ 
            fprintf (stderr, "Fail to create thread %s.", strerror(error)); 
            return ; 
        }
        printf("Philosopher %d is thinking\n", i + 1);
    } 
    
    /* wait for the join of threads */  
    for (j = 0; j < nthreads; j++){ 
        if(error = pthread_join(tid[j], NULL )){ 
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
   
    int *i = arg;
    pickUpChopsticks(*i);
     
    int rand_num = rand() % 500 + 1;
    int sleep_time = rand_num % pN;;
    sleep(sleep_time);

    putDownChopsticks(*i);

}


/*****************************************************************
                        pickUpChopsticks
*****************************************************************/
void pickUpChopsticks(int threadIndex){
    
    pthread_mutex_lock(&mutex);
    // state that hungry
    state[threadIndex] = HUNGRY;
    //eat if neighbours are not eating
    test(threadIndex);
    
    while (state[threadIndex] == HUNGRY)
             pthread_cond_wait (&S[threadIndex], &mutex);
    pthread_mutex_unlock (&mutex);
}
/*****************************************************************
                        pickUpChopsticks
*****************************************************************/
void eating(threadIndex){
    printf("Philosopher %d start eating\n", threadIndex + 1);
}
/*****************************************************************
                        eating
*****************************************************************/
void putDownChopsticks(int threadIndex){

    pthread_mutex_lock(&mutex);
    
    // state that thinking
    state[threadIndex] = THINKING;
    
    printf("Philosopher %d putting chopstick %d and %d down\n",
                             threadIndex + 1, LEFT + 1, threadIndex + 1);

    thinking(threadIndex);

    test(LEFT);
    test(RIGHT);

    pthread_mutex_unlock(&mutex);
}

/*****************************************************************
                        thinking
*****************************************************************/
void thinking(threadIndex){ 
//    int rand_num = rand() % 500 + 1;
//    int sleep_time = rand_num % pN;
    printf("Philosopher %d end eating\n", threadIndex + 1);
    printf("Philosopher %d start thinking\n", threadIndex + 1);
//    sleep(sleep_time);
}
/*****************************************************************
                        test
*****************************************************************/
void test(int threadIndex){
    if (state[threadIndex] == HUNGRY
        && state[LEFT] != EATING
        && state[RIGHT] != EATING) {

        if(number_of_ph[threadIndex] == p_test){
            // state that eating
            state[threadIndex] = EATING;

            printf("Philosopher %d end thinking\n", threadIndex + 1);
            printf("Philosopher %d takes chopstick %d and %d\n",
                        threadIndex + 1, LEFT + 1, threadIndex + 1);
        
            eating(threadIndex);
            
            pthread_cond_signal (&S[threadIndex]);   

            p_test ++;
        }
    }
}

