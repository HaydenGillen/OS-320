# Stride Scheduling
<img width="332" height="91" alt="image" src="https://github.com/user-attachments/assets/66211577-1a9f-4b46-8e06-9b9572935bfa" />

We see that after running for a while, the pass categories all even out and remain relatively similar. all of these processes started at the same time, we see that the PID with stride 1 is scheduled about 10 times as often as as the PID with 10 stride. We see that (PID A Stride / PID B Stride) ≈ (PID B Runtime / PID A Runtime) holds true for all combinations of A and B from our data. This is what we would expect because if we add 10 to pass for PID B with 10 stride, we need to run PID A 10 times at one stride per pass to get to 10 where PID B can run again.

<img width="332" height="49" alt="image" src="https://github.com/user-attachments/assets/6b0cecc4-b41e-4bad-868f-32dff288c56e" />
<br>
<img width="334" height="48" alt="image" src="https://github.com/user-attachments/assets/38de7544-4e9a-4dcc-91d0-f6b778f02457" />
<br>
<img width="352" height="50" alt="image" src="https://github.com/user-attachments/assets/e6b364ac-d0bf-4c0a-903f-c230bdb41638" />

We also see when a new process enters the system it dominates the cpu because it has not accumulated much pass and will be the lowest pass until it catches up with process already in the system. we see PID 9 above enter the system and the following 3 processes do not run again until PID 9 accumulates the same amount of pass and then cpu time is distributed among proceeses according to their stride.

Files Modified
    To add new syscalls for getpinfo and setstride
        modified:   kernel/syscall.c
        modified:   kernel/syscall.h
        modified:   kernel/sysproc.c
        modified:   user/user.h
        modified:   user/usys.pl
    Test Files for the user to determine if stride scheduling works
        new file:   user/getpinfo.c - I made mine spin and every so often print
        new file:   kernel/pstat.h
        new file:   user/hardwork.c
    Stride Scheduler
        modified:   Makefile
        modified:   kernel/defs.h
        modified:   kernel/proc.c
        modified:   kernel/proc.h

What I did
I added runtime to the process struct so that it could be tracked every time the process is put on the cpu. then I made the getpinfo syscall with the pstat struct. I also added   int pass[NPROC]; // the number of strides each process has accumulated, int stride[NPROC]; // stride length of each process, and int syspasses; // total system passes so that it would be more clear what was happening with the passes and strides of each process when calling getpinfo. I also added stride and pass to the process struct. In allocproc, stride defaults to 1, pass is set to 0, and runtime is set to 0. Then I implemented the stride scheduler portion. It loops through each process and grabs the processes lock. if the process has the lowest pass it releases the lock of the last lowest pass we identified and continues. if the process does not have the lowest pass the lock is released. this way we always have the lock of the lowest pass from the moment we look at it. then it switches processes and releases the lock. Also before looping through the processes, it checks if our pass total is greater than the max which I defined in defs.h. If it is greater then we set all process pass values to 0 and the total pass to 0. I also set CPU to one and changed the Makefile so that my c files would be compiled in.
