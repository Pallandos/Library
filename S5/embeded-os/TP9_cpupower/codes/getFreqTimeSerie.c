// ---------------------------------------------------------------------
// VO par Christophe BLAESS
// Adapté par Jalil Boukhobza
// Modifié par Camélia Slimani
// ---------------------------------------------------------------------

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <sys/time.h>

#define NANO 1000000000

static timer_t timer = (timer_t) 0;


// curFreq : Fichier de fréquence courante 
// output : Fichier de trace en sortie 
FILE *curFreq, *output;  
struct timespec t0;
		
void handler_signal(int inutilise)
{
	static struct timespec instant = { 0, 0} ;
        char freq[20], towrite[100];  
        long int timestamp; 
	// *** a compléter -->  Lecture de l'instant présent avec la fonction clock_gettime

	
	
	// *** a compléter --> Lecture de la fréquence courante freq depuis le fichier /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq 
 
	fclose(curFreq); 
	// *** a compléter --> mesurer le temps
	
	
	// *** a compléter -->  Calcul du timestamp instant - t0
	
	
	// Ecriture dand le fichier output 	
	sprintf(towrite, "%ld\t%s\n", timestamp, freq); 
	if (fputs(towrite, output) < 0) {
	    printf(  "Erreur à l'écriture \n");
            exit(0); 
	}
	

}


int main(int argc, char * argv[])
{
	int periode;
	struct sigevent event;
	struct itimerspec spec;
	
	if ((argc != 3) || (sscanf(argv[1], "%d", & periode) != 1)){
		fprintf(stderr, "usage: %s periode output\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// *** a compléter --> Ouverture du fichier output 



	// *** a compléter --> Lecture de l'instant t0 à partir duquel sera calculé le timestamp
	
	
	 
	// Configurer le timer
	// à la reception du signal SIGRTMIN, executer la fonction handler_signal()
	signal(SIGRTMIN, handler_signal);
	
	// Nous souhaitons être notifié par signal
	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo  = SIGRTMIN; 
	
	periode = periode * 1000;  // en nanosec
	
	// Définir la partie entière et fractionnaire
	spec.it_interval.tv_sec  = periode / NANO; 
	spec.it_interval.tv_nsec = periode % NANO; 
	spec.it_value = spec.it_interval;
	
	
	//  allouer le timer
	if (timer_create(CLOCK_REALTIME, &event, &timer) != 0 ) {
		perror("timer_create");
		exit(EXIT_FAILURE);
	}
	
	// programmer le timer
	if (timer_settime( timer,  0, &spec, NULL  ) != 0) {
		perror("timer_settime");
		exit(EXIT_FAILURE);
	}
	
	
	// Attendre le dernier signal
	while (1)
		pause();
		
	
	//*** a compléter --> fermeture du fichier output 
	
		
	return EXIT_SUCCESS;
}

