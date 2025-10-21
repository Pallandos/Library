# TP/TD1 OS

## Exo1

Le `fork()` dupplique le processus d'execution du binaire, donnant un PID au père. La fonction retourne le PID du processus fils dans le bloc père. Et retourne 0 dnas le bloc du fils.

L'ordre d'execution des processus est pseudo aléatoire et dépend du plannificateur de tâches.

> ANOMALIE? : l'ordre des printf est étrange, parfois une ligne du fils s'execute avant la fin du père.

## Exo2

La fonction `getpid()` permet d'obtenir le PID du processus courant. Les autres fonctions sont données dans le mannuel.

> Ne pas oublier que les programmes s'éxecutent de manière distinctes et donc aveugles

exemple de retour :

```txt

Debut du test info fork ()
Père : pid = 7508, ppid = 1066
Père : cwd = /home/melkior/home/osystem/tp1
Père : euser = 1000, eguser = 1000, ruser = 1000, rguser = 1000
Fils : pid = 7509, ppid = 7508
Fils : cwd = /home/melkior/home/osystem/tp1
Fils : euser = 1000, eguser = 1000, ruser = 1000, rguser = 1000

```

On remarque que :

- le père du fils est toujours le père
- le père du père est toujours le même (sûrement VS code ou gcc)
- le PID du fils est PID_père + 1
- ici tous les users sont les mêmes

## Exo3

On place une attente dans le fils.

> Placer une attente dans le processus fils fait changer de pPID le fils : c'est un processus différent qui le lance. En effet puisque le père s'est terminé, le fils devient orphelin, UNIX lui attribue donc un nouveau père de manière arbitraire. Le processus qui va les adopter est le processus 1, ou le processus de système D dans certaines distributions (constant tant que l'on a pas redémarré l'ordinateur).

## Exo4

```txt

Debut du test fork ()
Ouverture du fichier toto
buffer père: 4567
code_retour 3526
Fin du test fork ()
buffer fils: 89dc
code_retour 0
Fin du test fork ()

```

Le code ci dessus est le retour du programme de l'exo4.

Les étapes expliquées sont les suivantes :

1. Création d'un pointeur avant le `fork()`
2. Le pointeur est **partagé** entre le père et le fils au moment du fork
3. Le fils écrit `"fils"` dans la ligne -> le pointeur se déplace de 4
4. Le fils s'endore 2 secondes
5. Le père se réveille, lit les 4 caractères suivants -> le pointeur se déplace de 4
6. Le fils se réveille et lit les 4 caractères suivants -> le pointeur se déplace encore de 4

> On remarque donc que puisque le pointeur est partagé, son déplacement est partagé entre le père et le fils.

## Exo5

Le code retour du fils est `0` ce qui signifie qu'il a été terminé correctement.

## Exo6

Avec l'option 0, `waitpid()` attends que le fils se termine avant de retourner.

Lorsqu'on le tue avec un terminal séparé on a les résultats suivants :

- la commande `kill -15 pid_fils` fait tuer lefils par le signal 15 : SIGTERM (terminaison propre et en douceur)
- la commande `kill -9 pid_fils` fait tuer le fils par le signal 9 : SIGKILL (assassinat brut et méchant)

Plus d'[information sur les signaux](https://www.linuxtricks.fr/wiki/signaux-unix-unix-signals).
