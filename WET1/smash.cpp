/*	smash.cpp
main file. This file contains the main function of smash
*******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include "commands.h"
#include "signals.h"
#define MAX_LINE_SIZE 80
#define MAXARGS 20
#define MAX_PATH_SIZE 80
char* L_Fg_Cmd;
jobs_manager JobsManager; //our implamentation //This represents the list of jobs. Please change to a preferred type (e.g array of char*)
char lineSize[MAX_LINE_SIZE]; 
//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    char cmdString[MAX_LINE_SIZE]; 	   

	
	//signal declaretions
	//! add syscall error case
	signal(SIGTSTP, handler_ctrlz);
	signal(SIGINT, handler_ctrlc);
	
	
    	while (1)
    	{
	 	printf("smash > ");
		fgets(lineSize, MAX_LINE_SIZE, stdin);
		strcpy(cmdString, lineSize);    	
		cmdString[strlen(lineSize)-1]='\0';
					// background commands	
	 	if(!BgCmd(lineSize, JobsManager)) continue; 
					// built in commands
		ExeCmd(JobsManager, lineSize, cmdString);
		
		/* initialize for next line read*/
		lineSize[0]='\0';
		cmdString[0]='\0';
	}
    return 0;
}
