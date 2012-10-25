#include <iostream>
#include "jobQueue.h"

using namespace std;

int main()
{
	// Declare a job queue of size 5
	jobQueue queue(5);
	
	// Fill the job queue
	for( int i=0; i<5; i++ )
	{
		job b( i, IO, 10.0f, 0.0f, 0.5f, -1.0f, true );
		queue.enqueue(b);
	}
	
	// Check if it's full
	if( queue.isFull() ) cout << "Queue is now filled.." << endl<<endl;
	
	
	
	
	// Output the job queue
	while( !queue.isEmpty() )
	{
		job b = queue.dequeue();
		cout << b.getJobNumber() << " " << b.getJobType() << endl;
	}
	
	// Check if it's empty
	if( queue.isEmpty() ) cout << "Queue is now emptied.." << endl<<endl;
	
	
	
	
	// Enqueue a job
	job a( 12, IO, 10.0f, 0.0f, 0.5f, -1.0f, true );
	queue.enqueue(a);
	// Priority enqueue a job
	job c( 50, CPU, 60.0f, 0.0f, 0.5f, -1.0f, true );
	queue.priorityEnqueue(c);
	
	//Check state of queue
	if( !queue.isEmpty() ) cout << endl<<endl<< "Queue is not empty.." <<endl;
	if( !queue.isFull() ) cout << "Queue is not full.." <<endl;
	cout << "The queue has " << queue.getLength() << " items in it." << endl;
	
	// Display the queue, should display '50' before '12'
	while( !queue.isEmpty() )
	{
		job b = queue.dequeue();
		cout << b.getJobNumber() << " " << b.getJobType() << endl;
	}
	// Check if it's empty
	if( queue.isEmpty() ) cout << "Queue is now emptied.." << endl<<endl<<endl;
	
	
	
	
	// Fill the job queue
	for( int i=0; i<5; i++ )
	{
		job b( i, IO, 10.0f, 0.0f, 0.5f, -1.0f, true );
		queue.enqueue(b);
	}
	if( queue.isFull() ) cout << "Queue has been filled.." <<endl;
	queue.clear();
	
	// Check if it's empty
	if( queue.isEmpty() ) cout << "Queue has been cleared and is now empty.." <<endl;
	



	return 0;
}
