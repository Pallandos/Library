# Fiche de Cours – Web Services (Session 4)
### Professeur : Raúl Mazo  
### Thème : Services GraphQL  

---

## Objectif du cours
Cette session a pour but de comprendre et d’implémenter des **services GraphQL**, une alternative moderne et plus flexible aux API REST.  
GraphQL permet aux clients de **spécifier précisément les données** qu’ils souhaitent obtenir, en réduisant les problèmes de **surfetching** (trop de données) et **underfetching** (pas assez de données).

### Compétences visées
- Comprendre le fonctionnement de **GraphQL** et ses différences avec REST.  
- Créer un **serveur GraphQL** avec **Apollo** et **Express**.  
- Rédiger des **requêtes**, **mutations** et **subscriptions**.  
- Tester les requêtes GraphQL à l’aide d’un client.

---

## 1. Introduction à GraphQL

### Qu’est-ce que GraphQL ?
GraphQL est un **standard de requêtes d’API** développé par Facebook (maintenant Meta).  
Il fournit un moyen de **demander exactement les données nécessaires**, en une seule requête, via un **unique endpoint**.

### Avantages
- Une seule requête peut **récupérer des données complexes et liées**.  
- Évite la surcharge de données inutiles.  
- Facilite la **maintenance** et l’évolution des APIs.  

### Inconvénients
- Plus complexe à mettre en place qu’une API REST simple.  
- Les erreurs peuvent être plus difficiles à tracer.  
- Peut surcharger le serveur si les requêtes sont trop profondes.

---

## 2. REST vs GraphQL : Différences de fonctionnement

### Exemple : Application de blog
Un client veut afficher :
- Le **nom d’un utilisateur**,  
- Les **titres de ses publications**,  
- Et le **nom de ses trois derniers abonnés**.

#### En REST :
Il faut trois requêtes :
1. `/users/{id}`
2. `/users/{id}/posts`
3. `/users/{id}/followers`

Chaque endpoint renvoie souvent **plus d’informations que nécessaire**, provoquant un **overfetching**.

#### En GraphQL :
- Une seule requête à un **endpoint unique**.  
- Le client décrit précisément les champs voulus dans la **requête**.

Par exemple pour récupérer `user` et `follower` : 

```js
query {
  user(id: 1) {
    name
    posts {
      title
    }
    followers(limit: 3) {
      name
    }
  }
}
```

---

## 3. Structure d’un Service GraphQL

Un serveur GraphQL comprend trois éléments principaux :
1. **Le schéma** → définit la structure des données et les types disponibles.  
2. **Les resolvers** → contiennent la logique pour aller chercher les données.  
3. **Le serveur** → exécute et gère les requêtes GraphQL.

---

## 4. Le Schéma GraphQL (Schema Definition Language – SDL)

### Types de base
Les schémas GraphQL sont écrits en **SDL (Schema Definition Language)**.  
Exemple :

```js
type Person {
  id: ID!
  name: String!
  age: Int!
}

type Post {
  id: ID!
  title: String!
  author: Person!
}
```

### Relations entre types
Une personne peut avoir plusieurs publications, et chaque publication a un auteur.

```js
type Person {
  id: ID!
  name: String!
  age: Int!
  posts: [Post!]!
}

type Post {
  id: ID!
  title: String!
  author: Person!
}
```

### Requêtes (Queries)
Les requêtes GraphQL remplacent les endpoints REST.  
Elles définissent les **champs exacts** que le client souhaite récupérer.

```js
query {
  allPersons {
    name
    age
  }
}
```

### Mutations
Les **mutations** permettent de modifier les données (ajouter, modifier, supprimer).  
Elles suivent une syntaxe similaire aux requêtes.

```js
mutation {
  createPerson(name: "Alice", age: 30) {
    id
    name
    age
  }
}
```

ou pour mettre à jour :

```js
mutation {
  updatePerson(id: "1", name: "Alice Dupont", age: 31) {
    id
    name
    age
  }
}
```

### Subscriptions
Les **subscriptions** permettent de recevoir des données en **temps réel** via une connexion WebSocket.  
Elles s’activent lorsqu’un certain événement (comme la création d’un utilisateur) se produit.

```js
subscription {
  newPerson {
    id
    name
    age
  }
}
```

---

## 5. Les Resolvers

Les **resolvers** définissent la logique métier associée aux requêtes, mutations et subscriptions.  
Chaque champ d’un schéma GraphQL a un resolver correspondant.

### Exemple de résolveur

```js
import db from "./db.js";

export const resolvers = {
  Query: {
    people: () => db.people,
    posts: () => db.posts,
    person: (_, args) => db.people.find((p) => p.id === args.id),
    post: (_, args) => db.posts.find((p) => p.id === args.id),
  },
  Post: {
    author: (parent) => db.people.find((person) => person.id === parent.author_id),
  },
  Person: {
    posts: (parent) => db.posts.filter((post) => post.author_id === parent.id),
  },
  Mutation: {
    createPerson: (_, args) => {
      const newPerson = {
        id: (parseInt(db.people[db.people.length - 1].id) + 1).toString(),
        name: args.name,
        age: args.age,
      };
      db.people.push(newPerson);
      return newPerson;
    },
    updatePerson: (_, args) => {
      const person = db.people.find((p) => p.id === args.id);
      if (!person) return null;
      person.name = args.name || person.name;
      person.age = args.age || person.age;
      return person;
    },
    deletePerson: (_, args) => {
      const index = db.people.findIndex((p) => p.id === args.id);
      if (index === -1) return null;
      const deleted = db.people[index];
      db.people.splice(index, 1);
      return deleted;
    },
  },
  Subscription: {
    newPerson: {
      subscribe: (_, __, { pubsub }) => pubsub.asyncIterator(["NEW_PERSON"]),
    },
  },
};
```

### Hiérarchie des resolvers
- Les resolvers suivent la même structure que le schéma.
- Ils peuvent être organisés dans un **résolveur map**, chaque type ayant ses fonctions correspondantes.

---

## 6. Le Client et le Serveur GraphQL

### Côté serveur
- Le serveur utilise **Express** et **Apollo Server** pour recevoir les requêtes GraphQL.  
- Chaque requête est validée selon le schéma avant d’être exécutée.

```js
import { ApolloServer } from "@apollo/server";
import { expressMiddleware } from "@apollo/server/express4";
import express from "express";
import { typeDefs } from "./schema.js";
import { resolvers } from "./resolvers.js";

const app = express();
const server = new ApolloServer({ typeDefs, resolvers });

await server.start();
app.use("/graphql", express.json(), expressMiddleware(server));

app.listen(4000, () => {
  console.log("GraphQL server running at http://localhost:4000/graphql");
});
```

avec le schéma associé :

```js
export const typeDefs = `
  type Query {
    people: [Person!]!
    posts: [Post!]!
    person(id: ID!): Person
    post(id: ID!): Post
  }

  type Mutation {
    createPerson(name: String!, age: Int!): Person!
    updatePerson(id: ID!, name: String, age: Int): Person
    deletePerson(id: ID!): Person
  }

  type Subscription {
    newPerson: Person!
  }

  type Person {
    id: ID!
    name: String!
    age: Int!
    posts: [Post!]!
  }

  type Post {
    id: ID!
    title: String!
    author: Person!
  }
`;
```

### Côté client
Le client n’a qu’à envoyer une **unique requête POST** au serveur GraphQL, contenant :
- La **requête** (query),
- Les **variables** (facultatives).

```js
mutation {
  createPerson(name: "Charlie", age: 22) {
    id
    name
    age
  }
}
```

avec la réponse associée :

```json
{
  "data": {
    "createPerson": {
      "id": "3",
      "name": "Charlie",
      "age": 22
    }
  }
}
```

---

## 7. Exécution d’une Requête GraphQL

Lorsqu’une requête est reçue :
1. Elle est **vérifiée** par rapport au schéma.
2. Chaque champ est **résolu** par un resolver.
3. Les données sont **assemblées et renvoyées** sous forme d’objet JSON.

Le **moteur d’exécution** de GraphQL parcourt la requête champ par champ, exécute les resolvers correspondants, et reconstruit la réponse finale.

---

## 8. Hands-on Lab 4 – TP Pratique

### Objectifs
- Créer un **serveur GraphQL** avec Apollo et Express.  
- Implémenter des **queries**, **mutations** et **subscriptions**.  
- Tester les requêtes dans un client GraphQL (Apollo Studio ou Thunder Client).

### Activités proposées
1. Créer un **serveur Apollo** et installer la coloration syntaxique GraphQL.  
2. Créer un **schéma GraphQL** avec types `Person` et `Post`.  
3. Écrire les **resolvers** associés.  
4. Implémenter des **mutations** pour créer et modifier des personnes.  
5. Ajouter des **subscriptions** pour notifier la création de nouvelles personnes.  
6. Tester les requêtes et mutations dans le client GraphQL.

---

## 9. Conclusion

GraphQL permet une approche **flexible et efficace** pour construire des APIs modernes.  
Il centralise les données dans un **endpoint unique**, réduit la surcharge réseau et améliore la collaboration entre front-end et back-end.

### En résumé :
| REST | GraphQL |
|------|----------|
| Plusieurs endpoints | Un seul endpoint |
| Données fixes | Données dynamiques |
| Overfetching possible | Données précises et ciblées |
| Facile à mettre en place | Plus complexe mais plus puissant |

---

## À retenir

| Concept | Description |
|----------|-------------|
| **GraphQL** | Langage de requête pour interagir avec les APIs de manière flexible et précise. |
| **Query** | Permet de récupérer des données spécifiques. |
| **Mutation** | Permet de modifier ou ajouter des données. |
| **Subscription** | Permet de recevoir des mises à jour en temps réel. |
| **Schema (SDL)** | Définit la structure des données disponibles dans l’API. |
| **Resolver** | Contient la logique pour exécuter les requêtes et mutations. |
| **Apollo Server** | Librairie utilisée pour implémenter un serveur GraphQL. |
| **Express** | Serveur HTTP utilisé conjointement avec Apollo pour gérer les requêtes. |
