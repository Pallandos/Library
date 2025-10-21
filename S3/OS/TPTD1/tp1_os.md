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

On place un sleep dans le fils.

> Placer un sleep dans le processus fils fait changer de pPID le fils : c'est un processus différent qui le lance. En effet puisque le père s'est terminé, le fils devient orphelin, UNIX lui attribue donc un nouveau père de manière arbitraire. Le processus qui va les adopter est le processus 1, ou le processus de système D dans certaines distributions (constant tant que l'on a pas redémarré l'ordinateur).

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
6. Le père écrit `père` -> le pointeur se déplace de 4 de nouveau
7. Le fils se réveille et lit les 4 caractères suivants -> le pointeur se déplace encore de 4

> On remarque donc que puisque le pointeur est partagé, son déplacement est partagé entre le père et le fils.

## Exo5

Le code retour du fils est `0` ce qui signifie qu'il a été terminé correctement.

## Exo6

Avec l'option 0, `waitpid()` attends que le fils se termine avant de retourner.

Lorsqu'on le tue avec un terminal séparé on a les résultats suivants :

- la commande `kill -15 pid_fils` fait tuer lefils par le signal 15 : SIGTERM (terminaison propre et en douceur)
- la commande `kill -9 pid_fils` fait tuer le fils par le signal 9 : SIGKILL (assassinat brut et méchant)

Plus d'[information sur les signaux](https://www.linuxtricks.fr/wiki/signaux-unix-unix-signals).

## Exo7

Un double fork permet de créer 2 fils, et on peut attendre la fin du second avec la fonction `waitpid()`. Puisque l'on demande de définir le code retour avec `exit(2)` pour le second fils, le code retour sera 2.

## Exo9

On execute le code suivant :

```c

int main () {
    char buf [80];
    printf ("[%d]-- Debut du test exec () \n",getpid());
    sprintf (buf,"-- pid=[%d]", getpid());
    execl ("/bin/echo","echo","Execution","d'un test exec",buf, NULL);
    
    printf ("[%d]-- Echec de la fonction execl () \n",getpid());
    printf ("[%d]-- Fin du test exec () \n",getpid());
    exit (0);
}

```

Pour l'execution première (avec `echo`), on obtient :

```txt

[3731]-- Debut du test exec () 
Execution d'un test exec -- pid=[3731]

```

On remarque que le PID est identique, même si on change totalement de conatexte. On appelle la fonction `echo` qui prends en argument un ensemble de Strings qui seront affichés à la suite. On y ajoute le buffer contenant le PID. Le fait de mettre `/bin/echo` permet de préciser quelle fonction est appelée. La fin du code n'est pas executée car elle n'est jamais atteinte, sauf si une erreur apparaît (donc on ne voit ni "échec" ni même "fin du test").

> Remplacer `echo` par `ech` prooquera une erreur (cette commande n'existe pas) et donc cette fois la suite du code est executée et nous obtenons bien les 2 lignes de fin.

## Exo10

Avec `execl()` on obtient :

```txt

Début du fork + execl
  PID TTY          TIME CMD
  918 pts/4    00:00:00 bash
 8166 pts/4    00:00:00 recouvrement2
 8167 pts/4    00:00:00 ps
Fin du fork + execl
Statut du fils : 0

```

On remarque que le PID de ps est le même que celui du fils de recouvrement : en effet le `execl()` est appelé au sein du fils, et copie donc son PID (PID_père + 1).

Si on veut utiliser `execv()` on peut utiliser la syntaxe suivante :

```c

/// ...
char *args[] = {"-l", NULL};
execv("/bin/ps", args);
/// ...

```
