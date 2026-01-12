# `Prolog` - Inge ligne

*Prolog* est un language de vérification, simple et puissant. Son extension peut être `.pl` (conflit avec *perl*) ou `.pro`.

On peut utiliser `GNU prolog` comme compilateur. 

## Colibri

On part d'un exemple du cours et on écrit notre programme dans un fichier `.pro`. Puis on tape `gnuprolog` pour ouvrir le terminal. Puis pour compiler un fichier :

    consult('[absolut path]').

Ensuite on peut générer des configurations :

    colibriLP(Configuration).

On reçoit par exemple `Configuration = [1,1,1,1,1,1,1,0,0,1,0,1] ?` qui est une configuration valable pour notre définition. On peut appuyer sur `;` pour générer une autre configuration. 

Pour lister toutes les configurations :

    findall(L, colibriLP(L), Semantique).

De même, pour voir le nombre de configuration :

    findall(L, colibriLP(L), Semantique), length(Semantique, NombreSolutions).

On peut aussi imposer des configuration, et inclure des jokers avec `_` ce qui est très utile pour vérifier si nous avons des *dead features*.

## shs

Pour tester un dead feature, par exemple le F8, on va passer toutes les valeurs en joker et tester si une configuration est possible. 

```prolog
L = [1,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_],
findall(L,shs(L), Semantique),
length(Semantique, NSol).
```