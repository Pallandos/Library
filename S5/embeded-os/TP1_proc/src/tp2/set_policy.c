#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include "../lib/parse_info.h"

int main() {
    pid_t pid = getpid(); // Get current process ID (we could also use 0 for self)

    const char *status_path = "/proc/self/sched";
    const char *categories[] ={
        "policy",   // Scheduling policy : 0 for SCHED_OTHER, 1 for SCHED_FIFO
        "prio"      // Static priority
    };

    // Before changing the policy
    printf("Before changing the policy:\n");
    parse_info(status_path, categories, sizeof(categories) / sizeof(categories[0]));

    // make the process realtime
    struct sched_param param;
    param.sched_priority = 0; // Priority range for SCHED_FIFO is 1 to 99 (according to man)

    sched_setscheduler(pid, SCHED_FIFO, &param);

    // After changing the policy
    printf("\nAfter changing the policy:\n");
    parse_info(status_path, categories, sizeof(categories) / sizeof(categories[0]));
}