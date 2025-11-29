#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DEFAULT_SEUIL_NS 5000000 // 5 ms en nanosecondes

// Fonction pour obtenir le temps actuel en nanosecondes
long long current_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

int main(int argc, char *argv[]) {
    long long SEUIL = DEFAULT_SEUIL_NS;
    if (argc > 1) {
        SEUIL = atoll(argv[1]);
    }

    printf("Démarrage de la boucle de surveillance (Ctrl+C pour arrêter)...\n");
    printf("Seuil d'alerte : %lld nanosecondes\n", SEUIL);

    long long prev_time = current_time_ns();

    while (1) {
        long long current_time = current_time_ns();
        long long delta = current_time - prev_time;

        if (delta > SEUIL) {
            printf("ALERTE : Delta de %lld ms (%lld ns) détecté.\n", delta / 1000000, delta);
        }

        prev_time = current_time;
        // usleep(10000); // Optionnel : pour simuler une charge
    }

    return 0;
}