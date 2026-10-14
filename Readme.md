# Stride Scheduling
<img width="332" height="91" alt="image" src="https://github.com/user-attachments/assets/66211577-1a9f-4b46-8e06-9b9572935bfa" />

We see that after running for a while, the pass categories all even out and remain relatively similar. all of these processes started at the same time, we see that the PID with stride 1 is scheduled about 10 times as often as as the PID with 10 stride. We see that (PID A Stride / PID B Stride) ≈ (PID B Runtime / PID A Runtime) holds true for all of these combinations. This is what we would expect because if we add 10 to pass for PID B with 10 stride, we need to run PID A 10 times at one stride per pass to get to 10 where PID B can run again.
