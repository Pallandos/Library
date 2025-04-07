# Cryptographie algorithmique

La crypto comporte 3 objectifs :

- confidentialité
- intégrité
- authentification

On écrit les spécifications des algo sous la forme : 

$$ C = Fonction(K, P) $$

Avec C le chiffré, K la clé et P le texte clair.

Aujourd'hui, la cryptographie se base sur l'impossibilité de factoriser de manière *rapide* des nombres premiers grands (aux environs de 500 chiffres).

## Attaquant et modèles de sécurité

Qu'est ce que la sécurité d'un algorithme? 

Une première approche consiste à définir comme *sûr* toute méthode qui empêche l'attaquant de trouver toute information cachée (inclus la clé et le texte clair).

### Adversaire

Voir le principe de Kerchoff : 

    La sûreté d'un algo ne saurait résider dans son caractère secret 

Il est défini par : 
- sa connaisance de l'algo (considérée comme complète : il connaît ses spécifications)
- ses capacités : calcul / mémoire / écoute
- un scénario 
  - un défi : trouver la clé, ou une partie, ou une partie du chiffré ou une information
  - un contexte

On définit donc des standards de complexité en temps et en calcul, en fonction des données actuelles et de l'état de l'art.

> Aujourd'hui réaliser 2^128 opérations prends plus de temps que l'âge de l'univers

Comme objectif, on préfère ne tolérer aucune attaque intelligente plus performante que la bruteforce. 

Les contextes : 
- chiffré connu
- clair connu
- clair choisi
- chiffré choisi

## Chiffrements symétriques

Les chiffrements de substitution mono alphabétiques sont TOUS vulnérables aux attaques fréquentielles. Donc [Vigénère](https://fr.wikipedia.org/wiki/Chiffre_de_Vigen%C3%A8re) avait conçu un chiffrement poly alpha qui brise les techniques fréquentielles. 

### Chiffrement par flots

> Un algo est dit parfait si la connaissance du chiffré ne donne pas d'informations.

Le chiffrement de Vernam est parfait mais la clé doit être aussi longue que le texte. C'est donc peu pratique mais c'est une technique dite parfaite. Plutot que de prendre une clé aussi longue, on peut utiliser un générateur pseudo aléat pour étendre la clé. On génère donc la clé à partir de la *seed*. Et donc la clé devient la *seed*.

Un **générateur de pseudo aléa** (GPA) est un automate à états finis et à temps discret fournissant à partir d’un germe de taille faible, des suites déterministes indiscernables de suites aléatoires lorsqu’on ne connait pas ce germe.

Pour satisfaire vernam, on ajoute un vecteur d'initilisation (IV) qui est transmis et qui modifie aussi la séquence aléatoire. Il rajoute une notion d'incertitude. 

> On déplace le problème à la création du générateur pseudo aléatoire...

#### Sécurité d'un GPA 

On doit évaluer sa robustesse car il fait partie intégrante de l'algo. 

On évalue les 3 critères suivants : 

- recouvrement 
  - de clé : connaissant l'IV  (ou des séquences) comment trouver la clé 
  - d'état interne : connaissant l'IV et/ou des séquences, trouver le clair
- attaque du caractère aléatoire
  - prédiction du bit suivant en connaissant une séquence plus au moins longue. L'ANSI impose un intervale de +- 2^-21 autour de 1/2
  - faiblesse de la répartition 
- indistinguabilité
  - real or random : on différencie une suite aléatoire d'une suite créee
  
#### Registres linéaires 

Il comporte un état interne qui se décale à chaque étape. Un seul bit d'état est recalculé à chaque étape, les autres sont décalés vers la droite.

### Chiffrement par bloc

Prends en entrée des blocs de taille fixe, avec une clé. On applique plusieurs *rounds* à notre clair, avec des sous clés itérés à partir de la clé initiale. Dans le standard actuel, on fixe la taille des blocs à 128 blocs. 

Les 4 critères de *perfection* du chiffrement AES / par bloc : 

- diffusion : tout influe sur tout
- ? 
- confusion
- indistinguabilité (par rapport à du hasard)

#### Mode opératoire

1. Découpage en blocs de N bits
2. padding ou bourrage : on rempli les blocs qui ne sont pas de N bits. C'est systématique, quitte à rajouter un bloc
3. application de la méthode parmi : 
  - ECB : electronic code book = mode dictionaire
  - CTR counter = par XOR, pseudo aleat et parallélisable
  - OFB output feed back = idem mais non parallélisable
  - CBC cypher bloc chaining = un mode chaîné 
  
## Chiffrement asymétrique

Dans ce principe, chaque utilisateur possède une clé séparée en 2 parties : une clé publique et une privé. En théorie, la clé privé peut se déduire de la clé publique : *mais* c'est trop long calculatoirement. Donc on se base sur ce principe. 

### La complexité calculatoire

Cette difficulté de calcul est la base de la crypto. Par exemple la [factorisaton des entiers](https://fr.wikipedia.org/wiki/D%C3%A9composition_en_produit_de_facteurs_premiers), le [logarithme discret](https://fr.wikipedia.org/wiki/Logarithme_discret)... 

### RSA

Aussi, grâce à la [comlexité de certaines opérations](#la-complexité-calculatoire) on construit le couple clé privé / publique. On suit le schéma suivant : 

$$ \text{Soient } (p,q) \in \mathbb{P} $$
$$ n = p \times q $$
$$ \text{Soit } e \in \mathbb{N} \text{ tel que } e \text{ premier avec } \phi(n) = (p - 1)(q - 1)  $$
$$ \text{Calcul de } e\in \mathbb{N} \text{ tel que } e \times d \equiv 1 \text{ mod } \phi(n)  $$

On a donc le couple : 

$$ \text{Clé publique : } (n,e) \text{ et privée : } (p,q,d)  $$

Les critères sont : 
- `p` et `q` de 1536 bits, et leur produit en possède 3072 
- `e` et `d` ont le même ordre de grandeur que `n`
