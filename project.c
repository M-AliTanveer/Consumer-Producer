#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>

#define MaxItems 5 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 

int in = 0;
int out = 0;
int buffer[BufferSize];

void *producer()
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = i+2*i; // Produce an random item
        syscall(550,0);
        buffer[i] = item;
        printf("Producer: Insert Item %d at %d\n", buffer[i],i);
        syscall(550,1);

    }
}
void *consumer()
{   
    for(int i = 0; i < MaxItems; i++) {

        int item = buffer[i];
        syscall(551,0);
        printf("Consumer Remove Item %d from %d\n",item, i);
        syscall(551,1);
    }
}

int main()
{   

    pthread_t pro,con;
    syscall(549,BufferSize);

        pthread_create(&pro, NULL, (void *)producer,NULL );
        pthread_create(&con, NULL, (void *)consumer,NULL );

        pthread_join(pro, NULL);
        pthread_join(con, NULL);
    return 0;
    
}