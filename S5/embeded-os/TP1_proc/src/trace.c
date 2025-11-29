#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/user.h>
#include <sys/syscall.h>    /* For SYS_write etc */
#include <sys/reg.h>        /* For ORIG_RAX, RDI, RSI, RDX, RAX */

int main()
{   
    pid_t child;
    long orig_rax, rax;
    long params[3];
    int status;
    int insyscall = 0;
    child = fork();
    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/bash", "write.sh", NULL);
    }
    else {
        while(1) {
            wait(&status);
            if(WIFEXITED(status)) { 
                break; 
            }
            orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
            if(orig_rax == SYS_write) {
                if(insyscall == 0) {
                    /* Syscall entry */
                    insyscall = 1;
                    // Correction : params dans RDI, RSI, RDX pour x86_64
                    params[0] = ptrace(PTRACE_PEEKUSER, child, 8 * RDI, NULL);  // fd
                    params[1] = ptrace(PTRACE_PEEKUSER, child, 8 * RSI, NULL);  // buf
                    params[2] = ptrace(PTRACE_PEEKUSER, child, 8 * RDX, NULL);  // count
                    printf("Write called with %ld, %ld, %ld\n", params[0], params[1], params[2]);
                } else { 
                    /* Syscall exit */
                    rax = ptrace(PTRACE_PEEKUSER, child, 8 * RAX, NULL);
                    printf("Write returned with %ld\n", rax);
                    insyscall = 0;
                }
            }
            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
        }
    }
    return 0;
}