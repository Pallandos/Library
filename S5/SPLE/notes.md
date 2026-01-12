# Ingénierie de lignes de produits logiciels 

Aka *(Software) product line engineering* = SPLE ou PLE

# Introduction

Définition standardisée (SEI 2001) : *Une Software Product Line (SPL) est un ensemble de systèmes logiciels intensifs qui partagent un ensemble commun et géré de fonctionnalités (features) satisfaisant les besoins spécifiques d'un segment de marché, et qui sont développés à partir d'un ensemble commun d'actifs de base (core assets) d'une manière prescrite*

L'objectif est de produire en masse des produits customisés pour chaque client (donc de manière efficace). On introduit donc la notion de **feature** qui est une caractéristique, optionnelle ou non, que comporte (ou peut comporter) notre produit. 

Le PLE repose sur 3 **pilliers**:

- *commonality* = ce qui est commun à tous les produits d'une famille
- *variability* = ce qui distingue les produits les uns des autres
- *dependencies* = les contraintes logiques entre les features 

En gros, on doit au départ investir une grosse quantité de ressources (temps, humain, argent ...) pour construire une solide base (**core assets**). Puis, à partir de cette base on peut produire rapidement et facilement des produits en grande quantité et **configurables**. C'est à partir de ce moment que les choses deviennent rentables.

Les deux étapes pourraient être :

1. *domain engineering* : dessiner et concevoir le produit de base en analysant le problème. On pose donc les composants réutilisables etc
2. *application engineering* : on utilise les résultats de l'étape d'avant pour configurer les produits. C'est ici que l'on sort les produits

# Domain Engineering

L'objectif est de capturer et spécifier les exigences non pas pour un seul produit, mais pour toute la famille de produits. On doit donc définir les produits de manière *extensive*, c'est à dire tous les produits de cette famille. 

Les 3 activités principales de cette phase sont :

- Analyse : identifier la variabilité des produits
- Design : développer l'architecture de base
- Implémentation : Développer des composants réutilisables

> [!WARNING]
> Point vocabulaire : on distingue bien **request**, **need** et **requirements**. Le premier est une demande exprimée par le client, le second est un éléments réellement nécessaire au produit et le dernier est une caractéristique stricte, formulée dans le cahier des charges/specs.

Les exigences sont à classer dans 4 catégories selon de modèle *IREB* :

1. *functional - FR* : ce que le système doit faire
2. *quality - NFR* : ce que le système doit être 
3. *constraints* : limitations (souvent externes) non négociables (ex une norme ou une loi)
4. *process requirements* : contraintes sur la manière de concevoir le produit

Pour spécifier le PLE, on utilise un format bien particulier :

```
[CONDITION] <portée = all | some> <modalité = shall | should | could> <action> <objet>
```

Par exemple :

```
In case the 'Find and Replace' feature is activated, Those systems of the text editors product line that support prompts [Scope variable] shall [Priorité] provide the user with the ability to approve [Action] the changes.
```

Ce genre de documentation est normée, notamment avec la norme *ISO/IEC/IEEE 29148:2011*.
