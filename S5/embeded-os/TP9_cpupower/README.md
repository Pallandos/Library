# TP - gestion de l'énergie

Dans notre cas nous avons 5 governors: 

- *powersave*
- *performance*
- *ondemand*
- *userspace*
- *conservative*

En regardant le contenu de `scaling_governor` nous voyons que nous somems actuellement en mode *ondemand*. 

## Test de primalité 

Pour tester la primalité d'un nombre nous allons faire un algoritme qui teste tous les nombres inférieurs à n et vérifie si ils divisent n. Si il en existe un alors le nombre n'est pas premier, sinon il est premier. Cette approche n'est pas du tout optimisée mais le but est de tester des applications intensives. 

## Génération de vecteurs

Pour la génération de vecteurs nous avons implémenté une allocation dynamique, avec un malloc et nous utilisons la formule de la somme des composantes (dans une base orthonormée).

## Write données

Pour écrire des données nous avons utilisé la fonction `execv()` en construisant le tableau des arguments avec `NULL` à la fin. 