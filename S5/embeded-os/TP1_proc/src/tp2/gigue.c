#define _POSIX_C_SOURCE 199309L
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define errExit(msg) do { \
    perror(msg); \
    exit(EXIT_FAILURE); \
} while (0)

#define SIG SIGRTMIN

// handler will recieve all three args when called by `sa_handler`
static void handler(int sig, siginfo_t *si, void *uc){

    printf("Signal no %d \n", sig);

    // get time and print it
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    FILE *f = fopen("times.txt", "a");
    if (f){
        fprintf(f, "%ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
        fclose(f);
    }
}


// tick each x ns, and printf
int ns_clock(long long freq_ns) {

    timer_t tidp;
    struct sigaction sa;
    struct sigevent sev;
    struct itimerspec iti;

    //define the sigaction
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = &handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIG, &sa, NULL) == -1){
        errExit("Fail to create sigaction");
    }

    // define the sigevent
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIG;
    sev.sigev_value.sival_ptr = &tidp;

    // create timer:
    if (timer_create(CLOCK_REALTIME, &sev, &tidp) == -1){
        errExit("Fail to create timer");
    }

    // set timer specs : 
    // wait 2 * interval for first tick and then tick each interval
    iti.it_interval.tv_sec = freq_ns / 1000000000;
    iti.it_interval.tv_nsec = freq_ns % 1000000000;
    iti.it_value.tv_nsec = 2 * iti.it_interval.tv_nsec;
    iti.it_value.tv_sec = 2 * iti.it_interval.tv_sec;
    if (timer_settime(tidp, 0, &iti, NULL) == -1){
        errExit("Fail to init timer specs");
    }

    while(1){
        pause();
    }

    return 0;
}

int main() {
    ns_clock(1000000000);    
}