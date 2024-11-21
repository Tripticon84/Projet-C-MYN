# **Projet : Jeu de plateforme en 2D**

Inspiré des jeux comme Celeste ou Fireboy and Watergirl, Super Meat Boy, ce projet consiste à créer un jeu de plateforme simple et captivant avec des fonctionnalités engageantes, un système de sauvegarde et des niveaux évolutifs.

## **1. Objectif du Jeu**

Le joueur incarne un personnage dont le but est de récupérer une clé dans chaque niveau pour débloquer la porte menant au suivant. Il doit surmonter divers obstacles tels que des piques, des zones de lave, et résoudre des énigmes interactives.

## **2. Fonctionnalités Principales**

### **a) Gameplay**

Mécanismes de base :  
- Déplacements : gauche, droite, saut.  
- Interactions : récupération de clés.  
- Obstacles : pics, (lave, plateformes mouvantes).  
- Zones spéciales : portes verrouillées.

### **b) Système de sauvegarde**

Création de sauvegarde :  
- Le joueur entre un nom lors de la première partie.  
- 3 slots de sauvegarde  
- Contenu : niveau atteint, paramètres du joueur, score ou temps réalisé.

Chargement des données :  
- Si une sauvegarde existe, le joueur peut reprendre sa progression.  
- Sinon, une nouvelle partie est créée.

### **c) Système de paramètres**

Difficulté :  
\- Facile : vies illimitées.  
\- Normal : nombre limité de vies.  
\- Difficile : Une vie, temps limité

Paramètres personnalisables :  
\- Volume sonore.

## **3. Aspects Techniques**

### **a) Graphismes**

Utilisation de SDL2 pour les rendus en 2D. Sprites simples pour le personnage, les clés, et les obstacles. Animations basiques.

### **b) Interface**

Menu principal avec les options :  
- Lancer une partie.  
- Charger une sauvegarde.  
- Options (paramètres).  
- Quitter.

Interface en jeu : affichage du niveau, du score, et des vies restantes.

## **4. Développement des Idées Supplémentaires**

### **a) Enrichissement du Gameplay**

- Chronomètre : Encourager les joueurs à finir le niveau rapidement.  
- Pouvoirs temporaires : Invincibilité courte, double saut, gravité réduite.

### **b) Scoring et Classements**

- Scores basés sur : Temps pour terminer le niveau, collectible ramassé, Vies restantes.  
- Tableau des scores local pour encourager la rejouabilité.

## **5. Extensions Potentielles**

- Mode éditeur : Créer ses propres niveaux via un éditeur simple.  

