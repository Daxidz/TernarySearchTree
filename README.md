## Introduction
Ce projet est réalisé dans le cadre du laboratoire n˚6 du cours d'ASD2 de l'HEIG-VD.

## Environnement de développement
Le projet a été testé sur une machine ayant les spécifications suivantes :

* macOS Sierra 10.12.2
* g++ 4.2.1

## Compilation
Avant toute chose, vérifiez que les variables se trouvant dans le `Makefile` sont adaptées à votre système.

Puis dans un terminal :

    cd /path/to/folder
    make


## Documentation
La donnée du laboratoire est disponible à [cette adresse](files/donnee.pdf).

Une documentation à propos des algorithmes utilisés pour ce laboratoire est aussi disponible dans [ce dossier](files/) sous la forme de fichiers PDF.

## Implémentation
Il nous a été demandé d'implémenter un correcteur orthographique de deux manières différentes :

1. En utilisant une ou plusieurs structures de données de la STL.
2. En utilisant un *Ternary Search Trie* qui a été implémenté par nos soins.

Une explication détaillée des choix réalisés pour les deux implémentations est disponible plus bas.


## Choix
Pour la première partie, nous avons décidé d'utiliser la structure de donnée `unordered_set` car c'est celle qui offre la meilleure complexité quand il s'agit de chercher un élément stocké.

Pour ce qui est du Ternary Search Tree, nous avons décidé de ne pas rendre la classe générique car les arbres ternaires de recherche ont été inventés pour traiter des chaînes de caractères. Il nous a donc semblé inutile d'implémenter une classe générique.

L'arbre ternaire est composé de noeuds, chacun représentant un caractère d'un mot du dictionnaire. Chaque noeud possède un booléen `isEnd` qui indique si le noeud est la fin d'un mot du dictionnaire.
