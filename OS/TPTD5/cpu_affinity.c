#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){

    if(argc < 2 || argc > 9){
        printf("Usage : ./cpu_affinity n_cpu1 [n_cpu2] ...\n");
        exit(EXIT_FAILURE);
    }

    cpu_set_t cpu;
    CPU_ZERO(&cpu);

    int cpu_to_add[8];
    
    int i = 0;
    cpu_to_add[i] = atoi(strtok(*argv, " "));
    CPU_SET(cpu_to_add[i], &cpu);
    while(cpu_to_add[i] != NULL){
        i++;
        cpu_to_add[i] = atoi(strtok(NULL, " "));
        CPU_SET(cpu_to_add[i], &cpu);
    }


    // set affinity :

    if(sched_setaffinity(getpid(), sizeof(cpu), &cpu) != 0){
        printf("Erreur sched affinity \n");
        exit(EXIT_FAILURE);
    }

    int cpu_actual = sched_getcpu();
    printf("Actual cpu core no %d \n", cpu_actual);
    int cpu_temp;

    while(1){
        cpu_temp = sched_getcpu();


        if(cpu_temp != cpu_actual){
            cpu_actual = cpu_temp;
            printf("Actual cpu core no %d \n", cpu_actual);
        }
    }

}