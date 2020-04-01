#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
void *fun1();
void *fun2();
sem_t s; //semaphore variable
int main()
{
sem_init(&s,0,1); //initialize semaphore variable
pthread_t thread1, thread2;
pthread_create(&thread1, NULL, fun1, NULL);
pthread_create(&thread2, NULL, fun2, NULL);
pthread_join(thread1, NULL);
pthread_join(thread2,NULL);
printf("Final value of shared resource is %d\n",resource); //prints the last updated value of shared variable
}

void *fun1()
{
    int x;
    sem_wait(&s); //executes wait operation on s
    x=resource;//thread one reads value of shared variable
    x++;  //thread one increments its value
    sleep(1);  //thread one is preempted by thread 2
    resource=x; //thread one updates the value of shared variable
    sem_post(&s); //executes signal operation on s
}

void *fun2()
{
    int y;
    sem_wait(&s);
    y=resource;
    y--;  
    sleep(1);  
    resource=y; 
    sem_post(&s);
}

