# Pièces 3D réutilisables et adaptations RDV4

L’objectif est de réutiliser des modèles existants uniquement lorsqu’ils simplifient réellement la construction. La mécanique de référence reste une planche de contreplaqué avec quincaillerie standard.

## Tableau final de décision

| Élément | Décision | Solution de référence | Modèle 3D existant | Adaptation RDV4 |
|---|---|---|---|---|
| Bloc galvo XY | Ne pas imprimer | support métallique fourni avec le kit | aucune | fixation directe sur la planche avec rondelles et écrous freinés |
| Module laser 12 mm | Imprimer de préférence | support 3D court et rigide pour module AixiZ 12 mm | support laser du projet [ThingEngineer / Laser XY Scanner](https://github.com/ThingEngineer/Laser-XY-Scanner), fichiers [Thingiverse 2710048](https://www.thingiverse.com/thing:2710048) | ne récupérer que le support laser ; adapter ou repercer la base pour deux vis M3 ; régler la hauteur par entretoises ou cales |
| Teensy 4.0 | Ne pas imprimer | entretoises nylon M2/M2.5 | support PCB universel seulement en option | fixation directe sur entretoises ; conserver l’accès USB et au bouton Program |
| MCP4822 | Ne pas imprimer | entretoises nylon ou petite plaque à pastilles | support PCB universel en option | accès libre aux sorties VOUTA/VOUTB et au connecteur SPI |
| OPT101 | Impression facultative | entretoises + tube noir mat | petite bride de tube ou support en L générique | choisir la bride après mesure du diamètre réel du tube ; ne pas enfermer la photodiode |
| VL53L4CD | Impression facultative | petite équerre métallique | petit berceau de breakout générique | seulement si le breakout reçu n’a pas de trous pratiques ; laisser la fenêtre ToF entièrement dégagée |
| Arrêt d’urgence 22 mm | Ne pas imprimer | perçage standard de panneau | aucune | montage traversant dans une petite façade ou un bloc de bois |
| Bouton ARM | Ne pas imprimer | perçage standard de panneau | aucune | accès immédiat depuis le bord avant de la planche |
| Barrette à vis | Ne pas imprimer | vissée directement sur la planche | support universel uniquement si nécessaire | séparer clairement 5 V, 3,3 V et GND ; jamais de secteur sur cette barrette |
| Câbles | Ne pas imprimer | colliers à embase vissée | passe-câbles génériques facultatifs | ajouter une décharge de traction près de chaque module |
| Capot alimentation/driver | Réutiliser un boîtier standard | boîte de dérivation ou capot en contreplaqué | capot imprimé seulement si aucun boîtier adapté n’est disponible | ventilation, accès aux vis, contact de capot et aucune borne secteur accessible |

## Support laser 12 mm : contraintes obligatoires

Le support retenu doit respecter :

- diamètre intérieur de 12,0 à 12,2 mm pour un corps type AixiZ ;
- base plane vissable sur la planche ;
- deux trous M3 espacés de 18 à 30 mm, ou socle plein reperçable ;
- axe laser à environ 25 à 60 mm au-dessus de la planche, réglé par entretoises ;
- réglage d’azimut obligatoire ;
- petite correction d’inclinaison par lumière oblongue, vis de réglage ou cale ;
- impression PETG recommandée, 4 périmètres et remplissage de 30 à 50 %.

Le support du projet ThingEngineer est une base de départ. Sa mécanique complète à moteurs pas-à-pas ne doit pas être reprise : RDV4 utilise un bloc galvo fermé beaucoup plus rapide.

## OPT101

La meilleure première solution reste :

- module vissé sur deux entretoises ;
- tube noir mat de 25 à 40 mm ;
- gaine thermo ou collier pour tenir le tube.

Une pièce 3D n’est justifiée que pour verrouiller l’orientation du tube. La pièce doit être une petite bride, pas un boîtier complet.

## VL53L4CD

Utiliser d’abord les trous du breakout et une petite équerre métallique. Un berceau 3D n’est utile que si :

- le module ne possède pas de trous ;
- l’orientation varie ;
- il faut ajouter deux joues latérales pour séparer la zone d’octave de la main de jeu.

Aucune fenêtre transparente ne doit recouvrir le capteur sans test préalable.

## Pièces Cybercraftics

Le dépôt [cybercraftics/laser_harp](https://github.com/cybercraftics/laser_harp) contient des pièces imprimables sous licence MIT. Ses petits supports, capots et accessoires peuvent servir de références. Sa tête de balayage ne doit pas être reprise telle quelle, car elle est conçue pour un moteur pas-à-pas.

## Quand adapter un modèle

Ne modifier un modèle tiers qu’après réception et mesure des composants. Consigner dans `NOTICE.md` :

- auteur ;
- URL d’origine ;
- licence ;
- fichier retenu ;
- modifications ;
- date de récupération.

## Quantité d’impression visée

- obligatoire : aucune ;
- très probable : un support laser 12 mm ;
- facultatif : une bride OPT101 et un berceau VL53L4CD ;
- à éviter : châssis complet, support galvo imprimé, boîtiers individuels pour chaque carte.
