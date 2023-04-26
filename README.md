
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