#include<linux/kernel.h>
#include<linux/semaphore.h>
#include<linux/mutex.h>
#include <linux/syscalls.h>

static struct mutex lock;
static struct semaphore FullSem;
static struct semaphore EmptySem;

SYSCALL_DEFINE1(semaphore_initializer, int, count)
{
    sema_init(&EmptySem,count); //count is the buffer size
    mutex_init(&lock);
    sema_init(&FullSem,0); //nothing has been produced initially so this is initialized to 0
}

SYSCALL_DEFINE1(producer, int, choice)
{
    if(choice==0)
    {
	down(&EmptySem);//occupy and decrement an empty slot 
    	mutex_lock(&lock); // two producers dont work together 
    }
    else if(choice ==1)
    {
	mutex_unlock(&lock);//cs over now other process can start
	up(&FullSem);//one item has been produced in the buffer now 
    }
}

SYSCALL_DEFINE1(consumer, int, choice)
{
    if(choice==0)
    {
	down(&FullSem);//occupy and decrement an empty slot 
    	mutex_lock(&lock); // two producers dont work together 
    }
    else if(choice ==1)
    {
	mutex_unlock(&lock);//cs over now other process can start
	up(&EmptySem);//one item has been produced in the buffer now 
    }
}
