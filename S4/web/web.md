# Dev WEB

Jean CAYLUS

- [Dev WEB](#dev-web)
  - [HTML](#html)
    - [Elements sémantiques](#elements-sémantiques)
      - [Structure](#structure)
      - [Médias](#médias)
      - [Divers éléments](#divers-éléments)
    - [Stockage](#stockage)
  - [CSS et BootStrap](#css-et-bootstrap)
    - [Où placer son CSS](#où-placer-son-css)
    - [Les sélecteurs](#les-sélecteurs)
      - [Sélecteurs d'éléments](#sélecteurs-déléments)
      - [Sélecteurs de classe](#sélecteurs-de-classe)
      - [Sélecteurs d'ID](#sélecteurs-did)
      - [Sélecteurs d'attributs](#sélecteurs-dattributs)
      - [Pseudos classes et pseudos éléments](#pseudos-classes-et-pseudos-éléments)
    - [Media queries](#media-queries)
    - [Bootstrap](#bootstrap)
  - [Javascript](#javascript)
    - [Les variables en JS](#les-variables-en-js)
    - [Closure en JS](#closure-en-js)
    - [Les manipulations du DOM](#les-manipulations-du-dom)
    - [JSON](#json)
  - [Typescript](#typescript)
    - [Le typage statique et inférence](#le-typage-statique-et-inférence)
    - [Les *generics*](#les-generics)
  - [Web Frameworks with React](#web-frameworks-with-react)
  - [Model View Controller (MVC)](#model-view-controller-mvc)
    - [View and Controller](#view-and-controller)
      - [Les routes](#les-routes)
      - [Controllers](#controllers)
      - [Blade](#blade)
    - [Model](#model)
      - [Migrations](#migrations)
      - [Seeding](#seeding)
  - [Controller Model Dependencies (Bonus)](#controller-model-dependencies-bonus)


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

Javscript est un langage crée pour favoriser la réactivité des pages web, coté server, favorisant la productivité des dev. Javascript a été une révolution : on sort du HTML classique et statique. On peut enfin avoir des pages dynamiques qui répondent au user.

Comme en Python ou en Java, JS est orienté objet et propose un héritage.

```js
class Parent {
  constructor(name) {
    this.name = name;
  }
  greet() {
    console.log('Hello from Parent');
  }
}

class Child extends Parent {
  constructor(name) {
    super(name); // Appelle le constructeur de Parent
  }
  greet() {
    super.greet(); // Appelle la méthode greet() de Parent
    console.log('Hello from Child');
  }
}

```

JS peut interragir avec le DOM pour la réctivité, et y attacher des *listener* : via la méthode `addEventListener`.

```js
document.getElementById('btn').addEventListener('click', () => {
  alert('Bouton cliqué !');
});
```

### Les variables en JS

On peut définir des variables avec 3 mots clés principaux : `var`, `let`, `const`.


1. `var` :
    - Portée fonctionnelle : si on déclare `var x` dans une fonction, la variable reste accessible dans tout le corps de la fonction.
    - Hoisting : la déclaration est “remontée” en haut de sa portée, mais initialisée à undefined.
    - Réaffectation et redéclaration possibles 
2. `let` :
    - Portée bloc : la variable est accessible uniquement dans le bloc délimité par `{ }`
    - Hoisting, mais en “zone morte” : la déclaration est connue du moteur JS mais on ne peut pas y accéder avant la ligne de déclaration, sinon `(ReferenceError)`.
    - Réaffectation autorisée, mais pas de redéclaration dans le même bloc.
3. `const`:
    - Portée bloc : comme `let`
    - Hoisting identique à `let`
    - Pas de réaffectation : la valeur reste constante, ce qui évite les modifications accidentelles.

> Pour `const` si la valeur est un objet ou un tableau, son contenu interne peut être modifié (les clés ou éléments), mais on ne peut pas réassigner la variable elle-même.

### Closure en JS

Le *closure* apparaît quand une fonction interne qui accède aux variables de sa fonction externe, même après que celle-ci ait fini d’exécuter. Cela permet d'encapsuler les données, de les garder privées, et d'avoir un code plus modulaire.

Exemple :

```js
function createCounter() {
  let count = 0;
  return function() {
    count++;
    console.log(count);
  }
}

let counter = createCounter();
counter(); // 1
counter(); // 2
```

### Les manipulations du DOM

Le DOM pour *Document Object Model* est un arbre de données qui est généré par le navigateur lorsque l'on charge une page web. JS a la capacité de lire, accéder et modifier la page HTML grâce à ce DOM. 

JS peut donc : 

Sélectionner des éléments :

```js
document.getElementById('monId');
document.querySelector('.maClasse');
document.querySelectorAll('p');
```

Les lire ou les modifier :

```js
element.textContent = 'Nouveau texte';
element.innerHTML = '<strong>Texte en gras</strong>';
```

> Attention aux différences entre `innerHTML`, `textContent` et `innerText`

- `innerHTML` : renvoie ou définit le contenu HTML (avec balises) d’un élément. Attention aux problèmes de sécurité (injection XSS) et aux performances
- `textContent` : renvoie le texte brut, sans balises, ni styles ; n’exécute pas de scripts. Plus sûr et plus rapide pour gérer du texte pur.
- `innerText` : comme `textContent` mais tient compte du style CSS (retours à la ligne, visuels, etc.). Moins standardisé, peut donner un rendu dépendant du navigateur.

Modifier le style :

```js
element.style.color = 'red';
element.setAttribute('title', 'Mon titre');
```

Gérer les événements :

```js
element.addEventListener('click', () => {
  // Action au clic
});
```


### JSON

`JSON` (*JavaScript Object Notation*) est une extension de fichier qui permet d'échanger des données entre le serveur et le navigateur. Plus simple et lisible que le `XML`, il a une compatibilité plus large. 

```json
{
    "menu": {
        "id": "file",
        "value": "File",
        "popup": {
            "menuitem": [
                { "value": "New", "onclick": "CreateNewDoc()" },
                { "value": "Open", "onclick": "OpenDoc()" },
                { "value": "Close", "onclick": "CloseDoc()" }
            ]
        }
    }
}
```
## Typescript

**Typecsript** est un sur langage de *Javascript*. En plus du JS, il prends en compte le typage statique, la programmation orientée objet, et des améliorations de producitivité. 

### Le typage statique et inférence

TS gère aussi l'*inférence* de type : c'est le fait de déterminer automatiquement le type d'une variable en fonction de sa valeur.

De même en TS, on a un typage statique : on définit une variable et son type : `let ma_variable: TYPE = valeur`. On ne peut donc plus lui attribuer une autre valeur sous peine d'erreur. Cela facilite la lisibilité, maintenance et robustesse du code. 

### Les *generics*

Les *generics* permettent de créer des composants réutilisables qui fonctionnent avec différents types de données. On ne précise pas le type explicitement. On évite donc la répétition et la maintenabilité du code. 

On écrit des generics avec la syntaxe : `function name<[type]>(arg : [type]){}`

```ts
function identity<T>(arg: T): T {
    return arg;
}

let output1 = identity<string>("Hello");
let output2 = identity<number>(42);
```

On peut aussi définir un type par défaut dans un générique :

**Pour conclure** : 

Quand TypeScript est avantageux :

- rojets de moyenne ou grande envergure, où la maintenabilité, la robustesse et la collaboration sont essentielles.
- Équipes nombreuses, car les types facilitent la communication entre développeurs.
- Refactorings fréquents : le système de types détecte les erreurs plus tôt.

Cas où JavaScript “pur” est suffisant :
- Petits scripts, prototypes ou pages statiques sans logique complexe.
- Environnements très contraints (sans outils de build).
- Rapidité de mise en place pour un code minimaliste, lorsqu’on préfère la simplicité à la sécurité des types.

```ts
function identity<T = number>(arg: T): T {
  return arg;
}
```

## Web Frameworks with React

**React** est une biliothèque JS qui est utilisée pour construire des web apps à page unique qui changent souvent de données affichées. 

Il implémente le *Virtual DOM* : c'est un clone du DOM, qui est utilisé pour savoir quels éléments du DOM ont changé, et donc de n'actualiser que ceux là. On gagne en efficacité.

Les *react hooks* sont des composants centraux de React : ils permettent d'ajouter l'état d'un composant sans avoir à re écrire de nouvelles choses. 

Les *react fragments* sont des contenants de plusieurs éléments react. Ils permettent d'accéder à ces éléments sans alourdir le DOM. 

**React**, par son approche déclarative et son *Virtual DOM*, facilite la création de pages dynamiques, maintenables et performantes. La clé est de bien structurer les composants (rôles clairs, découpage raisonnable de l’état), utiliser des mécanismes de mémoïsation et de réconciliation pour éviter des re-rendus superflus, et ainsi parvenir à une application fluide et plus économe en ressources.

## Model View Controller (MVC)

![image mvc](MVC.png)

**MVC** est une architecture utilisée en dev web, centrale. On découle l'apps en 3 principaux composants, chacuns avec un rôle précis.

1. Model
   - le cadre abstrait, canevas de l'app
   - gère les BDD et les données du système
2. View :
   - génère l'interface user 
   - représente l'état du model
3. Controller :
   - capture les interractions de l'user, les enregistre et les traite
   - invoque les actions définies par le model 
   - connait les règles de navigation (espaces acessibles à un moment donné etc)

> Dans le cadre du cours nous utilisons Laravel, un framework MVC pour PHP

### View and Controller

#### Les routes

Les **routes** définissent les liens internes de notre appli. Quand un user demande un lien interne, les routes appliquent leurs règles (connexion etc) et redirigent l'user. 

Les routes peuvent retourner une vue : 

```php
<?php
Route::get('/', function () {
    return view('welcome');
});
```

Appeler un contrôleur (avec ou sans argument):

```php
<?php
Route::get('/home', [HomeController::class, 'index']);

Route::get('/user/{id}', [UserController::class, 'show']);
```

Enfin, on code les règles de navigation à l'aide de *middleware* :

```php
<?php
Route::get('/dashboard', function () {
    // Code pour afficher le tableau de bord
})->middleware('auth');
```

#### Controllers

Les controllers permettent de gérer le traitement commun des routes, de grouper les middleware etc. On peut les créer rapidement dans Laravel avec la commande suivante : `php  artisan make:controller [MonController] --ressource`.

Le controller généré par défaut : 

```php
<?php
namespace App\Http\Controllers;

use Illuminate\Http\Request;

class TaskController extends Controller
{
  //
}
```

Un exemple simple de controller avec arguments/paramètre :

```php
<?php
namespace App\Http\Controllers;

use Illuminate\Http\Request;

class UserController extends Controller
{
    public function show($id)
    {
        return "User ID: " . $id;
    }
}
```

#### Blade

**Blade** est un langage de template : on écrit un code à trous. Cela rends le code plus facile à lire qu'en PHP, avec une plus grande capacité de customisation. 

On peut aussi utiliser des directives indiquées par un `@[directive]`, comme `@if`, `@for` etc. 

Il y a aussi un système d'héritage *(mais c'est bresson j'ai pas compris)* avec `@yield` et `@extend`.

### Model

Le **Model** permet de controller tout ce qui se passe dans l'appli. 

On y implémnente aussi les stratégies de chargement : un *lazy loading* sera toujours plus efficace qu'un *eager loading*. Le but est d'éviter de faire des requêtes inutiles.

Le model gère aussi les bases de données. **Eloquent** est l'outil de Laravel qui permet de gérer de manière très efficace les accès en base de donnée etc. Pour chaque table, on créer un model **Eloquent** associé. 

Dans un fichier `config/database.php` on gère les connexions aux database (Mysql etc).

#### Migrations

Une **migration** est un fichier qui permet de gérer un base de donnée : addition ou suppressio nde colone etc. Tout est écrit dans du code pour que les changements soient controlés et précis. Une migration est définie dans deux sens : `up()` et `down()`.

Exemple de migration pour créer un table : 

```php
<?php
use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateUsersTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('users', function (Blueprint $table) {
            $table->id();
            $table->string('name');
            $table->string('email')->unique();
            $table->timestamp('email_verified_at')->nullable();
            $table->string('password');
            $table->rememberToken();
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('users');
    }
}
```

#### Seeding

Le **Seeding** est une méthode qui vise à remplir ses bases de données de valeurs afin de tester le comportement de l'application. Pour que ces valeurs soient cohérentes avec l'application ou utilise des *seeders*.

Dans un seeder nous pouvons décrire le comportement voulu des données afin de créer des tables qui correspondent aux cas d'utilisation de notre appli web.

On peut créer des seeders avec la commande artisan : 

```sh
php artisan make:seeder UsersTableSeeder
```

Voici à quoi pourrait resembler un seeder pour créer des utilisateurs fictifs : 

```php
<?php
namespace Database\Seeders;

use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Hash;
use Illuminate\Support\Str;

class UsersTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('users')->insert([
            'name' => Str::random(10),
            'email' => Str::random(10).'@example.com',
            'password' => Hash::make('password'),
        ]);
    }
}
```

Après avoit fait son seeder, on peut les lancer pour tester nos applications en condition presque réelle. 


## Controller Model Dependencies (Bonus)