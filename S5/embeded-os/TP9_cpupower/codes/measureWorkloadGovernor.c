//Inspré de C. Blaess

#define _GNU_SOURCE 
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>


int main (int argc, char **argv){

	int fd; // Descripteur du fichier gouverneur
	char filename[256]; // Chemin du fichier gouverneur 
	long long int duree; 
	struct timeval start, end; 
	pid_t pid; // pid du processus qui va lancer le workload 
	 
	 
	 
	 // Verification des paramètres d'entree
	 if (argc != 4) {
	 	fprintf( stderr, "Usage : %s <governor> <workload>\n", argv[0]); 
	 	exit(1); 
	 } 


         // Changement de gouverneur 

	 // ***** a compléter => Formation du chemin vers le fichier gouverneur 
	 
	 // sprintf(filename, ...)
	 
	 fd = open (filename, O_RDWR); 
	 if (fd < 0) {
	 	perror(filename); 
	 	exit(2); 
	 }
	 
	 // ****** a compléter => Ecriture du nom du gouverneur récupéré en paramètre dans le fichier du gouverneur courant 
	 if (write(fd, argv[1], strlen(argv[1]))<0){
	 	perror(filename); 
	 	exit(2);
	 }
	 
	 close (fd);
	 
	 sleep(1); 
	 
	 
	 gettimeofday(&start, NULL);  
	 if (fork()==0){
	 // ***** a compléter  => fils -> lancement du workload 
	 //	execlp (...); 
	 	perror(argv[2]); 
	 	exit(EXIT_FAILURE); 
	 } 
	 else {
	   // ***** a compléter  => parent -> attente du fils
			
	 }
	 
	 
	 gettimeofday(&end, NULL); 
	 
	 duree = end.tv_sec - start.tv_sec; 
	 duree *= 1000000; 
	 duree += end.tv_usec - start.tv_usec; 
	 
	 printf ("%6lld\n", duree); 
	 
	 return EXIT_SUCCESS; 
	 
	 }
	 
