# Fiche de Cours – Web Services (Session 1)
### Professeur : Raúl Mazo  
### Thème : Motivation, Définitions et Services RESTful  

---

##  Objectif du cours
Apprendre à **décrire, définir, utiliser et implémenter** des **services web** et **microservices**.

### Compétences visées
- Créer et tester des **services RESTful** et **GraphQL**  
- Accéder aux **API endpoints**  
- Utiliser des **frameworks** (full-stack & micro) pour créer des services

---

##  1. Motivation : Pourquoi des Services Web ?
Exemple : une application de **covoiturage**

Fonctionnalités nécessaires :
- Authentification   
- Paiement   
- Géolocalisation   
- Gestion des trajets   

Au lieu de tout développer, on **réutilise des services existants** via leurs **APIs** (ex. Google Maps, PayPal…).  
C’est le principe de **l’ingénierie orientée services** (*Service-Oriented Engineering*).

---

## 2. Définitions clés

### Web Service
Un **service web** permet à **deux machines de communiquer** sur un réseau (souvent via HTTP).  
Il renvoie des **ressources** : JSON, XML, HTML, images, etc.

### API (Application Programming Interface)
Une **API** expose des **fonctions et des données** pour permettre à des applications de **communiquer** entre elles.  
Une **Web API** est donc la **porte d’entrée** d’un service web.

### RESTful API
Une **REST API** est une API web qui respecte les **principes REST (Representational State Transfer)** :
- Basée sur le protocole HTTP  
- Manipule des **ressources identifiées par des URLs**  
- Utilise des **méthodes HTTP standard**  

---

##  3. Architectures logicielles

| Type | Description | Avantages | Inconvénients |
|------|--------------|------------|----------------|
|  Monolithique | Tout le code (UI, logique, DB) dans une seule app | Simple à déployer | Peu flexible, difficile à maintenir |
|  SOA | Application divisée en services interconnectés | Réutilisable, modulaire | Complexe et coûteux |
|  Microservices | Petits services autonomes et spécialisés | Scalable, souple | Sécurité et orchestration plus difficiles |

---

## 4. Composants d’un Service RESTful

| Composant | Description |
|------------|-------------|
| **Ressources** | Les entités manipulées (ex : `/users`, `/products`) |
| **Verbes HTTP** | Actions à effectuer sur les ressources : `GET`, `POST`, `PUT`, `DELETE` |
| **Headers** | Métadonnées (type, format, auth…) |
| **Body** | Contient les données envoyées (souvent en JSON) |
| **Status Codes** | Indiquent le résultat : `200 OK`, `201 Created`, `404 Not Found`, `500 Error` |
| **Endpoints** | URLs d’accès aux ressources (`/api/users`, `/api/users/:id`) |

---

## 5. Implémentation d’un Serveur REST en Vanilla JS

### Étapes principales
1. **Créer un serveur HTTP**
   ```js
   const http = require('http');
   const PORT = 5000;
   const server = http.createServer((req, res) => {
     res.writeHead(200, {"Content-Type": "text/plain"});
     res.end("Hello World!");
   });
   server.listen(PORT, () => console.log(`Server running on port ${PORT}`));
   ```

2. **Créer une ressource simulée**

    ```js
    const todos = [
      { id: 1, title: "Créer un serveur", completed: true },
      { id: 2, title: "Aller au sport", completed: false }
    ];
    module.exports = todos;
    ```


3. **Implémenter les méthodes CRUD**

   - `GET` → récupérer les tâches
   - `POST` → ajouter une tâche
   - `PUT` → modifier une tâche par ID
   - `DELETE` → supprimer une tâche par ID

4. **Traiter le corps de la requête (POST/PUT)**

    ```js
    const getRequestData = (req) => {
      return new Promise((resolve, reject) => {
        let body = "";
        req.on('data', chunk => { body += chunk.toString(); });
        req.on('end', () => resolve(body));
      });
    };
    ```

## A retenir

| Concept |	Description |
| --- | --- |
| `REST` | Style d’architecture pour créer des services web |
| **API** |	Interface entre clients et serveurs |
| **CRUD** |	Create, Read, Update, Delete |
| `HTTP`	| Protocole utilisé pour la communication web |
| **Thunder Client**	| Outil de test d’API dans VS Code |
| **Vanilla JS**	| JavaScript sans framework (pur) |
