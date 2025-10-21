#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

void main(){

    int cpu = sched_getcpu();
    printf("Coeur CPU numéro %d\n",cpu);

    while(1){
        int cpu_temp = sched_getcpu();

        if(cpu_temp != cpu){
            cpu = cpu_temp;
            printf("Coeur CPU numéro %d \n",cpu);
        }

    }

}
