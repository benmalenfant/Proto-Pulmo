# Proto-Pulmo
## Description
Ce repo github contient le code du projet de l'équipe Proto-Pulmo dans le cadre du cours ELE400

Le code est conçu pour être interfacer le capteur SLMX4 de SensorLogic sur une machine linux, détecter la respiration à partir des données du capteur et envoyer ces données vers le logiciel musical MaxMSP.

Documentation module capteur de SensorLogic:

https://github.com/SensorLogicInc/modules

Documentation plus poussée sur le circuit intégré du capteur

https://github.com/novelda/Legacy-Documentation

 
## Contenu
Le repo est separe en 3 dossiers principaux :
- **Boitier** 
	 -  Fichiers sources pour le boitier du capteur
	 -	Fichiers exportés pret à l'impression 3D
 - **Firmware_Capteur** 
	 - Code pour le logiciel embarqué qui roule sur le capteur 
	 - Viens de SensorLogic
 - **Matlab** 
	 - Scripts Matlab qui ont servi au développement de l'algorithme de detection
 - **SW_Repartisseur**
	 - Code C pour permettre l'interface avec le capteur, la détection de respiration et l'envoi des données vers MaxMSP

## Usage
