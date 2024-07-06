#ifndef _SIGS_H
#define _SIGS_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <csignal>
#include <iostream>
#include <csignal>
#include <cstring>
#define PERROR_MSG(sys_call) perror("smash error: " #sys_call " failed")
using namespace std;

extern int child_pid_in_fg;
void handler_ctrlc(int sig);
void handler_ctrlz(int sig);

#endif

