#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = getpid(); // Get current process ID

    int priority = getpriority(PRIO_PROCESS, pid); // Get the priority of the current process

    printf("Before setpriority():\n");
    printf("Process Priority: %d\n \n", priority);

    // Set a new priority 
    setpriority(PRIO_PROCESS, pid, -16); // Set the priority to 5
    priority = getpriority(PRIO_PROCESS, pid); // Get the updated priority

    printf("After setpriority():\n");
    printf("Process Priority: %d\n", priority);
}