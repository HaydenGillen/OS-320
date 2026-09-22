#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = 100;
    int parent_pid = getpid();
    printf("pre-fork %x: %d\n", parent_pid, x);

    fork();
    if (getpid() == parent_pid) {
        // parent process
        printf("Parent %x: %d\n", getpid(), x);
        x = 500;
        printf("Parent %x: %d\n", getpid(), x);
    }
    else {
        // child process
        printf("Child %x: %d\n", getpid(), x);
        x = 300;
        printf("Child %x: %d\n", getpid(), x);
    }
}
