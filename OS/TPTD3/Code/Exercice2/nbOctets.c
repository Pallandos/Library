#include <stdio.h>             /* nbOctets.c */
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "partage.h"

/* Decrire le handler de signal pour SIGUSR1 */
/* ========================================= */

void handler(int signum){
	// ceci est un handler qui fait je ne sais pas quoi
	printf("Handler appelé avec signum : %d \n",signum);
	// ??

}

/* Le main */
/* ======= */

int main(int argc,char **argv)
{
    pid_t pidWC;
	pid_t pidREAD;
 	int status;   /* Pour les waitpid                        */

 	int tube[2];
 	FILE *fIn;      /* Pour faire un fdopen : int -> FILE *    */

	struct sigaction action;

 	Zone z;
 	int *ptDeb;      /* Un pointeur (int*) sur la zone debut    */

 	char *fileName=NULL;

 	if (argc!=2) { fprintf(stderr,"Usage: %s fileName\n",argv[0]); return 1; }

 	fileName=argv[1];

	/* A cause de warnings lorsque le code n'est pas encore la. La ligne suivante permet de ignorer les erreurs */

 	(void)action; (void)fIn; (void)tube; (void)status; (void)pidREAD; (void)pidWC;

    /* Gestion des signaux */
    /* =================== */

    /* Preparation de la structure action pour recevoir le signal SIGUSR1 */

    /* action.sa_handler = ... */
    action.sa_handler = handler ; // on attache le handler

    /* Appel a l'appel systeme sigaction */
    if (sigaction(SIGUSR1, &action, NULL) == -1){
        
            perror("Erreur sigaction");
            exit(EXIT_FAILURE);

    }

    /* ... */

    /* Creation de la zone de memoire partagee */
    /* ======================================= */

    /* ... */

    if( creerZonePartagee( sizeof(int), &z )  == -1){

        perror("Erreur création zone mémoire");
        exit(EXIT_FAILURE);

    }

    ptDeb=(int*)z.debut;    /* *ptDeb <=> *((int*)z.debut) */

    /* Creation du tube */
    /* ================ */

    if (pipe(tube) == -1){
        perror("Erreur création tube");
        exit(EXIT_FAILURE);
    }

    /* Creation du processus qui fera le exec ...   */
    /* ============================================ */

    /* pidWC=... */
    pidWC = fork();
    
    if(pidWC == -1){

        perror("Erreur fork [fils exec]");
        exit(EXIT_FAILURE);

    }
    if(pidWC == 0){

        dup2(tube[1],STDOUT_FILENO); // redirection vers la sortie standard

        close(tube[0]); // on ferme la lecture : celui ci ne va que écrire

        execlp("wc","wc","-c", fileName ,NULL);

        close(tube[1]);

    }

    /* Dans le processus cree :
        - Rediriger la sortie standard vers le tube
        - Fermer le(s) descripteur(s) inutile(s) a cet enfant
        - Recouvrir par la commande ``wc'' 
    */

    /* Creation du processus qui fera la lecture ...*/
    /* ============================================ */

    /* pidREAD=... */

    pidREAD = -2; 

    if(pidWC != 0){ // on fork uniquement dans le père 
        pidREAD = fork();
    }

    if(pidREAD == -1){ 
        perror("Erreur de fork [fils read]");
        exit(EXIT_FAILURE);
    }
    if (pidREAD == 0){ // dans le fils

        // printf(" PidWC = %d (in fils2) \n", pidWC);
        // printf(" PidREAD = %d (in fils2) \n", pidREAD);

        close(tube[1]); // on ferme l'écriture 

        fIn = fdopen(tube[0] , "r"); // on ouvre le tube en mode lecture de données

        fscanf(fIn, "%d", ptDeb );

        fclose(fIn);
        close(tube[0]); // on a fini

        sleep(1);

        // on envoie le signal : 

        kill(getppid(), SIGUSR1);

    }


    /* Dans le processus cree :
        - Fermer le(s) descripteur(s) inutile(s) a cet enfant
        - Ouvrir un flux fIn sur la sortie du tube: fIn=fdopen(tube[0],"r");
        - Lire le resultat via le flux fIn et le mettre dans la memoire partagee
        - Fermer le flux fIn et le(s) descripteur(s) encore ouvert(s)
        - Attendre un peu pour que le pere puisse faire pause avant
        - Envoyer le signal SIGUSR1 au pere
    */

    /* La suite du pere */
    /* ================ */

    if( pidWC != 0){ 

        // printf(" PidWC = %d (in père) \n", pidWC);
        // printf(" PidREAD = %d (in père) \n", pidREAD);

        close(tube[0]);
        close(tube[1]); // on ferme tout 

        pause(); // attente d'un signal 

        int taille_octet = *ptDeb;

        wait(NULL);

        if( supprimerZonePartagee(&z) == -1){

            perror("Erreur suppresion zone partagée");

        }

        printf("Taille du fichier : %d octets \n", taille_octet );


    }

    /* Fermer les descripteurs de tube inutiles au pere */

    /* ... */

    /* Attente d'un signal */

    /* ... */

    /* Recuperer le resultat dans la memoire partagee */

    /* ... */

    /* Attendre le 1er enfant  */

    /* ... */

    /* Attendre le 2eme enfant */

    /* ... */

    /* Supprimer la memoire partagee */

    /* ... */

    return 0;
}
