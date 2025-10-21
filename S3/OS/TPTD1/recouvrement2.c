#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int code_retour ;
    int statut_fils;
    printf("Début du fork + execl\n");

    code_retour = fork();

    switch (code_retour){
        case -1:
            printf("Erreur lors du fork()");
            exit(1);
            break;

        case 0:
            // fils : execl ou execv

            // execl("/bin/ps", "-l", NULL);

            char *args[] = {"-l", NULL};
            execv("/bin/ps", args);


            printf("Erreur lors du execl()");
            exit(1);
            break;
        
        default:
            // père, attends 
            wait(&statut_fils);
            // statut = 0 si tout s'est bien terminé

            printf("Fin du fork + execl\n");
            printf("Statut du fils : %d\n", statut_fils);
            break;

    }
}