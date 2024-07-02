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
#include <job.h>
#endif
using namespace std;

class jobs_manager{
public:
    //members
    vector<job> jobs_list;

    //functions
    //constructor
    jobs_manager(){};
    //destrator
    ~jobs_manager(){};
    //print the list for jobs
    void print_jobs_list();
    //external & case or ^Z case
    void add_job_to_list(int job_id, string command, int process_id, time_t seconds_elapsed, State state);
};