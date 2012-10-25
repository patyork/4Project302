
#include "job.h"
#include "jobQueue.h"
#include <iostream>

// Default constructor
jobQueue::jobQueue()
{
	jobs = NULL;
	front = 0;
	rear = 0;
	maxSize = 0;
	length = 0;
}
		
// Parameterized constructor
jobQueue::jobQueue( int newSize )
{
	jobs = new job[newSize];
	front = 0;
	rear = 0;
	maxSize = newSize;
	length = 0;
}
		
// Deconstructor
jobQueue::~jobQueue()
{
	if( jobs != NULL ) delete[] jobs;
	jobs = NULL;
	front = 0;
	rear = 0;
	maxSize = 0;
	length = 0;
}
		
// Enqueue a job
void jobQueue::enqueue( job j )
{
	if( !isFull() && jobs != NULL )
	{
		jobs[rear] = j;
		length++;
		rear++;
	}
}
		
// Priority Enqueue a job
void jobQueue::priorityEnqueue( job j )
{
	if( !isFull() && jobs != NULL )
	{
		for( int i=rear; i>front; i-- )
		{
			jobs[i] = jobs[i-1];
		}
		jobs[front] = j;
		length++;
		rear++;
	}
}
		
// Dequeue
job jobQueue::dequeue()
{
	job b;
	if( !isEmpty() && jobs!=NULL )
	{
		job temp = jobs[front];	//store job to return
		
		for( int i=front+1; i<rear; i++ )
		{
			jobs[i-1] = jobs[i];
		}
		rear--;
		length--;
		return temp;
	}
	else return b;  // return a stub job if none available
}
		
// Return if the queue is full
bool jobQueue::isFull() const
{
	if( length == maxSize ) return true;
	return false;
}
		
// Return if the queue is empty
bool jobQueue::isEmpty() const
{
	if( length==0 ) return true;
	return false;
}
		
// Return the length of the queue
int jobQueue::getLength() const
{
	return length;
}
		
// Clear the queue
void jobQueue::clear()
{
	rear = front;
	length = 0;
}


