# TD2 : Sémaphores et accès concurents

## RDV entre *n* processus

On peut utiliser seulement *n* sémpahores pour *n* processus. Néanmoins ce ne sera plus des sémaphores binaires.

La généralisation serait :

Pour *n* processus qui s'attendent mutuellement, on a besoin de *n* sémaphores initliasés à 0. Chaque processus consommera *n-1* ressources sur son propre sémaphore, et rendra 1 ressources sur les *n-1* autres sémaphores.

Le pseudo code pour le procesus *i* serait le suivant :

```C

void processi(){

    // code i

    // V(Sj) pour tout j différent de i, avec j de 1 à n

    // P(Si) (n-1) fois

    rdv(i);

}

```

## EXO 4

Toute lecture puis écriture d'une **variable partagée**, on prends un risque car si il y a une interruption entre la lecture et l'écriture.

> l'instruction `n++` n'est d'ailleurs pas atomique car elle comporte une lecture et une écriture

La section de `if` est donc critique et on doit attacher un sémaphore partagé afin que un seul processus ne puisse tester la valeur du compteur commun.

## TP

### La fonction `ftok()`

Renvoie un objet de type `key_t` qui est une clé-token unique, pour après générer des objets de types sémaphores, files etc. La fonction prends en argument un path de fichier, et un entier qui sera aussi utilisé pour la génération.

### La fonction `semid()`

La fonction `semid()` renvoie un identifiant de groupes de sémaphores, à partir d'une clé ICD. Les sémaphores seront au nombre de sema et à la valeur précisée.

### La fonction `semset()`

Cette fonction permet de contrôler les opérations sur un ensemble de sémaphores. Notamment pour set les values. Dans ce cas, on passe *SETALL* en cmd, et un tableau de valeurs pour chaque sema.

```c
int semctl(int semid, int semnum, int cmd, ...);
```
