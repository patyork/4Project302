#ifndef SIMULATION_H
#define SIMULATION_H

#include "jobQueue.h"
#include <fstream>

class simulation
{
	private:
	
		// Number of jobs to be executed
		int numberOfJobs;
		
		// Probability of one job entering the system
		float probOne;
		
		// Probability of two jobs entering the system
		float probTwo;
		
		// Distribution of required times
		float distTimes[4];
		
		// Distribution of job types
		float distTypes[2];
		
		// The number of CPUs
		int numberOfCPUs;
		
		// Output File stream for CpuSim.out
		std::ofstream oFile;
		
		// Whether there is an empty spot in any of the CPU queues
		bool isEmptyinCPUs( jobQueue cpu[] );
		
		// Create a new job (but don't enqueue it)
		job createRandomJob( float currTime, int jobNum );
	
	public:
	
		// Constructor
		simulation();
	
		// Initialize the simulation
		void init();
		
		// Run the simulation
		void run();
};


#endif
