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

    quit [kill]
        do serial instead of transverse
        do need to terminate ^z (stopped) signals
        tests
            quit works
            args check works
    kill
        do check core dump
        tests
            check works
            -8 -9 works on stopped and on running processes

jobs_manger
    
				if(waitpid(pID, &child_status, 0) == -1)
					if(WIFSTOPPED(child_status))
						
					else
						PERROR_MSG(waitpid);

				wait(NULL);

im giving you my project. its not finished yet. please read and learn it.
reply with "ok."
read it more, really understand the project and remember all its logic.

