#ifndef _JOB_LIST_H
#define _JOB_LIST_H
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "job.h"
#define PERROR_MSG(sys_call) perror("smash error: " #sys_call " failed")
#endif
using namespace std;

class jobs_manager{
public:
    //members
    vector<job> jobs_list;
    int highest_job_id;
    //functions
    //constructor
    jobs_manager(){};

    //destrator
    ~jobs_manager(){};

    //print the list for jobs
    void print_jobs_list();

    //external & case or ^Z case
    void add_job_to_list(string command, int process_id, time_t seconds_elapsed, State state);
    
    //handles jobs in the list (any status change) - called before:
    //1. running a new command
    //2. printing the list
    //3. adding a new job to the list
    void update_list();

    //called in remove_job_from_list
    void set_highest_job_id();

    //called in update_list
    vector<job>::iterator remove_job_from_list(int job_id_to_erase);
};