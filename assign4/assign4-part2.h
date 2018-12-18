#define THINKING 2
#define HUNGRY 1
#define EATING 0


void creatPhilosophers(int nthreads);
void *philosopherThread(void *arg);
void thinking(); 
void pickUpChopsticks(int threadIndex); 
void eating();
void putDownChopsticks(int threadIndex);
void test(int phnum);
