#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include "job.h"
#include "jobs_manager.h"
#include <fcntl.h> 
#define MAX_LINE_SIZE 80
#define MAX_PATH_SIZE 80
#define MAX_ARG 20
#define PERROR_MSG(sys_call) perror("smash error: " #sys_call " failed")
using namespace std;
extern bool should_quit; //! temp
int BgCmd(char* lineSize, jobs_manager& JobsManager);
int ExeCmd(jobs_manager& JobsManager, char* lineSize, char* cmdString);
void ExeExternal(char *args[MAX_ARG], char* cmdString, jobs_manager& JobsManager);
#endif

