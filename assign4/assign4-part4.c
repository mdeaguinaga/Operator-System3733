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
#define LEFT2 (threadIndex + pN) % pN

int nthreads;
pthread_mutex_t *chopsticks;
int pN = 0;             //number of philosofer
int *state;


int main(int argc, char *argv[]){
    int nthreads;       // Total of philosofers (threads)
    if(argc != 2){      // checks for wrong parameters 
        printf("User %s #-of-interactions.", argv[0]);
        return 0;
    }
    nthreads = atoi(argv[1]);
    nthreads = atoi(argv[1]);
    pN = nthreads;
    // Prints header
    printf("Assignment 4: # of threads = %d\n", nthreads);
    // call creatPhilosophers function 
    creatPhilosophers(nthreads);
}


void creatPhilosophers(int nthreads){
    pthread_t tid[nthreads];    // array for threads
    int i, j;                   //initial values for forloops
    int error;                  //error check
    int t_num[nthreads];        //array for threads 
     
    //initialisatin of state and S
    chopsticks = (pthread_mutex_t *) malloc(nthreads * sizeof(pthread_mutex_t));
    // Initialize to Unlocked mutex
    for (i = 0; i < nthreads; i++){    
         pthread_mutex_init(&chopsticks[i], NULL);
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

void *philosopherThread(void *arg){
    int *i = arg;

    int rand_num = rand() % 500 + 1;
    int sleep_time = rand_num % pN;
    sleep(sleep_time);

    pickUpChopsticks(*i);  

    rand_num = rand() % 500 + 1;
    sleep_time = rand_num % pN;
    sleep(sleep_time);

    putDownChopsticks(*i);
}

void thinking(int threadIndex) {
    int rand_num = rand() % 500 + 1;
    int sleep_time = rand_num % pN;
    printf("Philosopher %d end eating\n", threadIndex + 1);
    printf("Philosopher %d start thinking\n", threadIndex + 1);
    sleep(sleep_time);
}
void pickUpChopsticks(int threadIndex) {

    int rc1,rc2;

    if (threadIndex & 1) {
        while (pthread_mutex_trylock(&chopsticks[RIGHT]) != 0){
            // wait treated as a spin lock 
            }
        while (pthread_mutex_trylock(&chopsticks[LEFT]) != 0) {
            // wait treated as a spin lock 
            }
        printf("Philosopher %d end thinking\n", threadIndex + 1);
        printf("Philosopher %d picked up chopsticks %d and %d\n"
                    , threadIndex + 1 , LEFT + 1, threadIndex + 1);
//        eating(threadIndex);
    }      
    else {
        while (pthread_mutex_trylock(&chopsticks[LEFT]) != 0) {
            // wait treated as a spin lock 
        }   
        while (pthread_mutex_trylock(&chopsticks[RIGHT]) != 0) {
            // wait treated as a spin lock 
        }   
       
        printf("Philosopher %d end thinking\n", threadIndex + 1);
        printf("Philosopher %d picked up chopsticks %d and %d\n"
                    , threadIndex + 1 , LEFT + 1, threadIndex + 1);
    }
    eating(threadIndex);
}
void eating(int threadIndex) {
    printf("Philosopher %d start eating\n", threadIndex + 1);
}

void putDownChopsticks(int threadIndex) {
    
    printf("Philosopher %d finished eating\n", threadIndex + 1);
    printf("Philosopher %d put down chopstick %d and %d \n",
                threadIndex + 1, LEFT + 1, threadIndex + 1);
    pthread_mutex_unlock(&chopsticks[RIGHT]);
    pthread_mutex_unlock(&chopsticks[LEFT]); 
    //pthread_mutex_unlock(&chopsticks[(threadIndex + nthreads) % nthreads]); 
}




