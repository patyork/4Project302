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
		double probOne;
		
		// Probability of two jobs entering the system
		double probTwo;
		
		// Distribution of required times
		double distTimes[4];
		
		// Distribution of job types
		double distTypes[2];
		
		// The number of CPUs
		int numberOfCPUs;
		
		// Output File stream for CpuSim.out
		std::ofstream oFile;
		
		// Whether there is an empty spot in any of the CPU queues
		bool isEmptyinCPUs( jobQueue cpu[] );
		
		// Create a new job (but don't enqueue it)
		job createRandomJob( double currTime, int jobNum );
	
	public:
	
		// Constructor
		simulation();
	
		// Initialize the simulation
		void init();
		
		// Run the simulation
		void run();
};


#endif
