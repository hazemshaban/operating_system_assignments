#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include<semaphore.h>
#define MAX 5
#include <stdbool.h>
// counter space area
int *counter=0;

sem_t counterSemphore;
sem_t sem_moni_coll,numberOfItems,remainingSize;

////////////////Queue impelmention//////////////////
int intQueue[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;
bool isFull() {
   return itemCount == MAX;
}
void insert(int data) {

   if(!isFull()) {

      if(rear == MAX-1) {
         rear = -1;
      }

      intQueue[++rear] = data;
      itemCount++;
   }
}
int removeData() {
   int data = intQueue[front++];

   if(front == MAX) {
      front = 0;
   }

   itemCount--;
   return data;
}
///////////////////////////////////////////////////////

//
////////counter function////////////////
void *mcounter(void *c)
{
int *i= (int *)c;
while(true){
int randomTime=rand()%3;
sleep(randomTime);
printf("counter thread '%d' recieve a message\n",*i+1);
int value ;
sem_getvalue(&counterSemphore,&value);
if(value<=0)
printf("counter thread '%d' waiting to write\n",*i+1);
sem_wait(&counterSemphore);
sem_getvalue(&counterSemphore,&value);
printf("Counter thread '%d': now adding to counter\n",*i+1);
*counter=*counter+1;
printf("counter:%d\n",*counter);
sem_post(&counterSemphore);
}
 pthread_exit(NULL);
}
///////////////////////////////////////



/////////// monitor function////////////////
void *monitor(void *c1)
{

while(1){
int randomTime=rand()%2;
sleep(randomTime);
int x;
int value;
////////// monitor and counter //////////////////////
sem_getvalue(&counterSemphore,&value);
if (value<=0)
printf("Monitor thread: waiting to read counter||||||||||||||||||||||||||||||||\n");
sem_wait(&counterSemphore);
x=*counter;
printf("Monitor thread: reading a counter value of :%d\n",x);
*counter=0;
sem_post(&counterSemphore);

////////// collector and monitor/////////////////////
int v1,v2;
if(x!=0){

sem_getvalue(&remainingSize,&v2);

if(v2<=0){
    printf("Monitor thread: Buffer full!!\n");
    }

sem_wait(&remainingSize);
sem_wait(&sem_moni_coll);
insert(x);
 printf("Monitor thread: writing to buffer at position'%d'\n",rear);
sem_post(&sem_moni_coll);
sem_post(&numberOfItems);
}
}
 pthread_exit(NULL);
}
///////////////////////////////////////////



///////////////////collector function /////////////////
void *mcollector(void *c)
{

while(1){
int randomTime=rand()%2;
sleep(randomTime+1);
int value;
sem_getvalue(&numberOfItems,&value);
if(value==0){
printf("Collector thread: nothig is in the buffer!\n");
}
sem_wait(&numberOfItems);
sem_wait(&sem_moni_coll);
printf("Collector thread: reading from the buffer at position '%d'\n",front);removeData();
sem_post(&sem_moni_coll);
sem_post(&remainingSize);
}
 pthread_exit(NULL);
}
/////////////////////////////////////////////////
int main()

{

    sem_init(&counterSemphore, 0, 1);
    sem_init(&sem_moni_coll, 0, 1);
    sem_init(&numberOfItems, 0, 0);
    sem_init(&remainingSize, 0, MAX);
    int *buffer;
    counter=(int*)malloc(sizeof(int));
    int N;
    scanf("%d",&N);
    printf("%d",N);
    pthread_t counterThreads[N],monitorThread,mCollectorThread;
    int x[N];

    int rc1 =pthread_create(&monitorThread, NULL, &monitor,counter);
    int rc2 =pthread_create(&mCollectorThread, NULL, &mcollector,counter);

    for(int i=0;i<N;i++)
    {
    x[i]=i;
    int rc =pthread_create(&counterThreads[i], NULL, &mcounter,&x[i]);
    }
     for(int j=0;j<N;j++)
    {
    pthread_join(counterThreads[j],NULL);
    }
    pthread_join(monitorThread,NULL);

    return 0;
}
