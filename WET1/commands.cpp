//		commands.cpp
//*********************************************************************************************
#include "commands.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
//*********************************************************************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//*********************************************************************************************
int ExeCmd(void* jobs, char* lineSize, char* cmdString)
{
	char* cmd; 
	char* args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
	char* delimiters = " \t\n";  
	int i = 0, num_arg = 0;
	bool illegal_cmd = false; // illegal command
    	cmd = strtok(lineSize, delimiters);
	if (cmd == NULL)
		return 0; 
   	args[0] = cmd;
	for (i=1; i<MAX_ARG; i++)
	{
		args[i] = strtok(NULL, delimiters); 
		if (args[i] != NULL) 
			num_arg++; 
 
	}
/**************************************************************************************************/
// Built in Commands PLEASE NOTE NOT ALL REQUIRED
// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
// MORE IF STATEMENTS AS REQUIRED
/**************************************************************************************************/
	if (!strcmp(cmd, "cd") ) 
	{

		//args overload case
		if(num_arg>1)
			std::cerr << "smash error: cd: too many arguments" << std::endl;
		
		//valid amount of args case
		else{
			char old_cwd[MAX_PATH_SIZE];
			if(getcwd(old_cwd, sizeof(old_cwd)) == NULL)
				perror("smash error: getcwd failed");

			// - case
			if(!strcmp(args[1], "-")){
				
				if(chdir("..")!=0)
					perror("smash error: chdir failed");

				else{
					char new_cwd[MAX_PATH_SIZE];
					if(getcwd(new_cwd, sizeof(new_cwd)) == NULL)
						perror("smash error: getcwd failed");
						
					//root case
					if(!strcmp(old_cwd, new_cwd))
						std::cerr << "smash error: cd: OLDPWD not set" << std::endl;

				}
			
			}
			// relative or full path
			else{
				if(chdir(args[1])!=0)
					perror("smash error: chdir failed");
			}
		}
	}
	
	/**************************************************************************************************/
	else if (!strcmp(cmd, "pwd")) 
	{
		char cwd[MAX_PATH_SIZE];
		if(getcwd(cwd, sizeof(cwd)) != NULL){
			std::cerr << cwd << std::endl;
		}
		else
			perror("smash error: getcwd failed");
	}
	
	/**************************************************************************************************/
	else if (!strcmp(cmd, "diff"))
	{
 		if(num_arg != 2)
			std::cerr << "smash error: diff: invalid arguments" << std::endl;

		//compare between the files
		else{

		}
	}
	/**************************************************************************************************/
	
	else if (!strcmp(cmd, "jobs")) 
	{
 		
	}
	/**************************************************************************************************/
	else if (!strcmp(cmd, "showpid")) 
	{
		
	}
	/**************************************************************************************************/
	else if (!strcmp(cmd, "fg")) 
	{
		
	} 
	/**************************************************************************************************/
	else if (!strcmp(cmd, "bg")) 
	{
  		
	}
	/**************************************************************************************************/
	else if (!strcmp(cmd, "kill"))
	{
   		
	} 
	/**************************************************************************************************/
	else if (!strcmp(cmd, "quit"))
	{
   		
	} 
	/**************************************************************************************************/
	
	else // external command
	{
 		ExeExternal(args, cmdString);
	 	return 0;
	}
	if (illegal_cmd == true)
	{
		printf("smash error: > \"%s\"\n", cmdString);
		return 1;
	}
    return 0;
}
//***************************************************************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//***************************************************************************************************************************************
void ExeExternal(char *args[MAX_ARG], char* cmdString)
{
	int pID;
    	switch(pID = fork()) 
	{
    		case -1: 
					// Add your code here (error)
					
					/* 
					your code
					*/
        	case 0 :
                	// Child Process
               		setpgrp();
					
			        // Add your code here (execute an external command)
					
					/* 
					your code
					*/
			
			//default:
                	// Add your code here
					
					/* 
					your code
					*/
	}
}

//***************************************************************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//***************************************************************************************************************************************
int BgCmd(char* lineSize, void* jobs)
{

	char* Command;
	char* delimiters = " \t\n";
	char *args[MAX_ARG];
	if (lineSize[strlen(lineSize)-2] == '&')
	{
		lineSize[strlen(lineSize)-2] = '\0';
		// Add your code here (execute a in the background)
					
		/* 
		your code
		*/
		
	}
	return -1;
}

