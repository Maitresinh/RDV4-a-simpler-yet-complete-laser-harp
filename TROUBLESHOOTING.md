# Dépannage

## Le galvo ne bouge pas

- vérifier l'alimentation symétrique du driver ;
- vérifier l'entrée exacte du driver ;
- mesurer la sortie du module offset/gain ;
- confirmer masse signal commune en entrée simple ;
- vérifier que l'axe Y est lui aussi alimenté et centré.

## Les cordes voisines déclenchent

- augmenter `GALVO_SETTLE_US` ;
- réduire l'ouverture ;
- rigidifier le support ;
- resserrer l'angle du tube OPT101.

## Le capteur détecte tout

- éloigner les éclairages rouges ;
- ajouter un filtre 650 nm ;
- réduire le gain du module ;
- relever les seuils par corde.

## Notes bloquées

- vérifier la soustraction ambiante ;
- vérifier que le signal repasse sous le seuil OFF ;
- augmenter `RELEASE_CONFIRM_FRAMES` seulement si le signal est bruité ;
- vérifier le Control Change 123 lors du désarmement.

## Mauvaise octave

- éloigner le capteur d'octave de la zone de jeu ;
- réduire son champ avec deux petites parois noires ;
- vérifier les frontières en millimètres ;
- contrôler le statut de mesure du VL53L4CD.

## Le Teensy n'apparaît pas en MIDI

- sélectionner un type USB comprenant MIDI ;
- utiliser un câble USB de données ;
- fermer les logiciels qui monopolisent le port ;
- tester le mode diagnostic 0.

## Le laser reste allumé au démarrage

- couper immédiatement son alimentation ;
- vérifier la résistance de rappel 10 kΩ vers GND ;
- vérifier `LASER_ACTIVE_HIGH` ;
- vérifier que le TTL est réellement compatible 3,3 V ;
- ne pas poursuivre tant que l'état OFF au démarrage n'est pas garanti.
