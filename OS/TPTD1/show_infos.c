#include <unistd.h>
#include <stdio.h>

void main() {
    // getpid() returns the process ID of the calling process.

    int code_retour ;
    char cwd[1024];
    int euser; // effective user id
    int eguser; // effective group id
    int ruser; // real user id
    int rguser; // real group id
    int pid;
    int ppid;

    printf ("Debut du test info fork ()\n");
    code_retour = fork ();

    switch(code_retour){
        case -1:
            printf ("Pbm lors de la creation du processus\n");
            break;
        case 0:
            // fils :
            sleep(5); // rends orphelin
            pid = getpid();
            ppid = getppid();
            getcwd(cwd, sizeof(cwd));
            euser = geteuid();
            eguser = getegid();
            ruser = getuid();
            rguser = getgid();
            printf("Fils : pid = %d, ppid = %d\n", pid, ppid);
            printf("Fils : cwd = %s\n", cwd);
            printf("Fils : euser = %d, eguser = %d, ruser = %d, rguser = %d\n", euser, eguser, ruser, rguser);
            break;
        default:
            // père:
            pid = getpid();
            ppid = getppid();
            getcwd(cwd, sizeof(cwd));
            euser = geteuid();
            eguser = getegid();
            ruser = getuid();
            rguser = getgid();
            printf("Père : pid = %d, ppid = %d\n", pid, ppid);
            printf("Père : cwd = %s\n", cwd);
            printf("Père : euser = %d, eguser = %d, ruser = %d, rguser = %d\n", euser, eguser, ruser, rguser);
            break;
    }
}
