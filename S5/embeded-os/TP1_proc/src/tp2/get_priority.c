#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include "../lib/parse_info.h"

int main() {
    pid_t pid = getpid(); // Get current process ID

    int priority = getpriority(PRIO_PROCESS, pid); // Get the priority of the current process

    printf("With getpriority():\n");
    printf("Process ID: %d\n", pid);
    printf("Process Priority: %d\n \n", priority);

    // With /proc/self
    const char *status_path = "/proc/self/sched";
    const char *categories[] ={
        "policy",   // Scheduling policy : 0 for SCHED_OTHER, 1 for SCHED_FIFO, 2 for SCHED_RR
        "prio"      // Static priority
    };
    printf("With /proc/self:\n");
    parse_info(status_path, categories, sizeof(categories) / sizeof(categories[0]));
}