Thiebaud Enzo p2207746, Yrius Marc. 

#=============================== Presentation ========================#
GestioTache est un gestionnaire de tâches qui permet à l'utilisateur de créer, modifier et supprimer des tâches. La page d'accueil affiche toutes les tâches existantes et l'utilisateur peut facilement accéder aux différentes fonctionnalités en utilisant les boutons dans le header.

Par exemple, pour afficher la page d'aide, l'utilisateur peut appuyer sur la touche F1. Pour quitter l'application, il peut utiliser la combinaison de touches Ctrl+Q, et pour sauvegarder les tâches, il peut utiliser la combinaison de touches Ctrl+S.

GestioTache offre donc une solution pratique et efficace pour gérer les tâches quotidiennes.


#=============================== Compilation ========================#
ÉTAPE 0)
Si vous ne possédez pas la bibliothèque Qt,
Rendez-vous sur le site de Qt et installez la bibliothèque.
Il est important de se souvenir où vous avez installé votre bibliothèque.

ÉTAPE 1 CONFIGURATION DE CMakeList.txt)

Rendez-vous dans le fichier CMakeList.txt à la racine du projet.
Allez à la ligne 15 et modifiez le chemin d'accès à la bibliothèque Qt.

ÉTAPE 2 COPIEZ-COLLEZ LA COMMANDE POUR LA PREMIÈRE COMPILATION)

Ouvrez un terminal à la racine du projet.
Entrez la commande suivante : "mkdir build && cmake -B build && cd build && make && cd .. && ./bin/GestioTacheApp"

ÉTAPE 3 COMPILATION EFFECTUÉE)

Copiez la commande suivante : "./bin/GestioTacheApp".
Collez-la dans le terminal à la racine du projet pour lancer l'application.

#=============================== Archive ========================#
Le dossier "app" contient l'application, ainsi que les ressources nécessaires. Le fichier "main" se trouve dans ce dossier et permet de lancer l'application.

Le dossier "appTexte" contient la librairie/objet "appgestiontachetexte".

Le dossier "tacheObjet" contient la librairie/objet "tache".

Le dossier "doc" contient la documentation relative au projet.

Le dossier "bin" contient l'exécutable ainsi que les fichiers qui stockent les tâches.

Le dossier "build" contient les fichiers compilés dans chaque dossier. Par exemple, le fichier "tache.o" se trouve dans le dossier "tacheObjet/...".
