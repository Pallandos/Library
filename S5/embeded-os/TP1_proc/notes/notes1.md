# TP1 - FHS

> [!NOTE]
> FHS = Filesystem Hierarchy Standard, propre à Linux. Voir [wikipedia](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard)

## `/proc`

On va travailler dans `/proc`, qui est une particularité de Linux. Ce dossier décrit l'état du système. Ce dossier est stocké en RAM au lieu d'en stockage, et on ne peut y écrire (`touch grass` échoue).

On peut retrouver tout un ensemble de fichiers d'informations sur le système. 

> [!NOTE]
> Les partitions indiquent énormément de partitions `loops`, ce qui serait dû à `snap`, qui installe chaque image de module sur une partition virtuelle. Dans ce fichier le nombre de blocs est le nombre de blocs de 1024B. 

### Procesus

Chaque sous dossier de `proc` est nommé selon le PID du procesus qu'il décrit. Dans les dossiers des process on retrouve plein de fichiers comme par exemple :

- `cmdline` : la commande lancée
- `status` : regroupe de nombreuses infos (pPID, tGID, nombres de threads, Uid, Gid)

## Utilisation de `ptrace`

La fonction `ptrace` peut être appelée avec les arguments suivants : 

```c
long ptrace(enum __ptrace_request request,
            pid_t pid,
            void *addr,
            void *data);
```

> [!WARNING]
> Pour utiliser ce tuto, il convient de changer les noms des registres et des librairies importées :
> - utiliser `sys/reg.h` car `linux/user.h` n'existe plus
> - changer `EAX` en `RAX`, `ECX` en `RCX` etc ...
> - changer les offsets de **4** à **8** car le tuto a été fait en architecture 32 bits

Si on intercepte le `write` du `ls`, on ne voit qu'un seul appel car le buffer tient dans un seul registre (de 64 bits maximum). Dans le tuto sur 32 cela ne passait pas donc on voyait de multiples appels. 

### Interception du `execl`

Dans cet exemple, je trace l'execution d'un fork de mon programme. Je lance un script qui envoie un buffer dans un fichier, et cela me renvoie plusieurs write :

```
Write called with 2, 110660678219456, 8
Write returned with 8
Write called with 2, 110660678219456, 81
melkior@melkior-ThinkPad-T480:~/Files/5-S5/embeded-os/TP1$ Write returned with 81
```