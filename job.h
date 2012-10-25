#ifndef JOB_H
#define JOB_H

enum jobType {IO,CPU};

class job
{
	private:
		// Job numer
		int number;
		
		// Type of job
		jobType jobClass;
		
		// Time Required
		float timeRequired;
		
		// Time it has been serviced so far
		float timeServiced;
		
		// Arrival Time
		float arrivalTime;
		
		// Completion Time
		float completionTime;
		
		// Is this the first time it's been serviced for this timeslice?
		bool first;
	
	public:
		
		// Default constructor
		job();
		
		// Parameterized Constructor
		job( int num, jobType type, float timeReq, float timeServd, float timeArrive, float timeCompleted, bool f );
	
	  //getters
		// Return the Job Numer
		int getJobNumber() const;
		
		// Return the Job Type
		jobType getJobType() const;
		
		// Return the time this job requires
		float getTimeRequired() const;
		
		//Return the time this job has been serviced thus far
		float getTimeServiced() const;
		
		//Return the arrival time of this job
		float getArrivalTime() const;
		
		// Return the completion time of this job
		float getCompletionTime() const;
		
		// Return whether this is the first time this job has been serviced this timeslice
		bool firstService() const;
		
	  //setters
	  	// Set the job number
	  	void setJobNumber( int jn );
	  	
	  	//Set the job type
	  	void setJobType( jobType t );
	  	
	  	//Set the amount time required for this job
	  	void setTimeRequired( float t );
	  	
	  	// Set the amount of time this job has been serviced thus far
	  	void setTimeServiced( float t );
	  	
	  	// Set the arrival time of this job
	  	void setArrivalTime( float t );
	  	
	  	// Set the Completion time of this job
	  	void setCompletionTime( float t );
	  	
	  	// Set whether this is the first time this job had been serviced this timeslice
	  	void setFirstService( bool f );
	  	
	  	
	
};

#endif
