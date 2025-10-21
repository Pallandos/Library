# TDTP6 : Gestion de la mémoire

## Exercice 1

On énumère les possibilités en fonction des états et de la localisation du processus

swapin :

-UC : Prêt, Bloqué
-mém: Non-résident

swapout:
-UC : Prêt, Bloqué
-mém : résident

## Exercice 2

On peut utiliser les critères suivants pour gérer les swap in/out.

Swapin : (parmi ceux en stockage)

1. parmi les prêts
   1. priorité croissante
      1. d_swap le plus ancien (pour apporter de l'équité)
      2. taille (pour pouvoir donner + de choix à l'ordonnanceur)
      3. d_swap au dela d'un certain seuil pour éviter une famine

2. parmi les bloqués
   1. taille
   2. d_swap
   3. priorité

Swapout :

1. parmi les bloqués
   1. taille croissante
   2. priorité décroissante

2. parmi les prêts
   1. priorité décroissante
   2. taille croissante

## Exercice 3

On a le code suivant qui permet de décrire les opérations de *swap*.

```c

main () {
    int noProcIn, noProcOut ;
    sema reveil_swap = 0 ;
    int place_en_memoire = 1 ;
    while (1) {
        while (place_en_memoire) {
            noProcIn = rechercherProcessusArentrer () ;
            if (noProcIn < 0) {
                etat_swap = INACTIF ;
                P (reveil_swap) ;
            }
        else {
            if (swapin (noProcIn) != 0 ) {
                place_en_memoire = 0 ;
                }
            }
        }
        while ( !place_en_memoire) {
            noProcOut = rechercherProcessusAretirer () ;
            if (noProcOut < 0) {
                etat_swap = INACTIF ;
                P (reveil_swap) ;
            }
            else {
                swapout (noProcOut) ;
                place_en_memoire = 1 ;
            }
        }
    }
}

```

Ce swappeur est réveillé de manière régulière par

```c
//Interuption_horloge_swap :
if (etat_swap = INACTIF) {
    etat_swap = ACTIF ;
    V (reveil_swap) ;
}
```

On peut donc implémenter les fonctions swapin de la manière suivante.

```c

int swapin(int num){

    int taille = processus[num].taille;
    char* add = processus[num].pt_disque;
    char* add_num = allouerZone(taille);

    if(add_num == NULL){
        return 0;
    }
    else{
        int ref = lireDisque(add, add_num, taille);
        if(ref != 0){
            return 0;
        }
    }
    processus[num].etat_mem = RESIDENT ;
    processus[num].pt_mem = add_mem;
    processus[num].d_swap = time();
    return 1;
}

int swapout(int num){

    char* pt_num = processus[num].pt_num
    int taille = processus[num].taille;
    char* pt_disque = processus[num].pt_disque;
    int ref = ecrireDisque(pt_disque, pt_num, taille);

    if (ref == -1){
        return 0;
    }

    int ref2 = libererZone(taille, pt_num);

    if(ref2 == -1){
        return 0;
    }

    processus[num].d_swap = time();
    processus[num].etat_mem = NON_RESIDENT;
    return 1;

}

```

> On utilise la structure globale `processus` qui est définie dans le sujet