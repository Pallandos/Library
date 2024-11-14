#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

main () {
    int code_retour ;
    int PID_filszombie;
    int status;
    printf ("Debut du test fork ()\n");
    code_retour = fork ();
    switch (code_retour ) {
        case -1 :
            printf ("Pbm lors de la creation du processus\n");
            break;
        case 0 :
            sleep(5);
            printf ("Je suis le fils : %d \n", getpid());
            sleep(10); // attente pour le tuer en terminal
            break;
        default :
            PID_filszombie = waitpid(0, &status, 0);

            printf ("Je suis le père : %d\n", getpid());
            printf ("PID fils zombie : %d\n", PID_filszombie);
            printf ("status fils : %d\n", status);

            if (WIFSIGNALED(status)) {
                printf("Le fils a été tué par le signal %d\n", WTERMSIG(status));
            } else if (WIFEXITED(status)) {
                printf("Le fils s'est terminé normalement avec le code %d\n", WEXITSTATUS(status));
            } else {
                printf("Le fils s'est terminé anormalement\n");
            }

            break;
    }
    printf ("Fin du test fork ()\n");
}