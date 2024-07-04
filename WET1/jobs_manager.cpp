#include "jobs_manager.h"


void jobs_manager::add_job_to_list(int job_id, string command, int process_id, time_t start_time, State state){
    this->jobs_list.push_back(job(command, job_id, process_id, start_time, state));
}

void jobs_manager::print_jobs_list(){
    for(vector<job>::iterator entry = this->jobs_list.begin(); entry != this->jobs_list.end(); entry++){
        //calc elapsed time
        //! add syscall error case
        time_t seconds_elapsed = difftime(time(NULL), entry->start_time);

        switch (entry->state)
        {
        case stopped:
            cout << entry->job_id <<" " << entry->command <<" : "<<entry->process_id<<seconds_elapsed<<" (stopped)"<< endl;
            break;
        
        case background:
            cout << entry->job_id <<" " << entry->command <<" : "<<entry->process_id<<seconds_elapsed<< endl;
            break;
        }
    }
}

//going through all of the jobs in the list and checking if their status has changed
//if it did, updates the list according to the case.
void jobs_manager::update_list(){
    int child_status;
    for(vector<job>::iterator entry = this->jobs_list.begin(); entry != this->jobs_list.end(); entry++){
        switch (waitpid(entry->process_id, &child_status, WNOHANG))
        {
        //syscall error
        case -1:
            PERROR_MSG(waitpid);
            break;

        //job has not finished yet
        case 0:
            break;

        // jobs status has changed- exited or stopped
        default:
            //! if preemption or whatever has occured like timeout, IO?

            //! possible errors: ^z case - changing status here!
            // * no need to kill, this code runs retrospectivly.
            if(WTERMSIG(child_status) == SIGTSTP){
				entry->state = stopped;
			}
            //! possible errors: ^c case, or job exited (finished, naturally or not)
            else{
                this->remove_job_from_list(entry->job_id);
            }
            break;
        }
    }
}

void jobs_manager::remove_job_from_list(int job_id_to_erase){
    for(vector<job>::iterator entry = this->jobs_list.begin(); entry != this->jobs_list.end(); entry++){
        if(entry->job_id == job_id_to_erase){
            this->jobs_list.erase(entry++);
            break;
        }
    }
    set_highest_job_id();
}

void jobs_manager::set_highest_job_id(){

    if(this->jobs_list.begin() == this->jobs_list.end())
        this->highest_job_id = 0;
    else
        this->highest_job_id = this->jobs_list.end()->job_id;
}

