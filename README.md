# Philosophers

Le projet **Philosophers** est un projet du cursus de l'**École 42**. Il s'agit d'une implémentation en langage C du célèbre problème du dîner des philosophes (*Dining Philosophers Problem*), formulé par Edsger Dijkstra. L'objectif est d'appréhender les bases de la programmation concurrente, la gestion des threads et la synchronisation via des mutexes.

---

## Description du problème

Un ou plusieurs philosophes sont assis autour d'une table ronde. Au centre de la table se trouve un grand bol de spaghettis, et il y a autant de fourchettes que de philosophes.

Chaque philosophe alterne entre trois états :
1. **Manger** : un philosophe a besoin de deux fourchettes (la sienne et celle de son voisin) pour manger.
2. **Dormir** : après avoir mangé, il repose ses fourchettes et s'endort.
3. **Penser** : après s'être réveillé, il réfléchit jusqu'à ce qu'une fourchette soit disponible.

La simulation s'arrête si :
- Un philosophe meurt de faim (le temps écoulé depuis son dernier repas dépasse `time_to_die`).
- L'argument optionnel `number_of_times_each_philosopher_must_eat` est renseigné et tous les philosophes ont mangé au moins ce nombre de fois.

---

## Notions abordées

- **Multithreading** avec la bibliothèque POSIX threads (`<pthread.h>`).
- **Synchronisation et exclusion mutuelle** avec des mutexes pour protéger l'accès aux ressources partagées (fourchettes, état de mort, affichage, compteurs de repas).
- **Prévention des data races** et des interblocages (*deadlocks*).
- **Gestion fine du temps** (`gettimeofday`, `usleep`).

---

## Compilation

Le projet se compile avec `make` (utilise `cc` avec les flags `-Wall -Wextra -Werror -pthread`) :

```bash
make
```

Commandes disponibles :
- `make` : compile l'exécutable `philo`.
- `make clean` : supprime les fichiers objets `.o`.
- `make fclean` : supprime les fichiers objets et l'exécutable `philo`.
- `make re` : recompile l'ensemble du projet.

---

## Utilisation

Le programme s'exécute avec les arguments suivants :

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
| :--- | :--- |
| `number_of_philosophers` | Nombre de philosophes et de fourchettes autour de la table. |
| `time_to_die` (en ms) | Temps maximal sans manger avant qu'un philosophe ne meure. |
| `time_to_eat` (en ms) | Temps nécessaire à un philosophe pour manger (maintient 2 fourchettes). |
| `time_to_sleep` (en ms) | Temps passé à dormir après un repas. |
| `[number_of_times_each_philosopher_must_eat]` *(optionnel)* | Si spécifié, la simulation s'arrête quand chaque philosophe a mangé au moins ce nombre de fois. |

> Tous les arguments doivent être des entiers strictement positifs.

---

## Format des logs

Chaque action d'un philosophe est affichée au format suivant :

```text
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

- `timestamp_in_ms` correspond au temps écoulé en millisecondes depuis le début de la simulation.
- `X` est le numéro d'identification du philosophe (de 1 à N).
- Les messages d'état ne se chevauchent pas grâce à un mutex dédié aux sorties.
- L'annonce de la mort d'un philosophe n'est affichée qu'une seule fois et interrompt immédiatement la simulation.

---

## Exemples

- Simulation infinie sans mort (les philosophes ne doivent pas mourir) :
```bash
./philo 5 800 200 200
```

- Simulation avec arrêt après 7 repas par philosophe :
```bash
./philo 5 800 200 200 7
```

- Cas limite avec un seul philosophe (il n'a qu'une seule fourchette et meurt) :
```bash
./philo 1 800 200 200
```

- Cas où un philosophe ne devrait pas survivre :
```bash
./philo 4 310 200 100
```
