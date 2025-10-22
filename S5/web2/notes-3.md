# Fiche de Cours – Web Services (Session 3)
### Professeur : Raúl Mazo  
### Thème : Services RESTful avec un Micro-Framework (Express.js)  

---

## Objectif du cours
Cette session vise à apprendre à **implémenter des services RESTful** en utilisant un **micro-framework**.  
Contrairement aux frameworks full-stack, les micro-frameworks sont **plus légers**, **rapides** et **flexibles**, mais offrent moins de fonctionnalités intégrées.

### Compétences visées
- Comprendre la différence entre **framework complet** et **micro-framework**.  
- Créer et tester un **serveur RESTful** avec **Express.js**.  
- Manipuler les routes, les paramètres et le middleware.

---

## 1. Notion de Micro-Framework

### Définition
Un **micro-framework** est une version minimaliste d’un framework web.  
Il fournit uniquement les **fonctionnalités essentielles** pour créer des APIs :
- Routage (définition des endpoints),
- Gestion des requêtes et réponses HTTP,
- Middleware (traitement entre la requête et la réponse).

Il **n’inclut pas** :
- de moteur de templates,  
- de gestion d’authentification,  
- ni d’ORM (accès base de données).

### Avantages
- Très **rapide** à exécuter et à configurer.  
- **Flexible** et facilement extensible.  
- Idéal pour créer des **microservices**.

### Inconvénients
- Moins de fonctionnalités prêtes à l’emploi.  
- Nécessite plus de **configuration manuelle**.

---

## 2. Présentation d’Express.js

**Express.js** est un micro-framework pour **Node.js**.  
Il permet de créer des serveurs HTTP rapidement et d’ajouter des routes ou du middleware facilement.

### Installation
1. Initialiser le projet Node :  
   `npm init -y`
2. Installer Express :  
   `npm install express`
3. Lancer le serveur :  
   `node server.js`

### Création d’un serveur Express

```js
var express = require('express');
var app = express();
var PORT = 3000;

app.listen(PORT, function() {
    console.log("Server running on port " + PORT);
});
```

---

## 3. Routage dans Express.js

### Structure de base d’une route
Une route Express est structurée de la façon suivante :

```js
app.METHOD(PATH, HANDLER)
```

- **METHOD** : méthode HTTP (GET, POST, PUT, DELETE).  
- **PATH** : l’URL ou endpoint de l’API.  
- **HANDLER** : la fonction exécutée quand la route est appelée.

```js
app.get('/', (req, res) => {
    res.send('Hello World');
});
```

### Routage avec des chemins dynamiques
Les routes peuvent inclure des **paramètres** dynamiques dans l’URL.

```js
app.get('/things/:id', (req, res) => {
    res.send('The ID you specified is ' + req.params.id);
});
```

### Routes avec plusieurs paramètres

```js
app.get('/things/:name/:id', (req, res) => {
    res.send('Name: ' + req.params.name + ' and ID: ' + req.params.id);
});
```

### Routes avec expressions régulières
Les **regex** peuvent être utilisées pour restreindre les paramètres (ex. : id à 5 chiffres).

```js
app.get('/things/:id([0-9]{5})', (req, res) => {
    res.send('Valid 5-digit ID: ' + req.params.id);
});
```

---

## 4. Modularisation du Routage

Pour maintenir un code propre, Express permet de **séparer les routes** dans des fichiers distincts à l’aide de `Router()`.

```js
var express = require('express');
var router = express.Router();

router.get('/', (req, res) => {
    res.send('GET route on things.');
});

router.post('/', (req, res) => {
    res.send('POST route on things.');
});

module.exports = router;
```

et l'intégration du routeur :

```js
var express = require('express');
var app = express();
var things = require('./things.js');

app.use('/things', things);
app.listen(3000);
```

---

## 5. Middleware dans Express

Un **middleware** est une fonction exécutée entre la requête et la réponse.  
Il peut :
- Modifier la requête ou la réponse,  
- Gérer la sécurité (authentification),  
- Journaliser les requêtes,  
- Terminer ou passer la main à un autre middleware.

### Exemple de Middleware

Middleware simple qui fais un *log* :

```js
app.use('/other', function(req, res, next){
    console.log("Request received at " + Date.now());
    next();
});
```

### Ordre d’exécution des Middlewares
L’ordre d’écriture des middlewares détermine leur exécution :
1. Les middlewares globaux (`app.use()`),
2. Les middlewares spécifiques aux routes,
3. Les gestionnaires de routes.

```js
app.use(function(req, res, next){
    console.log("Start");
    next();
});

app.get('/', function(req, res, next){
    console.log("Middle");
    res.send("This is the things app!");
    next();
});

app.use('/', function(req, res, next){
    console.log("End");
    next();
});
```

---

## 6. Query Parameters et Route Parameters

### Query Parameters
Utilisés pour filtrer ou transmettre de petites informations :
`/api/products?category=phones&sort=price`

```js
app.get('/products', (req, res) => {
    let category = req.query.category;
    let sort = req.query.sort;
    res.send(`Category: ${category}, Sort by: ${sort}`);
});
```

### Route Parameters
Utilisés pour identifier une ressource spécifique :
`/api/products/:id`

Comme expliqué [ci-dessus](#3-routage-dans-expressjs).

---

## 7. Gestion des Erreurs

Express permet d’envoyer des réponses personnalisées :
- **404 Not Found** : lorsque la ressource n’existe pas.
- **500 Internal Server Error** : en cas d’erreur serveur.

```js
app.use('*', (req, res) => {
    res.status(404).send('Sorry, this is an invalid URL.');
});
```

---

## 8. Hands-on Lab 3 – TP Pratique

### Objectifs
- Créer un **serveur API REST** avec Express.js.  
- Implémenter des **routes dynamiques** et des **middlewares**.  
- Tester les routes avec **Thunder Client** ou **Postman**.

### Activités proposées
1. Créer un serveur Express affichant “Hello World”.
2. Implémenter une API `/things` avec les méthodes **GET** et **POST**.  
3. Ajouter un middleware de log affichant les requêtes reçues.  
4. Créer une API `/chilies` avec différentes routes et paramètres dynamiques.
5. Tester l’ensemble avec Thunder Client.

---

## 9. Conclusion

Express est un **outil puissant et léger** pour créer des **microservices RESTful**.  
Il permet une grande modularité, une rapidité d’exécution, et une flexibilité idéale pour les architectures modernes basées sur des **microservices**.

---

## À retenir

| Concept | Description |
|----------|-------------|
| **Micro-Framework** | Framework minimaliste offrant les fonctionnalités de base pour créer une API. |
| **Express.js** | Micro-framework Node.js permettant de créer des serveurs REST. |
| **Middleware** | Fonction intermédiaire qui traite la requête avant d’envoyer la réponse. |
| **Route dynamique** | Route utilisant des paramètres variables (ex: `/users/:id`). |
| **Router()** | Fonction Express permettant de modulariser le code des routes. |
| **Query Params** | Données passées dans l’URL après “?”. |
| **Thunder Client / Postman** | Outils de test pour les APIs HTTP. |
