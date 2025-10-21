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

    if(sem == -1){
        perror("semget");
        return 1;
    }

    int donnee = 0;
    int mutex = 1;

    int n_lecteurs;

    P(sem, mutex); // P(mutex) : on accède a compteur partagé qui est donc protégé

    FILE *f_nombre = fopen("nombre", "r+"); // "r+" : lecture et écriture
    fscanf(f_nombre,"%d",&n_lecteurs);

    n_lecteurs++;

    rewind(f_nombre); // retour au début du fichier
    fprintf(f_nombre, "%d", n_lecteurs);
    fclose(f_nombre);

    V(sem,mutex);

    if (n_lecteurs == 1) {
        P(sem, donnee); // P(donnee) : premier lecteur personne ne peut écrire
    }

    // lecture
    FILE *f = fopen("livre", "r");
    char buffer[100];
    fgets(buffer,sizeof(buffer) - 1, f);
    buffer[100] = '\0' ; 

    printf("Lecture : %s\n", buffer);

    P(sem, mutex); // P(mutex)
    FILE *f_nombre2 = fopen("nombre", "r+"); // "r+" : lecture et écriture
    fscanf(f_nombre2, "%d", &n_lecteurs);

    n_lecteurs--;

    rewind(f_nombre2); // retour au début du fichier
    fprintf(f_nombre2,"%d",n_lecteurs);
    fclose(f_nombre2);

    if (n_lecteurs == 0) {
        V(sem, donnee); // V(donnee) : dernier lecteur, on rends la donnée
    }
    V(sem, mutex); // V(mutex)

}