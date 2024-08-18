# Simple Shell

## Description

Ce projet est une implémentation simplifiée d'un shell en C. Un shell est une interface de ligne de commande qui permet aux utilisateurs d'interagir avec le système d'exploitation en tapant des commandes. Ce projet vise à fournir une compréhension de base des concepts sous-jacents à un shell Unix, tels que la gestion des processus, l'exécution des commandes, et la manipulation des variables d'environnement.

## Fonctionnalités

- **Exécution de commandes** : Le shell peut exécuter n'importe quelle commande en fournissant le chemin complet de l'exécutable.
- **Gestion des variables d'environnement** :
  - `printenv` : Affiche toutes les variables d'environnement.
  - `setenv` : Définit ou modifie une variable d'environnement.
  - `unsetenv` : Supprime une variable d'environnement.
  - `showpath` : Affiche les répertoires contenus dans la variable `PATH`.
- **Support des commandes internes** :
  - `exit` : Quitte le shell.
  - `printenv` : Affiche toutes les variables d'environnement.
  - `setenv VAR_NAME VAR_VALUE` : Définit ou modifie une variable d'environnement.
  - `unsetenv VAR_NAME` : Supprime une variable d'environnement.
  - `showpath` : Affiche les répertoires dans le `PATH`.

## Installation

1. Clonez le dépôt :

   ```bash
   git clone https://github.com/votre-utilisateur/simple_shell.git
   ```

2. Accédez au répertoire du projet :

   ```bash
   cd simple_shell
   ```

3. Compilez le programme :

   ```bash
   gcc -Wall -Wextra -Werror -pedantic -std=gnu89 main.c commands.c processes.c environment.c utils.c -o simple_shell
   ```

## Utilisation

1. Exécutez le shell en tapant la commande suivante :

   ```bash
   ./simple_shell
   ```

2. Vous verrez apparaître une invite `"$ "` à laquelle vous pouvez entrer des commandes.

### Exemples de commandes

- **Exécuter une commande avec son chemin complet** :

  ```bash
  $ /bin/ls
  ```

- **Afficher toutes les variables d'environnement** :

  ```bash
  $ printenv
  ```

- **Définir une variable d'environnement** :

  ```bash
  $ setenv MY_VAR HelloWorld
  ```

- **Supprimer une variable d'environnement** :

  ```bash
  $ unsetenv MY_VAR
  ```

- **Afficher les répertoires du PATH** :

  ```bash
  $ showpath
  ```

- **Quitter le shell** :

  ```bash
  $ exit
  ```

## Structure du projet

- `main.c` : Fichier principal qui gère l'entrée de l'utilisateur et coordonne les autres modules.
- `commands.c` : Contient les fonctions pour traiter et exécuter les commandes utilisateur.
- `processes.c` : Gère la création et la gestion des processus (fork, wait).
- `environment.c` : Gère les variables d'environnement, y compris `setenv`, `unsetenv`, et `printenv`.
- `utils.c` : Fonctions utilitaires pour manipuler les chaînes de caractères et les variables d'environnement.
- `main.h` : Fichier d'en-tête contenant les déclarations de fonctions et de structures.


## Auteurs

- EVRADE, DIARRA, GENXWATER
