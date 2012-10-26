
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "jobQueue.h"
#include "simulation.h"



// Whether there is an empty spot in any of the CPU queues
bool simulation::isEmptyinCPUs( jobQueue cpu[] )
{
	for( int i=0; i<numberOfCPUs; i++ )
	{
		if( !cpu[i].isFull() ) return true;
	}
	return false;
}

// Create a new job (but don't enqueue it)
job simulation::createRandomJob( float currTime, int jobNum )
{
	int random = rand() % 1000;
				
	// if it's an IO job
	if( random < distTypes[0]*10 )
	{
		// create a basic job
		job newJob( jobNum, IO, 0.0f, 0.0f, currTime, -1.0f, true );
		
		// Randomly determine service time req'd
		random = rand() % 1000;
		if( random < (distTimes[0] * 10) )
		{
			newJob.setTimeRequired( 10.f );
		}
		else if( random < (distTimes[0] * 10)+(distTimes[1] * 10) )
		{
			newJob.setTimeRequired( 20.f );
		}
		else if( random < (distTimes[0] * 10)+(distTimes[1] * 10)+(distTimes[2] * 10) )
		{
			newJob.setTimeRequired( 30.f );
		}
		else
		{
			newJob.setTimeRequired( 60.f );
		}
			
		return newJob;
	}
	else // it's a CPU job
	{
		// create a basic job
		job newJob( jobNum, CPU, 0.0f, 0.0f, currTime, -1.0f, false );
		
		// Randomly determine service time req'd
		random = rand() % 1000;
		if( random < (distTimes[0] * 10) )
		{
			newJob.setTimeRequired( 10.f );
		}
		else if( random < (distTimes[0] * 10)+(distTimes[1] * 10) )
		{
			newJob.setTimeRequired( 20.f );
		}
		else if( random < (distTimes[0] * 10)+(distTimes[1] * 10)+(distTimes[2] * 10) )
		{
			newJob.setTimeRequired( 30.f );
		}
		else
		{
			newJob.setTimeRequired( 60.f );
		}
		
		return newJob;
	}
	
	
}
	
// Initialize the simulation
void simulation::init()
{
	using namespace std;
	
	// Prompt for the input data
	cout << "How many jobs would you like to process . . . . . . . . . . . . . : ";
	cin >> numberOfJobs;
	cout << "What is the probability of 1 job entering each cycle? (ex. 0.040) : ";
	cin >> probOne;
	cout << "What is the probability of 2 jobs entering each cycle? (ex. 0.005): ";
	cin >> probTwo;
	
	
	// Distribution of service times
	cout << endl << "DISTRIBUTION OF SERVICE TIMES" << endl
		<< "Percentage of jobs take 10 seconds of processing time: ";
	cin >> distTimes[0];
	cout << "Percentage of jobs take 20 seconds of processing time: ";
	cin >> distTimes[1];
	cout << "Percentage of jobs take 30 seconds of processing time: ";
	cin >> distTimes[2];
	cout << "Percentage of jobs take 60 seconds of processing time: ";
	cin >> distTimes[3];
	
	// Check if 
	if( distTimes[0] + distTimes[1] + distTimes[2] + distTimes[3] != 100.0f )
	{
		cout << endl << "ERROR" << endl
			<< "The Distribution of Service Times must add up to 100%!" << endl
			<< "Please Try Again." << endl << endl;
		
		return;
	}
	
	
	// Job class distribution
	cout << endl << "DISTRIBUTION OF JOB CLASSES" << endl
		<< "Percentage of I/O bound jobs: ";
	cin >> distTypes[0];
	cout << "Percentage of CPU bound jobs: ";
	cin >> distTypes[1];
	
	// Check if 
	if( distTypes[0] + distTypes[1] != 100.0f )
	{
		cout << endl << "ERROR" << endl
			<< "The Distribution of Job Classes must add up to 100%!" << endl
			<< "Please Try Again." << endl << endl;
		
		return;
	}
	
	
	// Number of CPUs
	cout << endl << "Number of CPUs to simulate: ";
	cin >> numberOfCPUs;
	
	// Check
	if( numberOfCPUs < 1 )
	{
		cout << endl << "ERROR" << endl
			<< "There must be at least 1 CPU!" << endl
			<< "Please Try Again." << endl << endl;
		
		return;
	}
	
}	
		
// Run the simulation
void simulation::run()
{
	using namespace std;
	
	// Setup the Wait queue
	jobQueue waitList(100);
	
	// Set up the CPU Queues
	jobQueue cpuList[numberOfCPUs];
	float cpuIdle[numberOfCPUs];
	for( int i=0; i<numberOfCPUs; i++ )
		cpuIdle[i] = 0.0f;
	
	// Job counter, job done counter
	int jobCounter = 0, jobsDone = 0;
	
	// The Current time
	float currentTime = 0.0f;
	
	// Initialize random number generator
	srand ( time(NULL) );
	
	// Main simulation loop
	while( jobsDone < numberOfJobs )
	{
		// Job creation
		if( !waitList.isFull() && jobCounter < numberOfJobs )
		{
			// Generate a random number 0-999
			int random = rand() % 1000;
			
			// Check if one job to enter
			if( random < (probOne * 1000) )
			{
				// Generate one job and enqueue
				waitList.enqueue( createRandomJob( currentTime, jobCounter ) );
				
				jobCounter++;
				//cout << " New Job Added to the Wait Queue " << endl;
			}
			else if ( random < ( (probOne * 1000)+(probTwo * 1000) ) )
			{
				// Enqueue two jobs
				waitList.enqueue( createRandomJob( currentTime, jobCounter ) );
				jobCounter++;
				waitList.enqueue( createRandomJob( currentTime, jobCounter ) );
				jobCounter++;
				//cout << " Two New Jobs Added to the Wait Queue " << endl;
			}
		
		} // End job creation
		
		
		// Fill CPU Queues
		while( !waitList.isEmpty() && isEmptyinCPUs( cpuList ) )
		{
			
			// Find shortest CPU Queue
			int shortestQueue = 0;
			int shortestLength = 5;
			for( int i=0; i<numberOfCPUs; i++ )
			{
				if( cpuList[i].getLength() < shortestLength )
				{
					shortestQueue = i;
					shortestLength = cpuList[i].getLength();
				}
			}
			
			// Move from waitlist into the shortest CPU queue
			cpuList[shortestQueue].enqueue( waitList.dequeue() );
			
			//cout << " Job Moved from Wait Queue into CPU " << shortestQueue << "'s Queue " << endl;
			
		}// End fill CPU Queues
		
		
		// Process a job timeslice in each CPU
		for( int i=0; i<numberOfCPUs; i++ )
		{
			if( !cpuList[i].isEmpty() )
			{
				job a = cpuList[i].dequeue();
				a.incrementTimeServiced();
			
				// Check if the job has been completely serviced
				if( a.getTimeRequired() - a.getTimeServiced() < 0.05f )
				{
					jobsDone++;
					
					// Set completion time
					a.setCompletionTime( currentTime );
					
					/////////// Do something with the fact that a job has been completed
						//TODO calculate elapsed time for statistics
						
					cout << " Job #" << a.getJobNumber() << " Finished!" << endl;
				}
				// else if the job was a CPU bound job and has to be Priority Enqueued
				else if( !a.lastService() )
				{
					// set it to only have .1 left
					a.setLastService( true );
					
					// Priority enqueue
					cpuList[i].priorityEnqueue( a );
					
					cout << " Job #" << a.getJobNumber() << " has " << a.getTimeRequired() - a.getTimeServiced() << endl;
				}
				else // else the job need to be sent back to the wait list
				{
					if( a.getJobType() == CPU ) a.setLastService(false);
					waitList.enqueue( a );
					
					cout << " Job #" << a.getJobNumber() << " has " << a.getTimeRequired() - a.getTimeServiced() << endl;
					
					//cout << " Job #" << a.getJobNumber() << " put back in wait list!" << endl;
				}
			}
			else
			{
				// Increase this CPUs idle time
				cpuIdle[i] += 0.1f;
			}
		}
		
		
		// Increment the time counter
		currentTime += 0.1f;
	}
	
	cout << "Simulation Over" << endl
		<< "Simulation Time: " << currentTime << endl;
}
