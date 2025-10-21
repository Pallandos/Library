// ------------------------------------------------------------------
// exemple-pthread-create-1.c
// Fichier d'exemple du livre "Developpement Systeme sous Linux"
// (C) 2000-2019 - Christophe BLAESS <christophe@blaess.fr>
// https://www.blaess.fr/christophe/
// ------------------------------------------------------------------

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *arg)
{
    int argument = * (int *) arg;

    int i = 0;
	while (i<5) {
		fprintf(stderr, "New thread with arg = %d\n", argument);
		sleep(1);
        i++;
	}
    exit(0);
}


int main (void)
{
	pthread_t thr;

    for (int i = 0; i<2; i++){
        if (pthread_create(&thr, NULL, thread_function, (void *) &i) != 0) {
		    fprintf(stderr, "Error during pthread_create()\n");
		    exit(EXIT_FAILURE);
	    }
    }


	while (1) {
		fprintf(stderr, "Main thread\n");
		sleep(1);
	}
}