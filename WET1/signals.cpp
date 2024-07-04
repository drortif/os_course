// signals.cpp
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_ctrlc
   Synopsis: handle the Control-C */
#include "signals.h"
#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstring>

pid_t child_pid = -1;

void handler_ctrlc(int sig){
   if(child_pid != -1){
      std::cout << "smash: caught ctrl-C" << std::endl;
      std::cout << "\nsmash: process " << child_pid << "was killed" << std::endl;
      kill(child_pid, SIGKILL);
      child_pid = -1;
   }
} 
void handler_ctrlz(int sig){
   if(child_pid != -1){ 
      std::cout << "smash: caught ctrl-Z" << std::endl;
      std::cout << "\nsmash: process " << child_pid << "was stopped" << std::endl;
      //to check with dror: how to update the job list --------------------------------------------TO DOOOO-----------
      
      kill(child_pid, SIGKILL);
      child_pid = -1;
   } 
}