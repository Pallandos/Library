# TP2 ordonancement

## Get priority (question 1)

On observe un retour dy type :

```
➜  TPs git:(main) ✗ ./bin/tp2_get_priority
With getpriority():
Process ID: 28423
Process Priority: 0
 
With /proc/self:
policy                                       :                    0
prio                                         :                  120
```

La différence s'explique car la valeur donnée par `getpriority()` est sur une échelle de -20 à 19, alors que celle dans `/proc/self` est sur une échelle de 100 à 139 (utilisée en interne dans le scheduluer). Dans les fait, une valeur de 0 sur la première échelle correspond bien à 120 dans la seconde échelle.

> J'ai rajouté aussi la valeur `policy` qui définit la politique du scheduler. Ici on voit 0, ce qui correspond à `SCHED_OTHER` (soit *round-robin*)

## Set priority

On remarque que pour toute valeur de priorité supérieure à 0, nous n'avons pas besoin de `sudo`, mais si on veut passer la priorité en dessous de 0, on doit avoir les droits administrateurs. Cela peut se comprendre car plus une tache a une petite priorité, plus elle est importante. On peut donc imaginer qu'il s'agit d'un seuil qui empêche les user classiques d'avoir des process trop importants. 

Ci après la différence entre une execution avec et sans les droits sudo. 

```
➜  TPs git:(main) ✗ ./bin/set_priority
Before setpriority():
Process Priority: 0
 
After setpriority():
Process Priority: 0
➜  TPs git:(main) ✗ sudo ./bin/set_priority 
[sudo] password for melkior: 
Before setpriority():
Process Priority: 0
 
After setpriority():
Process Priority: -16
```

## Set policy

Pour changer la *policy*, on peut préciser la priorité à appliquer lors du changement. Ces valeurs de priorité doivent être entre le min et le max permis par la *policy*. Dans notre cas, pour `SCHED_FIFO`, c'est entre 1 et 99.

> Cela nécessite `sudo`

Exemple :

```
➜  TPs git:(main) ✗ please ./bin/set_policy
Before changing the policy:
policy                                       :                    0
prio                                         :                  120

After changing the policy:
policy                                       :                    1
prio                                         :                   79
```

## Question 4 : **timer**

### a) 

Pour cette question, je me suis inspiré de la page du *man* de `timer_create`. Beaucoup de difficultés sur cette question.