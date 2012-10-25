
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
	first = true;
}
		
// Parameterized Constructor
job::job( int num, jobType type, float timeReq, float timeServd, float timeArrive, float timeCompleted, bool f )
{
	number = num;
	jobClass = type;
	timeRequired = timeReq;
	timeServiced = timeServd;
	arrivalTime = timeArrive;
	completionTime = timeCompleted;
	first = f;
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
float job::getTimeRequired() const
{
	return timeRequired;
}
		
//Return the time this job has been serviced thus far
float job::getTimeServiced() const
{
	return timeServiced;
}
		
//Return the arrival time of this job
float job::getArrivalTime() const
{
	return arrivalTime;
}
		
// Return the completion time of this job
float job::getCompletionTime() const
{
	return completionTime;
}
		
// Return whether this is the first time this job has been serviced this timeslice
bool job::firstService() const
{
	return first;
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
void job::setTimeRequired( float t )
{
	timeRequired = t;
}
	  	
// Set the amount of time this job has been serviced thus far
void job::setTimeServiced( float t )
{
	timeServiced = t;
}
	  	
// Set the arrival time of this job
void job::setArrivalTime( float t )
{
	arrivalTime = t;
}
	  	
// Set the Completion time of this job
void job::setCompletionTime( float t )
{
	completionTime = t;
}
	  	
// Set whether this is the first time this job had been serviced this timeslice
void job::setFirstService( bool f )
{
	first = f;
}
	  	

