//		commands.cpp
//*********************************************************************************************
#include "commands.h"
bool should_quit = false; //! temp
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
//! empty cd sigfault
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
			int fd1 = open(args[1], O_RDONLY);
    		int fd2 = open(args[2], O_RDONLY);

			if (fd1 < 0 || fd2 < 0) {
				PERROR_MSG(open);
				if (fd1 >= 0){
					if (close(fd1) != 0) {
						PERROR_MSG(close);
        				return false;
    				}
				}
				if (fd2 >= 0){
					if (close(fd2) != 0) {
						PERROR_MSG(close);
        				return false;
    				}
				}

				return false;
				}
			    const int bufferSize = 4096;
    			char buffer1[bufferSize], buffer2[bufferSize];
				size_t bytesRead1, bytesRead2;

				bool areFilesIdentical = true;
				do {
					bytesRead1 = read(fd1, buffer1, bufferSize);
       				bytesRead2 = read(fd2, buffer2, bufferSize);

					if (bytesRead1 < 0 || bytesRead2 < 0) {
           				PERROR_MSG(read);
            			areFilesIdentical = false;
            			return false;
					}
					if (bytesRead1 != bytesRead2 || memcmp(buffer1, buffer2, bytesRead1) != 0) {
						areFilesIdentical = false; // Files are different
            			break;
					}
				} while (bytesRead1 > 0 && bytesRead2 > 0);

				if (close(fd1) < 0) {
					PERROR_MSG(close);
        			return false;
				}	
				if (close(fd2) < 0) {
					PERROR_MSG(close);
        			return false;
				}	

				if (areFilesIdentical && bytesRead1 == 0 && bytesRead2 == 0) {
        			cout << "0" << endl; // Files are identical
    			} else {
        			cout << "1" << endl; // Files are different
    			}
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
		int job_id;
		int pID;
		int child_status;
		string cmd;
		switch (num_arg)
		{
		//given job id
		case 1:
			job_id = atoi(args[1]);
			//fg to the specific job
			if(JobsManager.is_job_in_list(job_id)){
				
				for(vector<job>::iterator entry = JobsManager.jobs_list.begin(); entry != JobsManager.jobs_list.end(); ++entry){
					if(entry->job_id == job_id){
						cmd = entry->command;
						cout<< cmd << " : " << job_id <<endl;
						pID = entry->process_id;
						child_pid_in_fg = pID;
					}
				}
				if (kill(pID, SIGCONT) < 0)
        			PERROR_MSG(kill);
				
				//removes job from the list
				JobsManager.remove_job_from_list(job_id);

				if (waitpid(pID, &child_status, WUNTRACED) == -1)
        			PERROR_MSG(waitpid);
				
				//if ^z was caught
				if(WSTOPSIG(child_status) == SIGSTOP){
					JobsManager.update_list();
					//! time may not be correct
					JobsManager.add_job_to_list(cmd,pID,time(NULL), State::stopped);
				}
			}
			//no job with that job id
			else
				cerr << "smash error: fg: job-id " << job_id << " does not exist" << endl;
			break;

		//no args
		case 0:

			//fg to the last job in the list
			if(!JobsManager.jobs_list.empty()){
				pID = JobsManager.jobs_list.back().process_id;
				child_pid_in_fg = pID;
				cmd = JobsManager.jobs_list.back().command;
				job_id = JobsManager.jobs_list.back().job_id;
				if (kill(pID, SIGCONT) < 0)
        			PERROR_MSG(kill);
				
				//removes job from the list
				JobsManager.remove_job_from_list(job_id);

				if (waitpid(pID, &child_status, WUNTRACED) == -1)
        			PERROR_MSG(waitpid);
				//if ^z was caught
				if(WSTOPSIG(child_status) == SIGSTOP){
					JobsManager.update_list();
					//! time may not be correct
					JobsManager.add_job_to_list(cmd,pID,time(NULL), State::stopped);
				}
			}

			//no jobs in the list
			else
				cerr << "smash error: fg: jobs list is empty" << endl;
			break;

		//too many args
		default:
			cerr << "smash error: fg: invalid arguments" << endl;
			break;
		}
	} 
	/**************************************************************************************************/
	else if (!strcmp(cmd, "bg")) 
	{
  		int job_id;
		int pID;
		int child_status;
		string cmd;
		job *stopped_job = nullptr;
		switch (num_arg)
		{

		//given job id
		case 1:
			job_id = atoi(args[1]);
			//job is in the list
			if(JobsManager.is_job_in_list(job_id)){
				
				for(vector<job>::iterator entry = JobsManager.jobs_list.begin(); entry != JobsManager.jobs_list.end(); ++entry){
					if(entry->job_id == job_id){
						//resume stopped job with the given job id
						if(entry->state == stopped){
							cmd = entry->command;
							cout<< cmd << " : " << job_id <<endl;
							pID = entry->process_id;

							//resume it
							if (kill(pID, SIGCONT) < 0)
        						PERROR_MSG(kill);
							else
								entry->state = background;
						}

						//the given job is not in stopped state
						else{
							cerr << "smash error: bg: job-id " << job_id << " is already running in the background" << endl;
						}
					}
				}
			}

			//job is not o the list
			else{
				cerr << "smash error: bg: job-id " << job_id << " does not exist" << endl;
			}
			break;

		//no args
		case 0:

			//search for the stopped job with the highest job id
            for (vector<job>::iterator entry = JobsManager.jobs_list.begin(); entry != JobsManager.jobs_list.end(); ++entry){
                if(entry->state == stopped){
                    if (!stopped_job || entry->job_id > stopped_job->job_id) {
                        stopped_job = &(*entry);
                    }
                }
            }
			//resume stopped job with the highest job id 
			if(stopped_job){
				cmd = stopped_job->command;
				job_id = stopped_job->job_id;
				cout<< cmd << " : " << job_id <<endl;
				pID = stopped_job->process_id;
			
				//resume it
				if (kill(pID, SIGCONT) < 0)
					PERROR_MSG(kill);
				else
					stopped_job->state = background;
			}
			//no job in stopped state
			else{
				cerr << "smash error: bg: there are no stopped jobs to resume" << endl;
			}
			break;

		//too many args
		default:
			cerr << "smash error: bg: invalid arguments" << endl;
			break;
		}
	}
	/**************************************************************************************************/
	else if (!strcmp(cmd, "kill"))
	{
		// Check for valid number of arguments
        if (num_arg != 2 || args[1][0] != '-') {
            cerr << "smash error: kill: invalid arguments" << endl;
            return 1;
		}

		// Parse signal number
        int signum = atoi(args[1] + 1);
        if (signum <= 0) {
            cerr << "smash error: kill: invalid arguments" << endl;
            return 1;
        }

		// Parse job ID
        int job_id = atoi(args[2]);
        if (job_id <= 0) {
            cerr << "smash error: kill: invalid arguments" << endl;
            return 1;
        }

		// Find the job with the given job_id
        job* target_job = nullptr;
        for (auto& job : JobsManager.jobs_list) {
            if (job.job_id == job_id) {
                target_job = &job;
                break;
            }
        }
        if (!target_job) {
            cerr << "smash error: kill: job-id " << job_id << " does not exist" << endl;
            return 1;
        }

		// Send the signal to the process
       if (kill(target_job->process_id, signum) == -1) {
            perror("kill");
            return 1;
        }
        
        cout << "signal number " << signum << " was sent to pid " << target_job->process_id << endl;
		return 0;
	}
	/**************************************************************************************************/
	else if (!strcmp(cmd, "quit"))
	{
		//!temp
		if(args[1] == NULL || strcmp(args[1], "kill")){
   			should_quit = true;
    		return 0;
		}
		if(!strcmp(args[1], "kill")) {
			for (auto& job : JobsManager.jobs_list) {
            	if (job.state == background) {
					cout << "[" << job.job_id << "] " << job.command << " - Sending SIGTERM...";
                	kill(job.process_id, SIGTERM);
           		}
			}
		}
		
		// Wait for 5 seconds
        this_thread::sleep_for(chrono::seconds(5));

		bool allTerminated = true;
        for (auto& job : JobsManager.jobs_list) {
            if (job.state == background) {
                int status;
                pid_t result = waitpid(job.process_id, &status, WNOHANG);
                if (result == 0) {
                    allTerminated = false;
                } else {
                    job.state = stopped;  // Mark as stopped
                }
            }
        }

        if (allTerminated) {
            cout << "Done." << endl;
        } else {
            cout << "(5 sec passed) Sending SIGKILL...";
            for (auto& job : JobsManager.jobs_list) {
                if (job.state == background) {
                    kill(job.process_id, SIGKILL);
                }
            }

            for (auto& job : JobsManager.jobs_list) {
                if (job.state == background) {
                    int status;
                    waitpid(job.process_id, &status, 0);
                    job.state = stopped;  // Mark as stopped
                }
            }
            cout << "Done." << endl;
        }
		
		should_quit = true;
    	return 0;
	}
	/**************************************************************************************************/
	else // external command
	{
 		ExeExternal(args, cmdString, JobsManager);
	 	return 0;
	}
	/**************************************************************************************************/
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
//! get read of cmdString, only for illigal commands
void ExeExternal(char *args[MAX_ARG], char* cmdString, jobs_manager& JobsManager)
{
	int child_status;
	int pID;
    	switch(pID = fork()){
    		case -1: 
				//fork didnt work
				PERROR_MSG(fork);

        	case 0:
                // Child Process - execute an external command
               	setpgrp();
				execvp(args[0], args);
				PERROR_MSG(execvp);
				exit(1);
			default:
                //father process - smash
				//child runs in the fg
				child_pid_in_fg = pID;
				//child exited due to an error of the waitpid syscall
				if(waitpid(child_pid_in_fg, &child_status, WUNTRACED) == -1)
					PERROR_MSG(waitpid);

				//if ^z was caught
				if(WSTOPSIG(child_status) == SIGSTOP){
					JobsManager.update_list();
					//! time may not be correct
					JobsManager.add_job_to_list(cmdString,pID,time(NULL), State::stopped);
				}
				//if ^c was caught
				//if something else has interrupted the child process
				//if child exited normally
				break;
					
	}
}

//***************************************************************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//***************************************************************************************************************************************
int BgCmd(char* lineSize, jobs_manager& JobsManager, char* cmdString)
{

	char* Command;
	char* delimiters = " \t\n";
	char *args[MAX_ARG];
	int pID;
	if (lineSize[strlen(lineSize)-2] == '&')
	{
		//removing &
		lineSize[strlen(lineSize)-2] = '\0';
		
		//parsing the command line
		args[0] = strtok(lineSize, delimiters);
		for (int i=1; i<MAX_ARG; i++)
			args[i] = strtok(NULL, delimiters);
		
		switch(pID = fork()) 
		{
    		case -1: 
				//fork didnt work
				PERROR_MSG(fork);
				break;
        	case 0:
                // Child Process - execute an external command
               	setpgrp();
				execvp(args[0], args);
				PERROR_MSG(execvp);
				exit(1);

			default:
                //father process - smash
				//child runs in the bg
				//insert job to the list directly and carry on
				JobsManager.update_list();
				//! time may not be correct
				JobsManager.add_job_to_list(cmdString, pID, time(NULL), State::background);
				break;
					
		}
		return 1;
	}
	return 0;
}

