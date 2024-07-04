Q: behavior of system call fail?
Q: csingnal library use?
Q: sigstop error?
Q: time() error

built ins
    pwd
        errors
            done
            do? max path size
        tests
            trivial
    
    cd
        errors
            done
            do 
            do? fewer args
        tests
            printed all errors
            relative path
            full path
            -
    
    diff 
        errors
            done
        do check if works after changing to open
        
    fg


jobs_manger
    
				if(waitpid(pID, &child_status, 0) == -1)
					if(WIFSTOPPED(child_status))
						
					else
						PERROR_MSG(waitpid);

				wait(NULL);