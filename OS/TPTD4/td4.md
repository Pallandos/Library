# TPTD4 : les ordonanceurs 

## Exercice 1 : évaluation de différents algo

### FCS

| FCFS                 	| A 	| B    	| C    	| D   	| E  	| Moyenne 	|
|----------------------	|---	|------	|------	|-----	|----	|---------	|
| Temps de terminaison 	| 3 	| 9    	| 13   	| 18  	| 20 	|      /   	|
| Temps de rotation    	| 3 	| 7    	| 9    	| 12  	| 12 	| 8.6     	|
| TR/TS                	| 1 	| 1.17 	| 2.25 	| 2.4 	| 6  	| 2.56    	|

> Le TR/TS est trop long (on doit se rapprocher de 1)

### Round Robin

| Tourniquet           	| A    	| B    	| C    	| D   	| E   	| Moyenne 	|
|----------------------	|------	|------	|------	|-----	|-----	|---------	|
| Temps de terminaison 	| 4    	| 18   	| 17   	| 20  	| 15  	|         	|
| Temps de rotation    	| 4    	| 16   	| 13   	| 14  	| 7   	| 10.8    	|
| TR/TS                	| 1.33 	| 2.67 	| 3.25 	| 2.8 	| 3.5 	| 2.71    	|

> Attente plus resserée mais plus longue, idéal pour l'interractif

### SPN

| SPN                  	| A 	| B    	| C    	| D   	| E   	| Moyenne 	|
|----------------------	|---	|------	|------	|-----	|-----	|---------	|
| Temps de terminaison 	| 3 	| 9    	| 15   	| 20  	| 11  	| x       	|
| Temps de rotation    	| 3 	| 7    	| 11   	| 14  	| 3   	| 7.6     	|
| TR/TS                	| 1 	| 1.17 	| 2.75 	| 2.8 	| 1.5 	| 1.844   	|

> SPN respecte la proportionalité de temps d'attente par rapport au temps d'execution. Peut créer de la famine

### SRT

Dans ce cas, on applique FCFS en cas d'égalité.

| SRT                  	| A 	| B    	| C 	| D   	| E  	| Moyenne 	|
|----------------------	|---	|------	|---	|-----	|----	|---------	|
| Temps de terminaison 	| 3 	| 15   	| 8 	| 20  	| 10 	| x       	|
| Temps de rotation    	| 3 	| 13   	| 4 	| 14  	| 2  	| 7.2     	|
| TR/TS                	| 1 	| 2.17 	| 1 	| 2.8 	| 2  	| 1.8     	|

> SRT un peu mieux que SPN mais on doit toujours connaître le temps d'execution du processus

### HRRN

Non préenmptif. On prends en compte R avec : 

$$ R = \frac{Ts+Ta}{Ts} $$

| HRRN                 	| A 	| B    	| C    	| D   	| E   	| Moyenne 	|
|----------------------	|---	|------	|------	|-----	|-----	|---------	|
| Temps de terminaison 	| 3 	| 9    	| 13   	| 20  	| 15  	| x       	|
| Temps de rotation    	| 3 	| 7    	| 9    	| 14  	| 7   	| 8       	|
| TR/TS                	| 1 	| 1.17 	| 2.25 	| 2.8 	| 3.5 	| 2.14    	|

> Essaie d'optimiser TR/TS mais n'est pas aussi efficace car non préemptif

### Feedback

Si le temps d'exécution total d'un processus n'est pas connu, on peut se baser sur le temps passé à s'exécuter. La priorité du processus baisse au fur et à mesure de son exécution (passage à une file différente et de priorité moindre).

| Feedback             	| A   	| B  	| C  	| D   	| E   	| Moyenne 	|
|----------------------	|-----	|----	|----	|-----	|-----	|---------	|
| Temps de terminaison 	| 4   	| 20 	| 16 	| 19  	| 11  	| x       	|
| Temps de rotation    	| 4   	| 18 	| 12 	| 13  	| 3   	| 10      	|
| TR/TS                	| 4/3 	| 3  	| 3  	| 2.6 	| 1.5 	| 2.29    	|