// signals.cpp
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_ctrlc
   Synopsis: handle the Control-C */
#include "signals.h"
//! behavior is probably not correct!
int child_pid_in_fg = -1;

void handler_ctrlc(int signal){
   cout << "smash: caught ctrl-C" << endl;
   if(child_pid_in_fg != -1){
      if(kill(child_pid_in_fg, SIGKILL) == -1)
         PERROR_MSG(kill);
      else
         cout << "\nsmash: process " << child_pid_in_fg << " was killed" << endl;
      child_pid_in_fg = -1;
   }
}

void handler_ctrlz(int signal){
   cout << "smash: caught ctrl-Z" << endl;
   if(child_pid_in_fg != -1){ 
      if(kill(child_pid_in_fg, SIGSTOP) == -1)
         PERROR_MSG(kill);
      else
         cout << "\nsmash: process " << child_pid_in_fg << " was stopped" << endl;
      child_pid_in_fg = -1;
   } 
}