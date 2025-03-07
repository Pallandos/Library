# Dev WEB

Jean CAYLUS

## HTML

### Elements sémantiques 

En **HTML5** les balises sémantiques sont des éléments qui servent à améliorer la lisibilité du code, faciliter l'accessibilité d'un site et rendre une application plus accessible. En général ils ne possèdent pas de fonction technique, mais permettent au lecteur (ou au navigateur) de bien lire une page. Ils sont aussi utiles dans le référencement par les moteurs de recherche.

#### Structure

`<header>`:
- Représente l’en-tête d’une page ou d’une section de page.
- Peut contenir un titre, un logo, un menu, un moteur de recherche, etc.

`<nav>`:
- Désigne la zone de navigation principale ou secondaire.
- Contient généralement des liens vers les différentes sections du site (menu principal, pagination, etc.).

`<main>`:
- Indique le contenu principal ou le “cœur” de la page.
- Il ne doit y avoir qu’un seul `<main>` par page. Les zones communes (header, footer, menu) en sont exclues.

`<section>`:
- Définit une section thématique d’une page (un regroupement d’éléments ayant une thématique commune).
- Peut contenir un titre et regrouper plusieurs articles ou sous-sections.

`<article>`:
- Représente un contenu indépendant, comme un article de blog, un post de forum, un commentaire, une news…
- Peut être exporté ou syndiqué sans perdre de sens.

`<aside>`:
- Regroupe du contenu “à part” ou complémentaire au contenu principal (barre latérale, encadré contextuel, publicité, etc.).

`<footer>`:
- Pied de page d’un document ou d’une section.
- Peut contenir des informations de copyright, de contact, des liens de bas de page, etc.

#### Médias

`<figure>` :
- Conteneur pour un contenu autonome, comme une image, un schéma, un extrait de code ou un tableau.
- Généralement associé à un `<figcaption>` pour la légende.

`<figcaption>` :
- Légende ou description du contenu placé dans `<figure>`.

#### Divers éléments

`<address>` :
- Fournit les informations de contact (par exemple, l’adresse de l’auteur ou de l’entreprise).
- Souvent affiché en italique par défaut.

`<time>` :
- Spécifie une date, une heure ou un intervalle temporel.
- Permet d’indiquer aux machines (ex. Google, calendriers) le format temporel exact.

`<details>` et `<summary>` :
- Permettent d’inclure un bloc d’informations repliable/dépliable, souvent appelé “accordéon”.
- `<summary>` indique le titre cliquable qui affiche ou masque le contenu `<details>`.

`<mark>` :
- Met en évidence (highlight) un texte qui a une importance particulière.
- Visuellement, c’est un surlignage, et sémantiquement, cela montre que ce texte mérite l’attention.

`<blockquote>` et `<q>` :
- `<blockquote>` : pour une citation longue, généralement avec un retrait.
- `<q>` : pour une citation courte, en ligne (souvent accompagnée de guillemets automatiques).

`<abbr>` :
- Indique une abréviation ou un sigle.
- L’attribut title peut préciser la version complète de l’abréviation.

`<strong>` et `<em>`
- `<strong>` indique que le texte est important (sens fort, prioritaire).
- `<em>` marque une emphase, un texte sur lequel on insiste (par exemple, intonation différente).

`<cite>` :
- Signale une référence à un titre d’œuvre (livre, film, étude, etc.).

`<code>`, `<pre>`, `<samp>` :
- Pour afficher du code source ou des échantillons. 
- Sémantiquement, c’est pour mettre en avant des portions de texte “code informatique”.


`aria-label` est un élément qui permet de décrire parfaitement une page en cas de problème d'accessiblité. 

Les *CDN* (Content distribution networks) sont un ensemble de server qui sont répartis géographiquement de manière à limiter les délais de chargement, les coups de transferts etc.

### Stockage

De tous les formats d'images, les `.webp` sont les plus légers tout en conserevant une qualité d'image très bonne. Il est donc intéressant de les utiliser dans un site web contrairement aux `.png` ou `.jpg`.

Il existe 2 types de *storage* en **HTML5** : 

- session Storage : stockée uniquement le temps que la page reste ouverte (s'efface quand on ferme le navigateur). Utile pour enregistrer des informations de session
- local Storage : dans le cache du navigateur, ne s'efface jamais sauf si l'user le demande

## CSS et BootStrap

## Javascript

javascript a été une révolution : pn sort du HTML classique et statique. On peut enfin avoir des pages dynamiques qui répondent au user.

## Typescript

## Web Frameworks

## Laravel and view controllers

## Model Laravel

## Controller Model Dependencies (Bonus)
