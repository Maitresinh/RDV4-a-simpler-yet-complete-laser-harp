# Mécanique : planche d'abord, impression 3D ensuite

La mécanique de référence est une planche de contreplaqué. Le projet évite de transformer l'imprimante 3D en condition d'entrée.

Ordre de préférence :

1. support fourni avec le composant ;
2. quincaillerie standard : équerres, entretoises, colliers, tube noir ;
3. fichier 3D existant et correctement licencié ;
4. pièce paramétrique locale seulement si les trois solutions précédentes échouent.

## Planche recommandée

- contreplaqué de 12 à 18 mm ;
- format de départ : 600 x 300 mm ;
- finition noire mate ;
- quatre patins caoutchouc sous la planche ;
- aucun composant secteur accessible par le dessus.

Vue de dessus, joueur en bas :

```text
ARRIÈRE
┌──────────────────────────────────────────────────────────┐
│ Alim galvo  Drivers X/Y       Laser → [bloc galvo]       │
│ sous capot  sous capot                 ↑ sortie faisceaux │
│                                                          │
│ OPT101 près de l'origine des faisceaux                    │
│                                                          │
│ [zone octave VL53L4CD]    zone libre pour les mains      │
│                                                          │
│ E-stop   ARM   borniers   Teensy   DAC   interface galvo │
└──────────────────────────────────────────────────────────┘
AVANT / JOUEUR
```

## Pièces qui ne nécessitent normalement aucune impression

- bloc galvo : support métallique du kit ;
- drivers et alimentations : vis et entretoises ou boîte de dérivation ;
- Teensy et modules : entretoises nylon ;
- VL53L4CD : petite équerre métallique ;
- OPT101 : entretoises et tube noir mat ;
- câblage : colliers à embase vissée ;
- arrêt d'urgence : perçage de panneau standard.

## Distances initiales

- bloc galvo à 60 à 100 mm du bord arrière ;
- laser à 40 à 120 mm du bloc, selon l'angle d'entrée ;
- OPT101 à 30 à 80 mm de l'ouverture optique ;
- capteur d'octave à 150 à 300 mm à gauche de l'éventail ;
- électronique logique à au moins 80 mm des drivers galvo ;
- câble OPT101 éloigné des câbles moteurs et de l'alimentation galvo.

## Fixation du bloc galvo

1. Utiliser le support métallique du kit.
2. Présenter le bloc avec ses deux miroirs libres.
3. Marquer les trous du support.
4. Percer à 0,5 mm de plus que le diamètre des vis.
5. Utiliser rondelles et écrous freinés si les vis traversent la planche.
6. Ne jamais serrer directement une pièce imprimée contre le corps du galvo si le kit possède déjà un support métallique.

## Fixation du laser

Trois solutions, par ordre de préférence :

1. support métallique 12 mm réglable vissé à la planche ;
2. support 3D existant pour module AixiZ 12 mm ;
3. pièce paramétrique nouvelle uniquement après mesure du module reçu.

### Support 3D existant recommandé

**Laser XY Scanner**, par ThingEngineer.

- dépôt : https://github.com/ThingEngineer/Laser-XY-Scanner
- fichiers STL/CAD : https://www.thingiverse.com/thing:2710048
- licence annoncée : CC BY-SA 4.0
- usage : récupérer uniquement le support du module AixiZ 12 mm, pas la mécanique de scanner à moteurs pas-à-pas.

Le support doit permettre une rotation grossière et une petite correction d'inclinaison. Une cale fine ou une rondelle sous une vis est souvent plus simple qu'une rotule imprimée complexe.

## Pièces du projet Cybercraftics

- dépôt : https://github.com/cybercraftics/laser_harp
- dossier : https://github.com/cybercraftics/laser_harp/tree/main/3d_printables
- licence du dépôt : MIT

On peut examiner ses capots, supports de capteurs et petits accessoires. Ne pas reprendre sa tête de balayage telle quelle : elle est conçue pour un moteur pas-à-pas, alors que RDV4 utilise des galvos.

## Fixation de l'OPT101

1. Visser le module sur deux entretoises.
2. Ajouter un tube noir mat de 25 à 40 mm devant le capteur.
3. Fixer le tube avec gaine thermo, collier ou ruban noir mat.
4. Orienter le capteur vers le volume où passent les mains, pas vers le point direct du laser.

Aucune pièce 3D n'est nécessaire par défaut. Un tube PVC noir, une gaine large ou un corps de feutre vidé fonctionnent souvent mieux qu'un capot spécifique.

## Fixation du VL53L4CD

1. Utiliser les trous du breakout lorsqu'ils existent.
2. Le visser à une petite équerre métallique ou à un bloc de bois.
3. Orienter le capteur verticalement.
4. Ajouter deux parois latérales noires si les mains de jeu perturbent la mesure.
5. Ne pas enfermer le capteur derrière une fenêtre transparente non testée.

## Fixations électroniques génériques

Pour les cartes, préférer des entretoises nylon M2/M2.5/M3. Elles sont moins fragiles, plus rapides et plus universelles qu'un boîtier imprimé spécifique.

Pour des pièces existantes, rechercher :

- `universal PCB standoff screw mount` ;
- `M3 PCB clip mount` ;
- `WAGO 221 screw holder` ;
- `cable tie screw mount`.

Ne redistribuer un STL dans ce dépôt que si sa licence le permet et si l'auteur est crédité dans `NOTICE.md`.

## Capots

Les alimentations et drivers sont couverts par une boîte de dérivation, une plaque de contreplaqué sur entretoises ou un capot imprimé existant. Le capot doit :

- empêcher le contact avec les bornes ;
- laisser circuler l'air ;
- actionner le microcontact de sécurité ;
- rester démontable.

## Règle de licence

Pour chaque fichier tiers finalement copié dans ce dépôt, ajouter :

- nom du modèle ;
- auteur ;
- URL d'origine ;
- licence ;
- modifications effectuées ;
- date de récupération.
