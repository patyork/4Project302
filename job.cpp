
#include "job.h"

		
// Default constructor
job::job()
{
	number = -1;
	jobClass = IO;
	timeRequired = -1.0f;
	timeServiced = -1.0f;
	arrivalTime = -1.0f;
	completionTime = -1.0f;
	last = true;
}
		
// Parameterized Constructor
job::job( int num, jobType type, double timeReq, double timeServd, double timeArrive, double timeCompleted, bool f )
{
	number = num;
	jobClass = type;
	timeRequired = timeReq;
	timeServiced = timeServd;
	arrivalTime = timeArrive;
	completionTime = timeCompleted;
	last = f;
}
	
// Return the Job Numer
int job::getJobNumber() const
{
	return number;
}
		
// Return the Job Type
jobType job::getJobType() const
{
	return jobClass;
}
		
// Return the time this job requires
double job::getTimeRequired() const
{
	return timeRequired;
}
		
//Return the time this job has been serviced thus far
double job::getTimeServiced() const
{
	return timeServiced;
}
		
//Return the arrival time of this job
double job::getArrivalTime() const
{
	return arrivalTime;
}
		
// Return the completion time of this job
double job::getCompletionTime() const
{
	return completionTime;
}
		
// Return whether this is the first time this job has been serviced this timeslice
bool job::lastService() const
{
	return last;
}
		
// Set the job number
void job::setJobNumber( int jn )
{
	number = jn;
}
	  	
//Set the job type
void job::setJobType( jobType t )
{
	jobClass = t;
}
	  	
//Set the amount time required for this job
void job::setTimeRequired( double t )
{
	timeRequired = t;
}
	  	
// Set the amount of time this job has been serviced thus far
void job::setTimeServiced( double t )
{
	timeServiced = t;
}

// Increment the time this job has been serviced by .1
void job::incrementTimeServiced()
{
	timeServiced += 0.1f;
}
	  	
// Set the arrival time of this job
void job::setArrivalTime( double t )
{
	arrivalTime = t;
}
	  	
// Set the Completion time of this job
void job::setCompletionTime( double t )
{
	completionTime = t;
}
	  	
// Set whether this is the first time this job had been serviced this timeslice
void job::setLastService( bool l )
{
	last = l;
}
	  	

