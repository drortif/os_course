#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#define MAX_LINE_SIZE 80
#define MAX_PATH_SIZE 80
#define MAX_ARG 20
#define PERROR_MSG(sys_call) perror("smash error: " #sys_call " failed")
int ExeComp(char* lineSize);
int BgCmd(char* lineSize, void* jobs);
int ExeCmd(void* jobs, char* lineSize, char* cmdString);
void ExeExternal(char *args[MAX_ARG], char* cmdString);
#endif

