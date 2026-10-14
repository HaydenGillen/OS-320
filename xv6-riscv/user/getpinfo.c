#include "kernel/pstat.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void main(){
    struct pstat ps;
    while (1){
        for(long long i = 0; i < 999999999; i++) {volatile int x = x + 1;}
        getpinfo(&ps);
        for(int i = 0; i < NPROC; i++){
        if (ps.inuse[i])
            printf("pid: %d,  \t runtime: %d,\t pass: %d,\t stride: %d\n", 
                    ps.pid[i], ps.runtime[i], ps.pass[i], ps.stride[i]);
        }
        printf("pass total: %d\n\n", ps.syspasses);
    }
}
