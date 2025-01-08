# OS

- [OS](#os)
	- [Intro](#intro)
	- [Les processus](#les-processus)
		- [Notion de processus](#notion-de-processus)
		- [Pseudo parallélisme](#pseudo-parallélisme)
		- [Hiérarchie des processus UNIX](#hiérarchie-des-processus-unix)
		- [Contexte d'un processus](#contexte-dun-processus)
		- [Création du processus](#création-du-processus)
	- [Concurrence et Exclusion mutuelle](#concurrence-et-exclusion-mutuelle)
		- [Pourquoi c'est important?](#pourquoi-cest-important)
		- [L'attente active](#lattente-active)
			- [Le TSL](#le-tsl)
	- [Files de messages](#files-de-messages)
		- [Implémentation UNIX des files de message en C](#implémentation-unix-des-files-de-message-en-c)
		- [Faiblesses des files:](#faiblesses-des-files)
	- [Segments de mémoire partagée](#segments-de-mémoire-partagée)
		- [Implémentation en C](#implémentation-en-c)
	- [Les *pipes* (tubes)](#les-pipes-tubes)
		- [Implémentation en C](#implémentation-en-c-1)
	- [Les signaux](#les-signaux)
		- [Implémentation en C](#implémentation-en-c-2)
	- [La norme POSIX](#la-norme-posix)
		- [Les threads](#les-threads)
			- [Ordonancement des threads et processus](#ordonancement-des-threads-et-processus)
		- [Algorithmes d'ordonancement](#algorithmes-dordonancement)
		- [Synchronisation sous POSIX](#synchronisation-sous-posix)
	- [La mémoire](#la-mémoire)
		- [L'allocation de mémoire](#lallocation-de-mémoire)
			- [Le swap](#le-swap)
			- [Pagination](#pagination)
			- [La mémoire virtuelle](#la-mémoire-virtuelle)
			- [Le remplacement de page](#le-remplacement-de-page)
		- [Les systèmes paginés](#les-systèmes-paginés)
		- [La segmentation](#la-segmentation)

## Intro

Objectifs :
Décrire rôle et fonctionnement d'un sys exploitation **mono-processeur**
mais **multi-tâches**.

Émuler : reproduire le fonctionnement d'une machine sur une autre. Traduit d'un sys à un autre.

**Virtualisation** : permet de virtualiser des composants physiques ou un système d'exploitation. Pour pallier un pb de compatibilité, pour simplifier.

**Architecture Von Neumann:**
Le processeur est séparé en deux parties: une unité de calcul/traitement et une de contrôle. On y rajoute un zone de mémoire (données + programme) reliée au processeur par un bus.

Voir : [Architecture de Von Neumann](https://fr.wikipedia.org/wiki/Architecture_de_von_Neumann)

Cela implique une gestion particulière de la mémoire et des périphériques : partage entre les users.

Donc 2 **objectifs pour l'OS** :

- Partage des ressources (tâches, mémoire, fichiers)
- Sécurisation

Différents types de systèmes d'exploitation :

- monolithiques :
  - un seul bloc,
  - facilité de conception
  - code dur à maintenir
- modulaire/multicouche
  - hiérarchie des couches
  - code organisé
- micronoyaux (ex windows / MacOs)
  - réduction du volume exécuté en mode noyau
  - fiabilité et stabilité de l'ensemble
  - mais on perds en efficacité
- machine virtuel
  - un moniteur de VM émule un OS
  
On peut aussi classer les OS par :

- OS temps partagé
- OS temps réel

## Les processus

**Parallélisation** des processus. Gestion fine de l'execution de mon code.

Objectif : comment faire de multi tâches

La commande `ps` donne les processus du sys.

### Notion de processus

C'est un programme qui s'execute. Ce n'est donc PAS un programme, c'est bien son execution. Le programme est la marche à suivre, le processus en est la réalisation. C'est une tâche.

Un processeur fonctionne en général avec un *ordonnanceur* qui priorise les processus et donne quand les interrompre/commencer.

Un processus peut être :

- ELU = actif
- PRET = en attente d'execution
- BLOQUE = en attente de ressource (déjà commencé), doit passer par PRET avant d'être élu

### Pseudo parallélisme

Pas de vrai parallélisme sauf en multi-coeurs.

Pour cela on fais des pauses dans les processus : on les exécute petit à petit avec des pauses (une pause chaque *quantum*)

### Hiérarchie des processus UNIX  

Un processus en lance d'autres ce qui crée une arborescence. Un processus a accès à son PID et à celui de son père.

### Contexte d'un processus

Contexte ou image contient toutes les informations de son execution comme le *PID* ou *l'état de registre* etc. Cela permet de définir complètement le processus pour que l'OS puisse le relancer si il est interrompu là où il s'est arreté. Le contexte est coûteux à écrire donc est crée principalement quand on change de processus.

Il se décompose en :

- structure mémoire du processus
  - pile
  - données
  - code
- bloc de contrôle (global)
  - état
  - pointeur de pile
  - compteur
  - allocation mémoire

A voir :

- [Pile / stack](https://fr.wikipedia.org/wiki/Pile_d%27ex%C3%A9cution)
- [Tas / heap](https://fr.wikipedia.org/wiki/Tas_(allocation_dynamique))

### Création du processus

On duplique un processus avec la fonction `fork()`.

On peut recouvrir un processus avec la commande `exec`.

## Concurrence et Exclusion mutuelle

Inhérent à toute programmation en multitâche.

### Pourquoi c'est important?

Objectifs :

- limiter l'accès aux ressources
- limiter à un seul user/processus

Une *section critique* est une zone/donnée qui présente des risques d'accès multiples et qui devra être protégée. Cela demande donc un système d'exclusion mutuelle.

4 conditions à satisfaire :

- 2 processus ne peuvent être en même temps dans la même zone critique
- aucune hypothèse sur les vitesses relatives et le nombre de coeurs
- aucun processus suspendu en dehors d'une section critique ne doit bloquer les autres
- aucun processus ne dois attendre trop longtemps

### L'attente active

Première solution pour pallier au problème (mais moins efficace que l'attente passive)

Plusieurs solutions sont imaginables mais non fiables:

- masquage des interruptions : trop dangereux de supprimer les interruptions
- par verrouillages/clés : vulnérable entre la lecture du verrou et sa modification
- alternance mode1 (clé d'accès avec un destinataire forcé) : implique la connaissance du nombre de processus, inégalitaire en terme de temps d'execution (un processus lent sera favorisé)

#### Le TSL

TSL ou *Test and Set Lock* est une instruction atomique qui implémente l'exclusion mutuelle ([Wikipedia](https://fr.wikipedia.org/wiki/Test-and-set)).

On sépare la lecture et l'écriture du verrou, ce qui permet d'empêcher les accès concurrents.

Code en C qui implémente l'opération atomique :

```.c

#define LOCKED 1

int test_and_set(int* lockPtr) {
	int oldValue;

	// -- Start of atomic segment --
	// This should be interpreted as pseudocode for illustrative purposes only.
	// Traditional compilation of this code will not guarantee atomicity, the
	// use of shared memory (i.e., non-cached values), protection from compiler
	// optimizations, or other required properties.
	oldValue = *lockPtr;
	*lockPtr = LOCKED;
	// -- End of atomic segment --

	return oldValue;
}

```

Implémentation C du spin-lock associé au mode atomique ci dessus :

```c

volatile int lock = 0;

void critical() {
	// Spin lock: loop forever until we get the lock; we know the lock was
	// successfully obtained after exiting this while loop because the 
	// test_and_set() function locks the lock and returns the previous lock 
	// value. If the previous lock value was 1 then the lock was **already**
	// locked by another thread or process. Once the previous lock value
	// was 0, however, then it indicates the lock was **not** locked before we
	// locked it, but now it **is** locked because we locked it, indicating
	// we own the lock.
	while (test_and_set(&lock) == 1);  
	critical section  // only one process can be in this section at a time
	lock = 0;  // release lock when finished with the critical section
}

```

## Files de messages

Communication via deux opérations :

- send
- receive

On échange des enveloppes, on ne peut pas envoyer de message sans enveloppe. Cela sécurise la chose : on attends d'avoir un contenant pour envoyer du contenu, mais on peut échanger les contenants vides. 

### Implémentation UNIX des files de message en C

Les files de messages sont implémentées en C à partir de [<sys/msg.h>](https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysmsg.h.html).

Voir les 4 primitives : *msgsnd* (envoie), *msgget* (creation), *msgctl* (opérations), *msgrcv* (lecture).

### Faiblesses des files:

Chaque lettre est stockée en 2 fois dans le système donc ce n'est pas adapté pour de grands volumes de données.

## Segments de mémoire partagée

On peut donc répondre au problème de taille avec des segmnets de mémoire partagée. Les process peuvent donc partager des segments de mémoire communs. 

Sous UNIX : 

- plusieurs segmnents possibles 
- un process peut en avoir plusieurs 
- existance des segments indé de celle des processys 
- un process doit attacher son segment à son espace d'adressage pur y accéder

Donc dans l'ordre les étapes sont les suivantes :

1. création du segment par le premier processus
2. chaque process qui veut y accéder attache le segment à son espace d'adressage 

> Les segments de mémoire partagés doivent être protégés par des sémaphores car ce sont *juste* des variables partagées

### Implémentation en C

Les mémoires partagées sont incluses dans [<sys/shm.h>](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/sys/shm.h.html)

De même, voir les 4 primitives de *shared memory*. 

> Les pointeurs pour un accès en lecture et en écritures sont distincts. On a donc 2 attachements distincts.

## Les *pipes* (tubes)

Les tubes font le lien entre le VFS et le système de fichier virtuel (fichier au sens *stream* ?). Un tube possède 2 entrées et peut être utilisé dans les 2 sens (au sens envoie / reception) mais pas simultanément : contrairement aux lettres, il n'est partagé que par 2 process. 

Chaque process vient avec un tableau de fichiers, qui correspond à tous les streams/files auxquels a accès ledit process. Les 3 premières cases sont réservées (stdout, stdin, stderr). Chaque `open` dans ledit process ajoutera au tableau des fichiers un pointeur vers le fichier ouvert (en fait c'est un pointeur vers une structure intermédiaire qui notera les droits d'accès etc). 

La lecture est destructrice, gestion en FIFO, lecture possible en continu, limite de taille réduite par rapport aux segments partagés.

Deux types de tubes: 

- **tube ordinaire : vit uniquement pour un procesus et sa famille** (on préfera ceux la)
- tube nommé : ouvert avec un `pipe` peut vivre au dela de son process
 
Comme leur nom l'indique, le *pipe* est le ` | ` que l'on peut utiliser en UNIX entre des commandes : il crée un pipe entre 2 commandes avec les close intégrés. 

### Implémentation en C

En C, les pipes sont implémentés dans `unistd.h`. Ils peuvent être crées à partir de [`pipe()`](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pipe.html).

## Les signaux

Les signaux sont l'équivalent des interruptions matérielles en version logicielle. Ils ne doivent être utilisés que dans des cas rares, pas en comm.

Ils peuvent être générés par :

- interruption logicielle (par une erreur par exemple)
- évènement système (un signal qui meurt)
- le user (en cas de sigaux customs)

Le signal peut être ignoré. Il tue en général le process receveur (d'où le `kill` qui envoie les signaux). Pas de contenu informatif (y compris l'émetteur).

### Implémentation en C

La fonction POSIX [`kill(int pid, int signal)`](https://pubs.opengroup.org/onlinepubs/009695399/functions/kill.html) permet d'envoyer un signal.

De même, la fonction [`signal`](http://manpagesfr.free.fr/man/man2/signal.2.html) permet de modifier le comportement à la réception d'un signal. 

## La norme POSIX

[POSIX](https://fr.wikipedia.org/wiki/POSIX) est une **norme** de dev de logiciels. Cela permet son intégration parfaite dans les systèmes UNIX. Très vieille norme : crée entre 1988 et 1990.

### Les threads

obj : donner plusieurs activités à un même process. On veut gagner du temps et de l'efficacité. *Commutation* plus efficace. 

`pthread_create()` permet de créer un thread pour l'execution d'une fonction. Cette appel se veut très généraliste pour être évolutif : on peut passer les arguments de la fonction en argument de `pthread_create()`.

Selon POSIX : tous les threads d'une même famille on le même nom (PID).

```c
int pthread_create(pthread_t * thread,
	pthread_attr_t * attr,
	void * (*start_routine) (void *),
	void * arg);
```

`pthread_exit()` permet de terminer un thread en cours. `pthread_join()` est l'équivalent du `wait()`.

#### Ordonancement des threads et processus

POSIX propose 3 politiques : une pour les processus classiques temps partagé et deux pour les applications à vocation temps réel. 

Une valeur de priorité statique *sched_priority* est assignée à chaque processus. 

Les 3 politiques sont : 

- *SCHED_FIFO*
- *SCHED_RR* (round robin)
- *SCHED_OTHER*

### Algorithmes d'ordonancement

- **FIFS** (First In First Served) : jusqu'à terminaison. Famine impossible, non préemptive, long turnaround
- **SPN** (Shortest Process Next) : court turnaround, *attention* on doit connaitre le temps d'exec
- **Round Robin** : préemptif, on alloue au tourniquet un *quantum* pour chaque process
- 

### Synchronisation sous POSIX

POSIX re définie et facilite le tâches de synchro. Les nouveaux sémaphores n'incluent pas de clé, créent un seul séma à chaque appel, les flags sont aussi simplifiés pour ressembler à ceux des fichiers. L'appel initie aussi les valeurs. 

Il y a aussi des *Mutex*, distinct des séma. Ce sont des séma binaires, mais sans valeur d'initialisation (elle sera de 1), qui servent de verrou. 

> Penser à l'exo des rédacteurs

## La mémoire

La mémoire progresse moins vite que les processeurs/unités de calcul. C'est le problème de la *mémoire mûre*. 

Lors de la compilation d'un programme, les compilateurs ne relient pas les adresses mémoires. C'est le rôle du *linker* ou du *chargeur*.

Pour alouer les espaces de mémoire on doit connaître l'état de celle ci. On a deux moyens: 

- table de bit (simple à mettre en place mais peut utilisé car prends bcp de place et peut efficient)
- liste chainée (très utilisé) on y inclue :	
  - adresse de début
  - état de la case
  - taille de la case
  - pointeur vers la case suivante

Ensuite au procède plutot au **premier ajustement** et pas au **meilleur ajustement** (plus couteux et produit de la fragmentation). Dans tous les cas, on cherche à éviter : la **fragmentation** (interne/externe) (lorsque les zones de mémoire d'un même fichier sont trop éloignées ce qui fait perdre de l'efficacité) par un compactage et les **fuite de mémoire** par un ramasse miettes.

### L'allocation de mémoire

Lors de la compilation par exemple, on a besoin de place sur mémoire pour attribuer les espaces de chaque programme. On doit mettre en place des techniques pour pour y réussir. 

#### Le swap 

Si on n'a plus de place pour allouer un bloc de programme on peut faire du swap : on déplace temporairement des process sur le disque lorsque l'on a plus de place en mémoire. On peut *swapin* (vers la mémoire) ou *swapout* (vers le disque).

Mais dans sa version brute, on ne peut toujours pas executer de programmes qui ne tiennent pas dans la mémoire principale. Sauf si on introduit un système de **pagination** et de **mémoire virtuelle**.

#### Pagination

Dans la pagination, on découpe la mémoire en blocs phyisiques de taille donnée. Cela améliore la performance du système. C'est comme travailler avec des entiers : c'est plus simple. De plus on peut travailler sans compactage *(mais quid de l'efficacité)*.

> La taille des blocs est aujourd'hui de 4 ko (déterminée de manière empirique).

#### La mémoire virtuelle

Pour lancer des programmes qui sont plus grands que la mémoire princpale, on *virtualise*. Contrairement à la pagination, on ne charge en mémoire principale qu'une portion des pages : que les utiles (on appele cela la *mémoire réelle*).

La **MMU** (memory managment unit) permet de traduire la mémoire réelle en virtuelle et inversement. 

#### Le remplacement de page

Lors de la traduction de page réelle à virtuelle, il peut arriver un défaut (plus de page réelle dispo, page trop petite etc).Il faut alors trouver une nouvelle page en en déférençant une. On doit donc trouver un algo de libération. L'idéal serait de retirer la page qui sera utilisée d le plus tard maiso on ne peut la connaître. 

On peut avoir les politiques suivantes : 

- FIFO : très court en temps cpu mais peu efficace au global 
- LRU (Last Recent Used) : plus intéressant et plus efficace mais moins simple à mettre en place. 


### Les systèmes paginés

Dans ces systèmes on effectue un *chargement à la demande*, dès qu'un défaut de page se produit. C'est le cas fréquemment au début puis au bout d'un moment un process peut tout effectuer sans dé.faut. 

Puis, si on utilise le *LRU* on peut mémoriser l'ensemble de travail de chaque processus, et donc le charger à l'avance. C'est un système par **modèle de l'ensemble de travail**.

l'allocation peut être :

- locale : on remplace parmi les pages du processus ayant fait défaut
- globale : on remplace parmi tout le monde (*plus performant*)
- équitable : chaque procesus peut charger le même nombre de page
- proportionelle : en fonction du besoin de chaque processus

**L'effondrement** ou **trashing** survient lorsque trop de pages font défaut. On ne peut l'éviter mais juste le surveiller. 

**Le retour sur instruction** survient lorsqu'un défaut de page arrive au milieu d'une instruction. Il faut alors la rejouer.


### La segmentation

On découpe les pages en sous page en fonction de leur utilisation, et elles sont contigues. 

On retrouve dans un segment:

- table des symboles
- code
- tables des constantes
- arbre d'analyse syntaxique
- pile d'appel