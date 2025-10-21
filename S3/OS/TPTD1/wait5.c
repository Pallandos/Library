#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main () {
    int code_retour ;
    int PID_fils;
    int status;
    printf ("Debut du test fork ()\n");
    code_retour = fork ();
    switch (code_retour ) {
        case -1 :
            printf ("Pbm lors de la creation du processus\n");
            break;
        case 0 :
            printf ("Je suis le processus fils \n");
            break;
        default :
            PID_fils = wait(&status);
            printf ("Je suis le père : %d\n", getpid());
            printf ("Le pid du fils est %d\n", PID_fils);
            printf ("Le status du fils est %d\n", status);
            break;
    }
    printf ("Fin du test fork ()\n");
}