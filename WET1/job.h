#ifndef _JOB_H
#define _JOB_H
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <ctime> //! check if allowed to use
using namespace std;

enum State {
    foreground = 1,
    background = 2,
    stopped = 3
};


class job{
public:
    //members
    string command;
    int job_id;
    int process_id;
    time_t start_time;
    State state;
    
    //functions
    //constructor
    job(string command, int job_id, int process_id, time_t start_time, State state)
    : command(command), job_id(job_id), process_id(process_id), start_time(start_time), state(state){};

    //distructor
    ~job(){};
};
#endif // JOB_H