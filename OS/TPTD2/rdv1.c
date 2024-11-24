#include <sys/types.h>     /* key_t  */
#include <sys/ipc.h>       /* ftok   */
#include <sys/sem.h>       /* semget, semctl, semop */
#include <sys/stat.h>      /* stat, struct stat  */
#include <stdlib.h>        /* malloc */
#include <stdio.h>         /* perror, printf */
#include <errno.h>         /* errno */
#include <unistd.h> 	   /*sleep*/

#define PRJVAL  1

// Ce programme doit etre duplique pour chaque processus voulant etablir un RDV
// vous pouvez nommer le programme du premier processus RDV1.C et celui du 2nd RDV2.C par exemple
// Les 2 programmes doivent etre compiles separement et executer separement sur le shell


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


int main (void)
{ // a completer sans oublier de supprimer l'ensemble des semaphores

	// Q- Il faut d'abord recreer la cle (voir sema.c)
    key_t k = ftok("gen_key", PRJVAL);
	
	// Q- il faut ensuite ouvrir le semaphore avec semget, a part la cle, les autres argument doivent etre a zero
	// car il ne s'agit pas d'une creation mais d'une ouverture
	int sem = semget(k, 0, 0);
	
	// Q- faire l'appel a sleep() afin d'avoir des attentes de differentes durees pour les 2 processus
	// sleep(5);
	
	// Q- faire appel a P et a V (voir le TD)
    V(sem, 1);
    P(sem, 0);
	
	
	
	// appeler la fonction de RDV, un printf est suffisant.
    printf("Fonction 1 au point de RDV\n");

}