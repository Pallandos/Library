# TP8 - Noyau temps réel

Jérémy COUTURE, Jean CAYLUS

## Preemption models

Nous avons trois options pour le modèle de préemption :

1. `No forced preemption (Server)` : pas d'interruption, les tâches sont faites sans arrêt
2. `Voluntary Kernel preemption` : la plupart des tâches sont non interrompues mais le user peut définir des portions de code qui peuvent être interrompues (en définissant des `might_sleep()` ou `cond_resched()`)
3. `Preemptible Kernel` : dans ce cas, toutes les tâches peuvent être interrompues (sauf dans certains cas avec des verrous)

Dans le cas du système `No forced preemption`, nous avons testé le programme du TP2 et nous avons les résultats suivants:

```txt
Nb mesures: 9500
Minumum: 28132575
Moyenne : 1013993
Ecart type : 76390
```

En le traçant dans un graphique en histogramme on voit l'image jointe **`base.png`**.

Nous allons maintenant perturber le CPU pour voir sa réactivité. Cette fois nous avons des valeurs différentes : 

```txt
Nb mesures: 9856
Minumum: 197416
Maximum : 1977542
Moyenne : 999996
Ecart type : 54420
```

Les données sont représentées dans l'image nommée **`perturbee.png`**. 

Comparons les deux cas. On observe dans le second cas que bien que l'écart type soit inférieur, les données semblent plus dispersées : on voit une base beaucoup plus large autour de la moyenne, car les pings ont perturbé le noyau. La majorité des interruptions semblent avoir lieu dans la région large autour de 1000000, contrairement au premier cas qui est bien plus régulier. 

## Linux - RT

En bash, l'option `--dry-run` permet de simuler l'execution de certaines commandes sans vraiment l'appliquer, mais en renvoyant les erreurs. Cela nous permet de vérifier qu'il n'y aura pas d'erreurs avant d'appliquer le patch en réel. 

Nous n'avons pas réussi à terminer le TP. Pour mesurer les décalages nous avons testé le code `time_pre.c` ci joint. Mais le binaire ne mesurait rien et se terminait silencieusement sans erreur. Nous avons alors tenté avec un script bash sans plus de succès. Le problème vient du fait que nius ne parvenions pas à obtenir le temps en ns. L'instruction `date +%s%N` ne renvoyait pas de résultat valide sur la carte bone, car l'option des ns (`+%N`) ne semble pas disponible. En mesurant en simple seconde tout fonctionnait mais il ne s'agit pas d'une échelle assez fine pour capter les différences des interruptions. 

Les ms auraient pu fonctionner mais il n'est pas possible d'obtenir la date en ms, car c'est soit en s soit en ns (les ms ne sont que des *fictives* et juste des ns tronquées). Donc, nous n'avons malheureusement pas pu continuer. 