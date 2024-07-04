// signals.cpp
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_ctrlc
   Synopsis: handle the Control-C */
#include "signals.h"
//! behavior is probably not correct!
pid_t child_pid = -1;

void handler_ctrlc(int child_pid){
   cout << "smash: caught ctrl-C" << endl;
   if(child_pid != -1){
      if(kill(child_pid, SIGKILL) == -1)
         PERROR_MSG(kill);
      else
         cout << "\nsmash: process " << child_pid << "was killed" << endl;
      child_pid = -1;
   }
} 
void handler_ctrlz(int child_pid){
   cout << "smash: caught ctrl-Z" << endl;
   if(child_pid != -1){ 
      if(kill(child_pid, SIGSTOP) == -1)
         PERROR_MSG(kill);
      else
         cout << "\nsmash: process " << child_pid << "was stopped" << endl;
      child_pid = -1;
   } 
}