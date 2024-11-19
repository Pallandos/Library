#include <stdio.h>
#include <fcntl.h>

main () {
    int code_retour ;
    printf ("Debut du test fork ()\n");

    // ouverture du fichier toto:
    int fd = open("toto", O_RDWR);
    if (fd == -1) {
        printf("Erreur lors de l'ouverture du fichier toto\n");
    } else {
        printf("Ouverture du fichier toto\n");
    }
    code_retour = fork ();
    switch (code_retour ) {
        case -1 :
            printf ("Pbm lors de la creation du processus\n");
            break;
        case 0 :

            write(fd, "fils", 4);
            sleep(2);
            char bufferf[4];
            read(fd, bufferf, 4);
            printf("buffer fils: %s\n", bufferf);

            break;
        default :
            sleep(1);

            char bufferp[4];
            read(fd, bufferp, 4);
            printf("buffer père: %s\n", bufferp);
            write(fd, "père", 4);

            break;
    }

    close(fd);
    printf ("code_retour %d\n", code_retour);
    printf ("Fin du test fork ()\n");
}