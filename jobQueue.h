#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include "job.h"

class jobQueue
{
	private:
	
		// Array of jobs
		job* jobs;
		
		// Index of the front
		int front;
		
		// Index of the rear
		int rear;
		
		// Max size of the queue
		int maxSize;
		
		// Current length of the queue
		int length;
	
	public:
	
		// Default constructor
		jobQueue();
		
		// Parameterized constructor
		jobQueue( int newSize );
		
		// Deconstructor
		~jobQueue();
		
		// Enqueue a job
		void enqueue( job j );
		
		// Priority Enqueue a job
		void priorityEnqueue( job j );
		
		// Dequeue
		job dequeue();
		
		// Return if the queue is full
		bool isFull() const;
		
		// Return if the queue is empty
		bool isEmpty() const;
		
		// Return the length of the queue
		int getLength() const;
		
		// Clear the queue
		void clear();
		
		// Returns a copy of the front of the Queue
		job copyFront();
};







#endif
