#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid1, pid2;

    // Premier fork pour créer le premier fils
    pid1 = fork();

    if (pid1 < 0) {
        // Échec du fork
        perror("Erreur lors du fork");
        exit(-1);

    } else if (pid1 == 0) {
        // Code exécuté par le premier fils
        printf("premier fils : PID %d\n", getpid());

        sleep(5);
        printf("Hello je suis le fils 1\n");
        sleep(1);

        exit(1);

    } else {
        // Code exécuté par le père
        // Deuxième fork pour créer le deuxième fils
        pid2 = fork();

        if (pid2 < 0) {
            // Échec du fork
            perror("Erreur lors du fork");
            exit(-1);

        } else if (pid2 == 0) {
            // Code exécuté par le deuxième fils
            printf("Second fils : PID %d\n", getpid());

            sleep(10);
            printf("Hello je suis le fils 2\n");
            sleep(1);

            exit(2);

        } else {
            // Code exécuté par le père
            printf("Père : PID %d\n", getpid());
            // Attendre que le fils 2 se termine

            int status_retour;
            waitpid(pid2, &status_retour, 0);
            printf("Le fils 2 s'est terminé avec le code %d\n", WEXITSTATUS(status_retour));
        }
    }

    return 0;
}