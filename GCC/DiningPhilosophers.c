#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int position;
  int count;
  sem_t *leftFork;
  sem_t *rightFork;
} philosopher_t;

void create_forks(sem_t *forks, int num_philosophers);
void start_threads(pthread_t *threads, sem_t *forks, int num_philosophers);

void *philosopherCallback(void *arg);

void think(philosopher_t *philosopher);
void eat(philosopher_t *philosopher);
void takeForks(philosopher_t *philosopher);
void returnForks(philosopher_t *philosopher);

int shouldTakeLeftForkFirst(philosopher_t *philosopher);
int getRandomNumber(int max, int min);

int main(int argc, char *args[])
{
  srand(time(NULL));
  int num_philosophers = getRandomNumber(25, 5);
  
  printf("Number of Philosophers: %d\n", num_philosophers);
  
  sem_t forks[num_philosophers];
  pthread_t threads[num_philosophers];
  
  create_forks(forks, num_philosophers);
  start_threads(threads, forks, num_philosophers);
  
  pthread_exit(NULL);
}

void create_forks(sem_t *forks, int num_philosophers)
{
  for(int i = 0; i < num_philosophers; i++) {
    sem_init(&forks[i], 0, 1);
  }
}

void start_threads(pthread_t *threads, sem_t *forks, int num_philosophers)
{
  for(int i = 0; i < num_philosophers; i++) {
    philosopher_t *philosopher = malloc(sizeof(philosopher_t));
    
    philosopher->position = i;
    philosopher->count = num_philosophers;
    philosopher->leftFork = &forks[i];
    philosopher->rightFork = &forks[i + 1 % num_philosophers];
    
    pthread_create(&threads[i], NULL, philosopherCallback, (void *)philosopher);
  }
}

void *philosopherCallback(void *arg)
{
  philosopher_t *philosopher = (philosopher_t *)arg;
  
  while(1)
  {
    think(philosopher);
    takeForks(philosopher);
    eat(philosopher);
    returnForks(philosopher);
  }
}

void think(philosopher_t *philosopher)
{
  printf("Philosopher %d started thinking\n", philosopher->position + 1);
  
  do
  {
    sleep(getRandomNumber(3, 1));
  } while (getRandomNumber(1, 0));
  
  printf("Philosopher %d stopped thinking\n", philosopher->position + 1);
}

void eat(philosopher_t *philosopher)
{
  printf("Philosopher %d started eating\n", philosopher->position + 1);
  
  do
  {
    sleep(getRandomNumber(3, 1));
  } while (getRandomNumber(1, 0));
  
  printf("Philosopher %d stopped eating\n", philosopher->position + 1);
}

void takeForks(philosopher_t *philosopher)
{
  if (shouldTakeLeftForkFirst(philosopher))
  {
    sem_wait(philosopher->leftFork);
    sem_wait(philosopher->rightFork);
  }
  else
  {
    sem_wait(philosopher->rightFork);
    sem_wait(philosopher->leftFork);
  }
}

void returnForks(philosopher_t *philosopher)
{
  sem_post(philosopher->rightFork);
  sem_post(philosopher->leftFork);
}

int shouldTakeLeftForkFirst(philosopher_t *philosopher)
{
  return (philosopher->position - 1) == philosopher->count;
}

int getRandomNumber(int max, int min)
{
  int result = (rand() % (max + 1));
  if (result < min) result = min;
  return result;
}
