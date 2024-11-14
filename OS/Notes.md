# OS

- [OS](#os)
  - [Intro](#intro)
  - [Les processus](#les-processus)
    - [Notion de processus](#notion-de-processus)
    - [Pseudo parallélisme](#pseudo-parallélisme)
    - [Hiérarchie des processus UNIX](#hiérarchie-des-processus-unix)
    - [Contexte d'un processus](#contexte-dun-processus)
    - [Création du processus](#création-du-processus)

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

Contexte ou image contint toutes les informations de son execution comme le *PID* ou *l'état de registre* etc. Cela permet de définir complètement le processus pour que l'OS puisse le relancer si il est interrompu là où il s'est arreté. Le contexte est coûteux à écrire donc est crée principalement quand on change de processus.

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

On peut recouvrir un processus avec la commande `exec` *(ça sert à quoi??)*.
