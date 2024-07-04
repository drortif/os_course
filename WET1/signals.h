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

extern pid_t child_pid;

void handler_ctrlc(int sig);
void handler_ctrlz(int sig);

#endif

