#include "jobs_manager.h"


void jobs_manager::add_job_to_list(int job_id, string command, int process_id, time_t seconds_elapsed, State state){
    jobs_list.push_back(job(command, job_id, process_id, seconds_elapsed, state));
}

void jobs_manager::print_jobs_list(){
    for(vector<job>::iterator entry = jobs_list.begin(); entry != jobs_list.end(); entry++){
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

