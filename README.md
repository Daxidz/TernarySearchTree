## Introduction
Ce projet est réalisé dans le cadre du laboratoire n˚6 du cours d'ASD2 de l'HEIG-VD.

## Documentation
La donnée du laboratoire est disponible à [cette adresse](files/donnee.pdf).

Une documentation à propos des algorithmes utilisés pour ce laboratoire est aussi disponible dans [ce dossier](files/) sous la forme de fichiers PDF.

## Implémentation
Il nous a été demandé d'implémenter un correcteur orthographique de deux manières différentes :
1. En utilisant une ou plusieurs structures de données de la STL.
2. En utilisant un *Ternary Search Trie* qui a été implémenté par nos soins.

Une explication détaillée des choix réalisés pour les deux implémentations est disponible plus bas.



## Choix
Pour la première partie, nous avons décidé d'utiliser la structure de donnée `unordered_set` car c'est elle qui offre la meilleure complexité quand il s'agit de chercher un élément stocké.
