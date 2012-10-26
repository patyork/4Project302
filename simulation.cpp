
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
	float cpuIdle = 0.0f;
	
	// Job counter, job done counter
	int jobCounter = 0, jobsDone = 0;
	
	// The Current time
	float currentTime = 0.0f;
	
	// Initialize random number generator
	srand ( time(NULL) );
	
	// Statistic Variables
	int numberOfIOJobs = 0, numberOfCPUJobs = 0,
		numberOf10=0, numberOf20=0, numberOf30=0, numberOf60=0;
	float timeInWait=0.0f, timeInCPU=0.0f;
	
	// Main simulation loop
	while( jobsDone < numberOfJobs )
	{
		// Job creation
		if( waitList.getLength() + numberOfCPUs+1 < 100 && jobCounter < numberOfJobs )
		{
			// Generate a random number 0-999
			int random = rand() % 1000;
			
			// Check if one job to enter
			if( random < (probOne * 1000) )
			{
				// Generate one job and enqueue
				waitList.enqueue( createRandomJob( currentTime, jobCounter ) );
				
				jobCounter++;
			
				
				//TODO print out to file a new job has been created
			}
			else if ( random < ( (probOne * 1000)+(probTwo * 1000) ) )
			{
				// Enqueue two jobs
				waitList.enqueue( createRandomJob( currentTime, jobCounter ) );
				jobCounter++;
				if( !waitList.isFull() && jobCounter < numberOfJobs )
				{
					waitList.enqueue( createRandomJob( currentTime, jobCounter ) );
					jobCounter++;
				}
				
				
				//TODO print out to file a new job has been created
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
			
		}// End fill CPU Queues
		
		
		// Check the Waitlist times
		timeInWait += waitList.getLength() * 0.1;
		
		//Check the CPU wait times
		int tempNumCPU = 0;
		for( int i=0; i<numberOfCPUs; i++ )
		{
			tempNumCPU += cpuList[i].getLength();
		}
		timeInCPU += tempNumCPU * 0.1f;
		
		
		// Process a job timeslice in each CPU
		for( int i=0; i<numberOfCPUs; i++ )
		{
			if( !cpuList[i].isEmpty() )
			{
				job a = cpuList[i].dequeue();
				a.incrementTimeServiced();
			
				// Check if the job has been completely serviced
				if( a.getTimeRequired() - a.getTimeServiced() < 1.0f )
				{
					jobsDone++;
					
					// Set completion time
					a.setCompletionTime( currentTime );
					
					// Determine job class, and job service time
					if( a.getJobType() == IO ) numberOfIOJobs++;
					else numberOfCPUJobs++;
					
					if( a.getTimeRequired() == 10.0 ) numberOf10++;
					else if( a.getTimeRequired() == 20.0 ) numberOf20++;
					else if( a.getTimeRequired() == 30.0 ) numberOf30++;
					else numberOf60++;
					
					/////////// Do something with the fact that a job has been completed
						//TODO calculate elapsed time for statistics
						
				}
				// else if the job was a CPU bound job and has to be Priority Enqueued
				else if( !a.lastService() )
				{
					// set it to only have .1 left
					a.setLastService( true );
					
					// Priority enqueue
					cpuList[i].priorityEnqueue( a );
				}
				else // else the job need to be sent back to the wait list
				{
					// If it's a CPU job, reset the flag
					if( a.getJobType() == CPU ) a.setLastService(false);
					waitList.enqueue( a );
				}
			}
			else
			{
				// Increase CPU idle time
				cpuIdle += 0.1f;
			}
		}
		
		
		// Increment the time counter
		currentTime += 0.1f;
		
		cout << currentTime << "   " << jobsDone << endl;
	}
	
	float CPUPercentBusy = ( (numberOfCPUs * currentTime) - cpuIdle ) / (numberOfCPUs * currentTime) * 100;
	float thruPut = numberOfJobs / (currentTime / 3600);
	float avgWait = (timeInWait / numberOfJobs ) / 10;
		if( timeInWait == 0.0f ) avgWait = 0.0f;
	float avgCPU = (timeInCPU / numberOfJobs )/10;
		if( timeInCPU == 0.0f ) avgCPU = 0.0f;

	
	cout << "Simulation Over" << endl
		<< "Simulation Time: " << currentTime << endl << endl
		<< "Number of IO Jobs: " << numberOfIOJobs << endl
		<< "Number of CPU Jobs: " << numberOfCPUJobs << endl
		<< "Number of 10s Jobs: " << numberOf10 << endl
		<< "Number of 20s Jobs: " << numberOf20 << endl
		<< "Number of 30s Jobs: " << numberOf30 << endl
		<< "Number of 60s Jobs: " << numberOf60 << endl << endl
		<< "Percent of time CPU Busy: " << CPUPercentBusy << endl
		<< "Through-put: " << thruPut << " jobs/hour" << endl
		<< "Average Time in Wait Queue: " << avgWait << "s" << endl
		<< "Average Time in CPU Queue: " << avgCPU << "s" << endl;
		
		
}
