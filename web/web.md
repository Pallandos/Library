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

Séparer HTML et CSS rends le code plus facile à maintenir : 

- HTML : la structure
- CSS : l'aspect

On peut donc appliquer un même style à plusieurs éléments sans recopier de code (**DRY**), ou changer un style sans toucher au HTML.

### Où placer son CSS

Il existe 3 possibilités pour écrire du CSS : 

- *Inline* : (avec un attribut `style`)
    - rapide à écrire
    - peu lisible, pollue le code
- *Interne* : (balise `<style>` dans `<head>`)
    - centralise le style de la page courante
    - si plusieurs page on dupplique du code
- *Externe* : (dans un `style.css`)
    - fichier séparé
    - facilité de lecture, centralisé 

### Les sélecteurs

Un sélecteur est un élement qui permet de délimiter à quels blocs de code seront appliqués le style courant.

> Les moteurs de rendu parcourent le DOM pour appliquer les styles. Dans un souci de performances, éviter les sélecteurs trop complexes

#### Sélecteurs d'éléments

Sélectionne tous les éléments d’un type donné (ex. `p`, `h1`, etc.) :

```css
p {
   color: blue;
}
```

#### Sélecteurs de classe

Sélectionne tous les éléments ayant l’attribut `class="..."` correspondant.

```css
.ma-classe {
  background-color: #f5f5f5;
}
```

Dans le html : 

```html
<div class="ma-classe">Contenu</div>
```

#### Sélecteurs d'ID

Sélectionne un élément portant l’attribut `id="..."` censé être unique dans la page :

```css
#mon-id {
  border: 1px solid #000;
}
```

Dans le html :


```html
<section id="mon-id">Contenu</section>
```

#### Sélecteurs d'attributs

Permettent de cibler un élément selon un attribut ou une valeur.

```css
input[type="text"] {
  border: 1px solid grey;
}

img[alt] {
  /* s'applique à tout <img> ayant un alt */
}

```

#### Pseudos classes et pseudos éléments

- Pseudo-classes (`:hover`, `:focus`, `:active`, `:nth-child()`, etc.) indiquent un état : survol de souris, focus clavier, ordre de l’élément…
- Pseudo-éléments (`::before`, `::after`, `::first-line`, etc.) ciblent une portion virtuelle ou générée, ex. du contenu ajouté avant ou après un élément.

Les pseudos classes permettent de faire du contenu réactif sans utiliser de javascript.

```css

a:hover {
  text-decoration: underline;
}

p::first-line {
  font-weight: bold;
}

```

Lorsque plusieurs règles ciblent le même élément, la spécificité détermine quelle règle prévaut.

- Sélecteur ID (`#quelquechose`) a une spécificité plus élevée.
- Sélecteur classe (`.machin`), pseudo-classes (`:hover`) et attributs (`[type="text"]`) ont une spécificité moyenne.
- Sélecteur d’élément (`p`, `h1`) a une spécificité plus faible.

### Media queries

Les media queries permettent de connaître les spécifités de l'appareil de l'utilisateur, pour adpater l'affichage du contenu. On code donc un seul site, mais qui s'adapte aux écrans des users.

### Bootstrap

Bootstrap est un *framework* qui propose des templates de sites et de style préconçus d'une GRANDE BEAUTE. Cela permet de créer très rapidement des sites beaux, mais avec l'inconvénient d'être dépendant et d'avoir des feuilles de style surchargées. 

Bootstrap vient avec un système de *grids* avec des classes qui gèrent le *reponsive design*

## Javascript

javascript a été une révolution : pn sort du HTML classique et statique. On peut enfin avoir des pages dynamiques qui répondent au user.

## Typescript

## Web Frameworks

## Laravel and view controllers

## Model Laravel

## Controller Model Dependencies (Bonus)