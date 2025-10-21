// génération de sémaphores pour l'exo des rédacteurs

#include <sys/types.h>     /* key_t  */
#include <sys/ipc.h>       /* ftok   */
#include <sys/sem.h>       /* semget, semctl, semop */
#include <sys/stat.h>      /* stat, struct stat  */
#include <stdlib.h>        /* malloc */
#include <stdio.h>         /* perror, printf */
#include <errno.h>         /* errno */

#define PRJVAL  1

int main(int argc,char ** argv)
{
	int nbSem, val;
	int s;
	unsigned short *values;
	struct stat buf;
	 
	if (argc!=4) { fprintf(stderr,"Usage: %s nomFichier nbSem val\n",argv[0]);
		return 1;
	}

	if (stat(argv[1],&buf)==-1) { //le nom de fichier
	    fprintf(stderr,"%s n'est pas une reference!\n",argv[1]);
	    return 1;
	}

	if (sscanf(argv[2],"%d",&nbSem)!=1) { // le nombre de semaphore crées
	    fprintf(stderr,"%s n'est pas un entier!\n",argv[2]);
	    return 1;
	}
	if (sscanf(argv[3],"%d",&val)!=1) { // la valeur initiale des sémaphores
	    fprintf(stderr,"%s n'est pas un entier!\n",argv[3]);
	    return 1;
}
	 
	key_t k = ftok(argv[1], PRJVAL);
	 
	if (k==-1) perror("ftok");

	printf("cle %d (dec) %x (hex) inode %x\n", k,k,(int)buf.st_ino);
	 
    int semid = semget(k, nbSem, IPC_CREAT | 0600);
    
	 
	if (semid==-1){
	fprintf(stderr,"Erreur lors de la creation\n");
	return 1;
	}
	printf("semid obtenu:%d\n",semid);
	 
	values=(unsigned short*)malloc(sizeof(unsigned short)*nbSem); 
	if (values==NULL){
		exit(-1);
	}	

	for (s=0; s<nbSem; s++) values[s]=val;
	
    semctl(semid, 0, SETALL, values);

	free(values);
	return 0;
}