# Medical Triage System

## Description
Le **Système de Triage Médical** est une application conçue pour évaluer et prioriser les patients en fonction de leurs symptômes et de leurs facteurs de risque. En utilisant un modèle de **Random Forest**, le système permet de classer les patients en trois catégories de triage : **Critique**, **Modéré**, et **Faible**, facilitant ainsi la gestion des urgences médicales.

L'algorithme **Random Forest** est employé pour prédire l'issue de santé d'un patient en fonction de ses caractéristiques (symptômes, âge, sexe, etc.). Le modèle analyse ces données et génère un score de priorité, déterminant ainsi l'urgence du cas.

## Fonctionnalités
- **Création de patients** : Ajoutez des informations détaillées sur les patients, telles que leurs symptômes, leur âge, leur sexe et leurs conditions médicales.
- **Calcul de la priorité** : Le système attribue automatiquement un score de priorité en fonction des symptômes et des facteurs de risque du patient.
- **Triage automatique avec Random Forest** : Un modèle de **Random Forest** est utilisé pour prédire l'issue de santé du patient et déterminer sa catégorie de triage.
- **Sauvegarde des données** : Les informations des patients sont sauvegardées dans des fichiers CSV pour une gestion à long terme.
- **Affichage des patients** : Visualisez les informations de tous les patients enregistrés et triez-les par catégorie de triage.

## Algorithme de Random Forest
L'algorithme de **Random Forest** utilisé dans ce projet est un ensemble d'arbres de décision qui permettent de prédire le niveau d'urgence d'un patient en fonction de ses caractéristiques. L'algorithme attribue une importance à chaque caractéristique du patient (symptômes, âge, sexe, etc.), ce qui permet de classer le patient en fonction de sa gravité médicale.

## Installation
1. Clonez le dépôt du projet.
2. Utilisez le script `build.bat` pour compiler l'application.
3. Exécutez `run.bat` pour démarrer l'application.

## Utilisation
1. **Créer un patient** : Ajoutez un patient en entrant ses détails via l'interface principale.
2. **Afficher les patients** : Affichez tous les patients enregistrés et triez-les selon leur niveau d'urgence.
3. **Sauvegarder et lire des données** : Toutes les données sont enregistrées dans des fichiers CSV et peuvent être consultées à tout moment.

## Technologies
- **C++** pour l'implémentation du système
- **Random Forest** pour le modèle de triage
- **Fichiers CSV** pour la gestion des données
- **Scripts Batch** pour automatiser les tâches de build, d'exécution et de nettoyage

## Contribution
Les contributions sont les bienvenues. Si vous souhaitez améliorer ce projet, veuillez soumettre une pull request.

## Licence
Ce projet est sous licence MIT.
