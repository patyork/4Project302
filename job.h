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
		double timeRequired;
		
		// Time it has been serviced so far
		double timeServiced;
		
		// Arrival Time
		double arrivalTime;
		
		// Completion Time
		double completionTime;
		
		// Is this the last time this job needs to be serviced?
		bool last;
	
	public:
		
		// Default constructor
		job();
		
		// Parameterized Constructor
		job( int num, jobType type, double timeReq, double timeServd, double timeArrive, double timeCompleted, bool f );
	
	  //getters
		// Return the Job Numer
		int getJobNumber() const;
		
		// Return the Job Type
		jobType getJobType() const;
		
		// Return the time this job requires
		double getTimeRequired() const;
		
		//Return the time this job has been serviced thus far
		double getTimeServiced() const;
		
		//Return the arrival time of this job
		double getArrivalTime() const;
		
		// Return the completion time of this job
		double getCompletionTime() const;
		
		// Return whether this is the first time this job has been serviced this timeslice
		bool lastService() const;
		
	  //setters
	  	// Set the job number
	  	void setJobNumber( int jn );
	  	
	  	//Set the job type
	  	void setJobType( jobType t );
	  	
	  	//Set the amount time required for this job
	  	void setTimeRequired( double t );
	  	
	  	// Set the amount of time this job has been serviced thus far
	  	void setTimeServiced( double t );
	  	
	  	// Increment the time this job has been serviced by .1
	  	void incrementTimeServiced();
	  	
	  	// Set the arrival time of this job
	  	void setArrivalTime( double t );
	  	
	  	// Set the Completion time of this job
	  	void setCompletionTime( double t );
	  	
	  	// Set whether this is the first time this job had been serviced this timeslice
	  	void setLastService( bool l );
	  	
	  	
	
};

#endif
