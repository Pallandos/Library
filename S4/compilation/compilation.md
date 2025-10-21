# Compilation

- [Compilation](#compilation)
  - [Introduction](#introduction)
  - [Vue d'ensemble du compilateur](#vue-densemble-du-compilateur)


On va faire traiter un programme par un autre programme. On prends en entrée un texte (programme) et on sort un objet executable par la machine. 

## Introduction

Les langages, sont en général séparés en plusieurs paradigmes. 

| Impératif 	| Orienté objet 	| Fonctionnel 	| Déclararif 	|
|-----------	|---------------	|-------------	|------------	|
| Assembly  	| smalltalk     	| Lisp        	| SQL        	|
| Fortran   	| Java          	| Ocaml       	| Prolog     	|
| Rust      	| python        	| haskell     	| HTML+ CSS  	|
| Go        	| Dart          	| R           	| Prolog     	|
| Cobol     	| C#            	|             	| Markdown   	|
| Ada       	| Ruby          	|             	| SVG        	|

> Quelles sont les définitions d'un *langage de programmation*? On pourrait prendre la définiton de Turing.

Dans tous les cas, on a un foisonement de languages, de petits dialectes, tous pour une utilisation particulière. On a donc une foison de compilateurs.

## Vue d'ensemble du compilateur

**Définiton** : C'est un **programme** qui transforme un code source en un **code cible**.

Domaine théorique, clé dzans le monde de l'informatique. Le code source est en général un language informatique, et la sortie en binaire (executable).

Se découpe en plusieurs étapes : 

1. Analyse lexicale : découper le code en *lexèmes* (unité atomique de texte)
2. Analyse syntaxique : faire remonter les erreurs pertinentes au user. On y analyse la grammaire
3. Analyse contextuelle
4. Elaboration
5. Génération du code / assemblage

![schéma de la compilation](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e5/Cha%C3%AEne_de_compilation.svg/1024px-Cha%C3%AEne_de_compilation.svg.png)

## Analyse syntaxique

Une fois le code passé par l'analyse lexicale, on va passer à l'analyse syntaxique et produire un **arbre** en sortie. 

On utilise [**BNF**](https://fr.wikipedia.org/wiki/Forme_de_Backus-Naur) ou [**EBNF**](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form) pour décrire les grammaires.
