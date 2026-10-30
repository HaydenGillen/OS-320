# Page Tables
## pt 1
I used the freewalk function to model my function after. it measures the level of recursive depth and does different prints based on it's recursive depth. it implements the same logic of if page is valid, lets print, and if it points to a lower level page we call it again on that lower level page with an incremented depth/level counter. to test I ran xv6 and looked at the result.

## pt 2
I made the syscall pgaccess and it creates an empty bit field variable thing and loops through the number of pages requested or the max size of our bitfield if the user requested too many pages. then we use walk to get the PTE and use the bit mask to see if the page has been accessed. then we use the bit mask to unset the bit as well. then each loop we increment our address by the PGSIZE and repeat. to test I used the provided test code and messed with which pages are accessed in the test code and saw if my pgaccess provided what I expected. I did all pages, every other page, and just the first page, results were as expected.

## pt 3
I placed the USYSCALL just above the trap frame in memlayout, I copied the memory map functions of the trapframe for the usyscall (this is in alloc proc and free proc pagetable ). when the process is allocated we also allocate the usyscall struct and put the pid in there as well as set that page to be read only and user accessible using the PTE_R and PTE_U bit masks. then I wrote a function declared in user.h and defined in ulib.c that reads the memory and returns the pid. I think i called it usyscallgetpid. to test I wrote some test code that prints usyscallgetpid() and getpid(), I ran it a few times and the pids were always the same

# Stride Scheduling
<img width="332" height="91" alt="image" src="https://github.com/user-attachments/assets/66211577-1a9f-4b46-8e06-9b9572935bfa" />

We see that after running for a while, the pass categories all even out and remain relatively similar. all of these processes started at the same time, we see that the PID with stride 1 is scheduled about 10 times as often as as the PID with 10 stride. We see that (PID A Stride / PID B Stride) ≈ (PID B Runtime / PID A Runtime) holds true for all combinations of A and B from our data. This is what we would expect because if we add 10 to pass for PID B with 10 stride, we need to run PID A 10 times at one stride per pass to get to 10 where PID B can run again.

<img width="332" height="49" alt="image" src="https://github.com/user-attachments/assets/6b0cecc4-b41e-4bad-868f-32dff288c56e" />
<br>
<img width="334" height="48" alt="image" src="https://github.com/user-attachments/assets/38de7544-4e9a-4dcc-91d0-f6b778f02457" />
<br>
<img width="352" height="50" alt="image" src="https://github.com/user-attachments/assets/e6b364ac-d0bf-4c0a-903f-c230bdb41638" />

We also see when a new process enters the system it dominates the cpu because it has not accumulated much pass and will be the lowest pass until it catches up with process already in the system. we see PID 9 above enter the system and the following 3 processes do not run again until PID 9 accumulates the same amount of pass and then cpu time is distributed among proceeses according to their stride.

<br>Files Modified
<br>    To add new syscalls for getpinfo and setstride
<br>        -modified:   kernel/syscall.c
<br>        -modified:   kernel/syscall.h
<br>        -modified:   kernel/sysproc.c
<br>        -modified:   user/user.h
<br>        -modified:   user/usys.pl
<br>    Test Files for the user to determine if stride scheduling works
<br>        -new file:   user/getpinfo.c - I made mine spin and every so often print
<br>        -new file:   kernel/pstat.h
<br>        -new file:   user/hardwork.c
<br>    Stride Scheduler
<br>        -modified:   Makefile
<br>        -modified:   kernel/defs.h
<br>        -modified:   kernel/proc.c
<br>        -modified:   kernel/proc.h

What I did
I added runtime to the process struct so that it could be tracked every time the process is put on the cpu. then I made the getpinfo syscall with the pstat struct. I also added   int pass[NPROC]; // the number of strides each process has accumulated, int stride[NPROC]; // stride length of each process, and int syspasses; // total system passes so that it would be more clear what was happening with the passes and strides of each process when calling getpinfo. I also added stride and pass to the process struct. In allocproc, stride defaults to 1, pass is set to 0, and runtime is set to 0. Then I implemented the stride scheduler portion. It loops through each process and grabs the processes lock. if the process has the lowest pass it releases the lock of the last lowest pass we identified and continues. if the process does not have the lowest pass the lock is released. this way we always have the lock of the lowest pass from the moment we look at it. then it switches processes and releases the lock. Also before looping through the processes, it checks if our pass total is greater than the max which I defined in defs.h. If it is greater then we set all process pass values to 0 and the total pass to 0. I also set CPU to one and changed the Makefile so that my c files would be compiled in.
