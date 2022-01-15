---
marp: true
author: Dylan Robins
paginate: true
title: "Communication inter-processus: sémaphores"
style: |
  section {
    font-size: 20pt;
  }

---

# Communication inter-processus: sémaphores
Dylan Robins
2022-01-13

---

Lorsque deux processus accèdent simultanément à une ressource partagée, il peut y avoir des problèmes.

Exemples:
- Accès à une imprimante (seul un document peut être imprimé à la fois)
- Accès en écriture à un fichier (sinon risque de perte de données)
- Accès à une zone mémoire partagée ou à un port de communication (USART, USB, etc...)

Pour contrôler l'accès à ces ressources, on peut utiliser des **sémaphores**.

---

**Un sémaphore est un compteur** géré par le système d'exploitation. On l'utilise de la façon suivante:  
- On initialise le compteur à une valeur initiale (nombre de processus autorisés à accéder à la ressource en parallèle)
- A chaque fois qu'un processus veut accéder à la ressource, il décrémente le compteur (opération P - *proberen*)
- A chaque fois qu'un processus a fini d'utiliser la ressource, il incrémente le compteur (opération V - *verhogen*)

La subtilité est que lorsque le compteur vaut 0, **l'opération P bloque** jusqu'à ce que la ressource soit libérée.

---

**Implémentation en C**

Les sémaphores sont créés **par famille**: on ne créé pas *un seul* sémaphore mais *un groupe*. Ces groupes sont identifiés par une clé unique, générée à partir d'un fichier.

Cette famille doit être créée et initialisée avant d'être utilisée.

---

Création d'une famille se sémaphores:

```c
/* Création d'une famille de sémaphores
 * ARGUMENTS:
 * key: clé générée à partir d'un fichier
 * nb_sem: nombre de sémaphores à créer dans la famille
 * option: 'ou' logique des permissions d'accès et des options suivantes
 *    - IPC_CREAT (créer la famille si elle existait pas encore)
 *    - IPC_EXCL  (planter si la famille existait déjà)
 * VALEUR DE RENVOI:
 * int identifiant la famille de sémaphores créée
*/
int semget(key_t key, int nb_sem, int option);
```

---

Initialisation d'un sémaphore:

```c
/* Initialise un sémaphore dans une famille
 * ARGUMENTS:
 * semid: identifiant d'une famille de sémaphores
 * semnum: numéro du sémaphore à initialiser
 * cmd: macro SETVAL
 * init_val: valeur initiale du sémaphore
*/
int semctl(int semid, int semnum, int cmd, int init_val);
```

---

Les opérations sur les sémaphores se font via la fonction `semop`. Cette fonction prend en argument une structure définissant l'opération à effectuer:

```c
struct sembuf sb;
sb.sem_num = idx;       // Numéro du sémaphore à modifier
sb.sem_op = -1;         // Opération à effectuer: -1=decr/P, 1=incr/V
sb.sem_flg = SEM_UNDO;
semop(semid, &sb, 1);   // Effectue l'opération
```


