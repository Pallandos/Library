# Fiche de Cours – Web Services (Session 2)
### Professeur : Raúl Mazo  
### Thème : Services RESTful avec un Framework Full-Stack  

---

## Objectif du cours
L’objectif de cette session est de comprendre et implémenter des **services RESTful** à l’aide d’un **framework full-stack**.  
Les compétences visées :
- Créer des services RESTful avec un framework complet.
- Tester les services RESTful avec des outils comme **Thunder Client** ou **Postman**.
- Explorer les bonnes pratiques pour concevoir des APIs robustes et maintenables.

---

## 1. Introduction aux Frameworks Full-Stack

Un **framework full-stack** offre une **solution complète** pour développer des applications web, incluant des outils pour :
- La gestion des routes,
- L’interaction avec la base de données,
- La gestion de la logique métier,
- L’authentification, etc.

### Avantages des frameworks full-stack
- **Productivité** : accélère le développement grâce à des outils intégrés.
- **Sécurité** : gère automatiquement des aspects comme l’authentification.
- **Structure** : impose une architecture cohérente pour les applications.

---

## 2. Framework Laravel : Création d’un service RESTful

### Installation de Laravel
Laravel est un **framework PHP** qui facilite la création d'APIs RESTful.  
Pour commencer avec Laravel :
1. Installez **PHP** et **Composer**.
2. Créez un projet Laravel avec la commande :  
   `composer create-project --prefer-dist laravel/laravel nom_du_projet`
3. Lancez le serveur de développement avec :  
   `php artisan serve`

### Création d’une API dans Laravel
- **Routes API** : Les routes sont définies dans `routes/api.php`.
- **Controllers** : Créez des contrôleurs pour gérer les requêtes HTTP.
    ```js
    public function index() {
        return response()->json(Product::all());
    }
    ```
- **Ressources** : Utilisez les classes **Resource** pour formater la réponse JSON.
    ```js
    namespace App\Http\Resources;

    use Illuminate\Http\Resources\Json\JsonResource;

    class ProductResource extends JsonResource
    {
        public function toArray($request)
        {
            return [
                'id' => $this->id,
                'name' => $this->name,
                'description' => $this->description,
            ];
        }
    }
    ```

---

## 3. Manipulation des Requêtes HTTP avec Laravel

### Routes API
Les routes dans `api.php` sont destinées à la gestion des **requêtes sans état**. Voici un exemple de route pour récupérer les produits :

```js
Route::get('/products', [ProductApiController::class, 'index']);
```

### Modèles et Eloquent ORM
**Eloquent** est le système ORM de Laravel, qui facilite l’interaction avec la base de données.

Exemple de modèle **Product** :

```js
namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Product extends Model
{
    use HasFactory;
}
```

### Validation des données
Laravel facilite la validation des données avec les **Form Requests**. Exemple de validation d'une requête **POST** pour créer un produit :

```js
$request->validate([
    'name' => 'required|max:255',
    'description' => 'required',
]);
```

---

## 4. Structurer une API RESTful Correcte

Une bonne **architecture API** repose sur plusieurs principes :
- **Utiliser les bonnes méthodes HTTP** : GET pour lire, POST pour créer, PUT/PATCH pour mettre à jour, DELETE pour supprimer.
- **Retourner les bons codes de statut HTTP** :
  - 200 OK pour une requête réussie,
  - 201 Created pour une ressource créée,
  - 400 Bad Request pour une erreur de validation,
  - 404 Not Found si la ressource n’existe pas.
- **Utiliser des ressources** pour encapsuler les données.

```js
public function show($id) {
    $product = Product::find($id);
    if (!$product) {
        return response()->json(['error' => 'Product not found'], 404);
    }
    return response()->json(new ProductResource($product), 200);
}
```

### Pagination
Lorsqu’il y a beaucoup de données, il est essentiel de paginer les résultats :

```js
public function index() {
    return response()->json(Product::paginate(10));
}
```

---

## 5. Testing de l’API

### Utilisation de Postman ou Thunder Client
Pour tester une API, des outils comme **Postman** ou **Thunder Client** permettent de simuler des requêtes HTTP et d'examiner les réponses.

Exemples de tests :
- Tester une **GET** pour récupérer tous les produits (`GET /api/products`).
- Tester une **POST** pour ajouter un produit (`POST /api/products`).
- Tester une **PUT** pour modifier un produit spécifique (`PUT /api/products/{id}`).
- Tester une **DELETE** pour supprimer un produit (`DELETE /api/products/{id}`).

### Exemple de Test avec Postman
1. **GET /api/products**
   - **URL** : `http://localhost:8000/api/products`
   - **Méthode** : GET
2. **POST /api/products**
   - **URL** : `http://localhost:8000/api/products`
   - **Méthode** : POST
   - **Body** :  

        ```json
        {
        "name": "Product A",
        "description": "Best product ever"
        }
        ```

---

## 6. Hands-on Lab 2 – TP Pratique

### Objectifs du TP
- Créer une API RESTful avec **Laravel**.
- Tester l’API avec un **client REST** (Thunder Client/Postman).
- Appliquer les bonnes pratiques dans la création d’APIs.

### Activités proposées :
1. **Installation de Laravel** : Créer un projet Laravel.
2. **Créer une API RESTful** : Implémenter les méthodes GET, POST, PUT et DELETE pour gérer les produits.
3. **Gestion des données** : Utiliser les ressources et la pagination pour gérer les réponses de l’API.
4. **Test de l’API** : Tester les différentes méthodes avec un client REST.

---

## 7. Conclusion

Lors de cette session, vous avez appris à créer et à gérer une API RESTful avec **Laravel**, en utilisant des **bonnes pratiques** pour la validation, la gestion des erreurs et la pagination. Vous avez également testé les API avec **Thunder Client** ou **Postman**.

---

## À retenir

| Concept | Description |
|----------|-------------|
| **Framework Full-Stack** | Un framework complet qui facilite le développement d’applications web. |
| **Laravel** | Un framework PHP pour créer facilement des APIs RESTful. |
| **Eloquent ORM** | Outil de Laravel pour interagir avec la base de données via des modèles. |
| **Pagination** | Diviser les résultats d'une requête en plusieurs pages pour améliorer les performances. |
| **Thunder Client/Postman** | Outils de test pour envoyer des requêtes HTTP et visualiser les réponses. |
