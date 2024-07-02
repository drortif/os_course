//		commands.cpp
//*********************************************************************************************
#include "commands.h"

//*********************************************************************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//*********************************************************************************************
int ExeCmd(jobs_manager& JobsManager, char* lineSize, char* cmdString)
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
			cerr << "smash error: cd: too many arguments" << endl;
		
		//valid amount of args case
		else{
			char old_cwd[MAX_PATH_SIZE];
			if(getcwd(old_cwd, sizeof(old_cwd)) == NULL)
				PERROR_MSG(getcwd);

			// - case
			if(!strcmp(args[1], "-")){
				
				if(chdir("..")!=0)
					PERROR_MSG(chdir);

				else{
					char new_cwd[MAX_PATH_SIZE];
					if(getcwd(new_cwd, sizeof(new_cwd)) == NULL)
						PERROR_MSG(getcwd);
						
					//root case
					if(!strcmp(old_cwd, new_cwd))
						cerr << "smash error: cd: OLDPWD not set" << endl;

				}
			
			}
			// relative or full path
			else{
				if(chdir(args[1])!=0)
					PERROR_MSG(chdir);
			}
		}
	}
	
	/**************************************************************************************************/
	else if (!strcmp(cmd, "pwd")) 
	{
		char cwd[MAX_PATH_SIZE];
		if(getcwd(cwd, sizeof(cwd)) != NULL){
			cerr << cwd << endl;
		}
		else
			PERROR_MSG(getcwd);
	}
	
	/**************************************************************************************************/
	else if (!strcmp(cmd, "diff")) 
	{
 		if(num_arg != 2)
			cerr << "smash error: diff: invalid arguments" << endl;

		//compare between the files
		else{

		}
	}
	/**************************************************************************************************/
	
	else if (!strcmp(cmd, "jobs")) 
	{
 		JobsManager.print_jobs_list();
	}
	/**************************************************************************************************/
	else if (!strcmp(cmd, "showpid")) 
	{
		cerr << "smash pid is " << getpid() << endl;
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
				//error
				PERROR_MSG(fork);

        	case 0:
                // Child Process - execute an external command
               	setpgrp();
				execvp(cmdString, args);
				PERROR_MSG(execvp);
				exit(1);
			default:
                // father process - smash
				wait(NULL);
				return;
					
	}
}

//***************************************************************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//***************************************************************************************************************************************
int BgCmd(char* lineSize, jobs_manager* JobsManager)
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

