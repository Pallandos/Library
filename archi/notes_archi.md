# Introduction à l'architecture des ordinateurs

ALU = Arithmetic and logic unit

files de registre : stocke les données temporaires pour l'ALU

contrôleur : commande l'ordre des opérations de l'ALU, et reçoit les résultats des opérations.
Fonctionne sur 3 étapes :

- Fetch : lit une instruction dans la mémoire
- Décode : décode l'instruction lue (lis le registre source, le destination et l'opération)
- Execute : réalise l'instruction

**Architecture load store** : utilise la RAM en PLUS du registre pour stocker et charger les données

Le **bus d’interconnexion** permet de mapper toutes les mémoires (y compris les périphériques) en un seul espace mémoire. Cela permet de simplifier le travail du processeur. Les adresses mémoires du bus sont définies par le constructeur/concepteur de la machine.

Un système complet est donc constitué de l'ensemble:

- un ALU
- un registre
- un contrôleur
- une mémoire
- un bus
