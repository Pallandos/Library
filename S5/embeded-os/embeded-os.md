# OS embarqué

On peut définir les systèmes embarqués comme des systèmes qui ne possèdent pas d'E/S standards, et dont le matériel et le logiciel sont très liés. L'OS qui ordonne tout ce systèmes est appelé **OS embarqué**. La **basse consommation** est généralement une caractéristique centrale de ces systèmes. 

On peur séparer les os embarqués en 2 catégories :

1. dits 'destinés à l'user' (*high-end*), issus d'un OS degradé
2. dits profondéments enfouis : avec peu de fonctions (ex montre, photo)

Ce n'est PAS pour les électroniciens uniquement... Très souvent écris en `C`/`C++`...

## Le temps

La gestion du *temps* est une préoccupation centrale des systèmes embarqués. En effet dans la plupart des cas ces systèmes interragissent non pas avec un utilisateur mais avec un système physique qui peut avoir des *responsabilités*, par exemple une sonde, un système de sécurité, un contrôleur de véicule etc... On attends donc de fortes garanties d'éxecution et notamment temporelles. On veut être certains que la tâche serra résolue en dessous d'un certain temps. Cela est bien sûr non exclusif avec la garantie d'une éxecution *juste*. 

Dans ce cadre, on peut définir la **latence** : c'est la différence de temps entre le moment où la tâche doit commencer (ou finir) et le moment où elle commence réellement (ou se finit). Elle est induite par les propriétés maéterielles des composants, aux politiques d'ordonancement, à la préemptibilité du noyau, à la charge du système etc. 

On considère deux catégories de *temps* en OS embarqué :

- temps réel : c'est le temps qui s'écoule littéralement en dehors du système. Un système temps réel est un système qui satisfait des critères temporels, quels qu'ils sont. On peut sous catégoriser en temps réel strict ou mou. 
- temps partagé : si pas de contrainte de temps alors on est en temps partagé

> [!TIP]
> Les ordres de grandeur de temps peuvent s'étendre de la ms pour les radars à plusieurs années pour les sondes/satellites

| Critère | Temps partagé | Temps réel |
|---|---|---|
| But | Maximiser la capacité de traitement (débit) & utilisation des ressources | Etre prévisible (garantir les temps de réponse) |
| Temps de réponse | Bon en moyenne | Bon dans le pire des temps  |
| Comportement à la charge | Confortable pour le user | Stabilité et respect des contraintes |

### Préemptibilité

Un **noyau préemptif** est un noyau qui peut interrompre une tâche avant qu'elle n'ait fini son exécution pour laisser la place à une autre tâche plus importante. 

| Critère | préemptif | non préemptif |
|---|---|---|
| CPU | La tâche peut être interrompue à tout moment | La tâche possède le CPU jusqu'à la fin de son exécution | 
| Durée d'exécution | Limitée par un quantum de temps (ou l'ordonanceur) | Peut être très longue | 
| Réactivité | Bonne dans le pire ces cas | Bonne en moyenne |
| Famine | Possible | Impossible | 

Jusqu'au noyau Linux `2.6̀  la préemptibilité est faible mais elle s'est améliorée depuis, avec la mise en place notamment de :

- **priorité statique** : défini le quantum de temps, est transmis par un père à son fils, utilisé pour classer les processus conventionnels. 
- **priotité dynamique** : détermine l'ordre d'exécution des tâches, calculée à partir du bonus
- **bonus** : entre 0 et 10, dépend de sa durée de sommeil
- **delta interractif** : détermine si le processus est interractif ou non
- **liste des actifs** : les processus qui n'ont pas encore épuisé leurs quantums de temps
- **liste des expirés** : ceux qui ont épuisé leur quantum, et qui doivent attendre que la liste des actifs soit vide pour se lancer
 
### License

De nombreux OS embarqués sont distribués sous license open source car plus facile pour des entreprises de petite taille.

## Architectures

On a plusieurs catégories

### Os Monolithique

Ancien, simple, ne consomme pas bcp de ressources. Tourne en général sur des vielles versions UNIX. Les modules logiciels du noyaux sont dans une seule couche. Tout le noyau est en mode privilégié.

| Avantages | Inconcévients |
| --- | ---|
| belles perfs | extension difficile |
| vite développé (on reprends un vieux) | pas de changement à chaud (on doit reboot) |
| chargements dynamiques | très gros et complexe |
| - | nid de bugs |
| - | un bug → un redémarrage |

### OS multicouches

Chaque couche repose sur la précédente.

| Avantages | Inconcévients |
| --- | ---|
| facile à étendre (bonne structure) | diffcile de traverser les couches |
| modèle plus simple | multiplication des couches non nécessaires |
| - | perf moins bonnes que les monolithiques |

> [!NOTE]
> Les `monolithiques` et `multicouches` peuvent être confondus dans certains cas.
  
### OS micro-noyau

On réduit au maximum le nombre de process privilégiés, on les place dans un petit noyau. Tout le reste fonctionne comme si un user utilisait la machine. Cela réduit la portion critique, car on peut redémarrer juste les process *serveurs*.

Ce mode est appliquable aux systèmes *distribués* : on peut mettre les services serveurs n'importe où.

| Avantages | Inconcévients |
| --- | ---|
| code plus petit | mauvaises perfs |
| sécurité | recquière bcp de prudence lors de la conception |
| peu de bugs | - |

### OS machine virtuelle

Un ou plusieurs OS *invités* sont hébérgés sur une machine, gérés par un **hyperviseur**. Il supervice la sécurité, les appels hors système etc.

On distungue deux modes:

- VM native : les OS invités sont directements sur le moniteur (hyperviseur sur couche matérielle)
- VM invité : l'hyperviseur est un programme au sein d'un autre OS (hyperviseur sur OS roi sur couche matériellle)

| Avantages | Inconcévients |
| --- | ---|
| multiples OS sur une machine | faible perf | 
| protection complète | manque de flexibilité | 
| bonne portabilité | - |
| bon env de dev | - |

## Ordonancement

Les différents types d'ordonanceurs sont :

- interractif
- batch
- temps réel (à priorité)

Puis, les **classes** d'ordonancement :

- FCFS : First Come First Serve
- Round Robin : idem préemptif
- SRT : Shortest Remaining Time
- SPN : Shortest Process Next
- feedback

En général, on  ordonance quand on a un nouveau process, par exemple après un fork, ou à la fin d'un process.

### Espaces des ordonancements et des priorités

Certains OS placent toutes leurs tâches dans le même *espace* de priorité. Mais, dans certains cas on sépare les tâches de l'OS et les tâches de l'utilisateur, par exemple dans le cas de tâches critiques. Dans le cas d'un airbag ou d'un train d'aterrissage, on veut que la tâche se lance, même avant l'OS si besoin.

On a **deux** priorités dans le système LINUX :

- priotité statique
- priorité dynamique

## Construction d'un OS embarqué

Puisque chacun veut une utilisation assez différente de son système embarqué, prendre une solution sur étagère est rarement la meilleure idée. En effet il faut en général optimiser son système pour qu'il corresponde très bien à sa propre utilisation. C'est pourquoi on veut construire son propre noyau. 

> [!NOTE]
> La mémoire est très couteuse sur un système embarqué, c'est ce que l'on va essayer de réduire au maximum en premier. Cela passe donc par une réduction du noyau, mais aussi des optimisations de compilation, de bibliothèques etc

On va donc mettre en place un système de **compilation croisée** : on construit son OS embarqué, réduit au minimum, il est juste conçu pour l'exécution, rien d'autre. On code les programmes sur une autre machine qui compilera en cross plateform pour n'envoyer que le binaire sur la carte. 

Par exemple `buildroot` est un framework qui permet de compiler seul son propre noyau, en choisissant avec attention chaque composant et option. Il produit en sortie une image du noyau ainsi que des outils de cross building, comme `gcc` etc...

La construction de l'OS se déroule selon les étapes suivantes :

1. Construction du noyau :
    - sélection du processeur
    - sélection des pilotes 
    - sélection d'options autres (par exemple le réseau, des modules etc)
2. Construction du système de fichiers
    - on déploie le *File Hierarchy Standard* : `/bin`, `/lib`, `/root` etc
3. Construction des applications / commandes
    - on ne met que les commandes dont on a besoin 
4. Configuration et démarrage 
    - on amorce le noyau à partir d'une commande `init x` avec x le niveau de démarrage 
