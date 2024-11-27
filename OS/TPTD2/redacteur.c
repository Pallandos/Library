#include <sys/types.h>     /* key_t  */
#include <sys/ipc.h>       /* ftok   */
#include <sys/sem.h>       /* semget, semctl, semop */
#include <sys/stat.h>      /* stat, struct stat  */
#include <stdlib.h>        /* malloc */
#include <stdio.h>         /* perror, printf */
#include <errno.h>         /* errno */
#include <unistd.h> 	   /*sleep*/

#define PRJVAL  1 // valeur pour la creation de la cle

/* retourne -1 en cas d'erreur           */
int P(int semid, int noSem)
{
    struct sembuf Ops[1];
	int ok;
	
	// Q- donner les 3 elements de la structure Ops pour realiser l'operation (voir le cours)
	// Ops[0].sem_num = ...; ...
    Ops[0].sem_num = noSem;
    Ops[0].sem_op = -1;
    Ops[0].sem_flg = 0; // mode bloquant
	
	// Q- faire appel à la fonction semop pour realiser l'operation P, la variable OK recupere la valeur de retour
    ok = semop(semid, Ops, 1);

    if (ok == -1) {
        perror("semop");
    }
    return ok;
}

/* retourne -1 en cas d'erreur           */
int V(int semid, int noSem)
{
	struct sembuf Ops[1];
	int ok;
	
	// Q- donner les 3 elements de la structure Ops pour realiser l'operation (voir le cours)
	// Ops[0].sem_num = ...; ...
    Ops[0].sem_num = noSem;
    Ops[0].sem_op = 1;
    Ops[0].sem_flg = 0; // mode bloquant
	
	// Q- faire appel à la fonction semop pour realiser l'operation V, la variable OK recupere la valeur de retour
    ok = semop(semid, Ops, 1);

    if (ok == -1) {
        perror("semop");
    }
    return ok;
}

int main(){
    key_t k = ftok("gen_key",PRJVAL); // creation de la cle
    int sem = semget(k,0,0); // arguments à 0 car simple ouverture
    printf("semid : %d \n", sem);

    if(sem == -1){
        perror("semget");
        return 1;
    }

    // les deux sémaphores du programme
    int donnees = 0;
    int mutex = 1;

    P(sem, donnees); // P(données)

    // écriture
    FILE* f = fopen("livre", "a"); // ouverture en mode addition/append

    if(f == NULL){ // si on a loupé l'ouverture
        perror("fopen");
        return 1;
    }

    sleep(5); // c'est long d'écrire...
    fprintf(f, "Un rédacteur a écrit du texte\n");

    fclose(f); // fermeture pour sauvegarde

    V(sem, donnees); // V(données)
}