# Tutoriel détaillé de construction

Ce guide construit l'instrument par sous-systèmes. Ne saute pas directement au laser. La bonne méthode consiste à rendre chaque bloc prévisible avant d'ajouter le suivant.

## 0. Avant de commencer

### Résultat attendu

À la fin, la main droite coupe ou réfléchit l'une des douze cordes chromatiques. La main gauche se déplace au-dessus d'un capteur séparé pour choisir l'une des quatre octaves. Le Teensy apparaît comme périphérique USB-MIDI standard.

### Outils

- multimètre numérique ;
- fer à souder fin, étain et gaine thermorétractable ;
- tournevis, pince coupante et pince à dénuder ;
- perceuse et forets bois de 2,5 à 6 mm ;
- règle, équerre, crayon ;
- ordinateur avec PlatformIO ou Arduino IDE ;
- synthétiseur logiciel ou moniteur MIDI ;
- idéalement oscilloscope ou analyseur logique pour la latence, mais non obligatoire pour le premier montage.

### Matériaux mécaniques

- planche de contreplaqué 600 x 300 x 12 à 18 mm ;
- peinture noire mate ou adhésif noir mat ;
- entretoises nylon M2/M2.5/M3 ;
- petites équerres métalliques ;
- vis à bois courtes ;
- colliers de câble à embase vissée ;
- une boîte de dérivation ou un capot simple pour l'alimentation et les drivers.

### Règle de sécurité pendant le montage

Le module laser reste physiquement débranché jusqu'à la phase 8. Les premières validations optiques se font avec une LED rouge de 5 mm et sa résistance série.

## 1. Préparer la planche

1. Poncer les arêtes de la planche.
2. Peindre la face supérieure en noir mat.
3. Tracer trois zones :
   - à l'arrière, alimentation et drivers galvo ;
   - au centre arrière, tête galvo et support laser ;
   - à l'avant, Teensy, DAC, OPT101, boutons et borniers.
4. Réserver une colonne de 80 à 120 mm de large sur le côté gauche pour le capteur d'octave.
5. Poser les composants sans percer et vérifier que :
   - aucun câble secteur ne traverse la zone logique ;
   - le miroir du galvo reste accessible ;
   - le laser peut être aligné sans démonter l'électronique ;
   - le bouton d'arrêt d'urgence est accessible immédiatement.
6. Marquer les trous seulement après cette vérification.

Le dessin recommandé est dans `mechanics/board-layout.svg` et les dimensions sont détaillées dans `MECHANICS.md`.

## 2. Installer le logiciel

### PlatformIO

1. Installer Visual Studio Code.
2. Installer l'extension PlatformIO.
3. Ouvrir le dossier `firmware/`.
4. Connecter le Teensy par USB.
5. Compiler :

```bash
pio run -e teensy40
```

6. Téléverser :

```bash
pio run -e teensy40 -t upload
```

### Arduino IDE

Le sketch de diagnostic dans `firmware/examples/diagnostics/` peut être ouvert directement. Sélectionner :

- carte : Teensy 4.0 ;
- type USB : MIDI + Serial ;
- vitesse CPU par défaut.

## 3. Test USB-MIDI, sans autre électronique

1. Relier un bouton momentané entre la broche 2 et GND.
2. Ouvrir le sketch de diagnostic et régler `TEST_MODE` à `0`.
3. Ouvrir un moniteur MIDI ou un synthétiseur logiciel.
4. Appuyer sur le bouton.
5. Vérifier qu'un C4 est envoyé au Note On et qu'un Note Off arrive au relâchement.

Résultat attendu : aucune carte son ou passerelle série n'est nécessaire. Le Teensy apparaît directement comme périphérique MIDI.

En cas d'échec :

- vérifier le type USB choisi dans l'IDE ;
- essayer un autre câble USB, certains câbles ne transportent que l'alimentation ;
- vérifier que le bouton relie réellement la broche 2 à GND.

## 4. Monter et tester le MCP4822

### Câblage minimal

| MCP4822 | Teensy 4.0 |
|---|---|
| VDD | 3,3 V |
| VSS | GND |
| SDI | 11, MOSI |
| SCK | 13 |
| CS | 10 |
| LDAC | GND |
| VOUTA | point de test DAC |

Ne pas connecter le driver galvo à ce stade.

### Test

1. Régler `TEST_MODE` à `1`.
2. Placer le multimètre entre VOUTA et GND.
3. Le sketch produit successivement environ 0,9 V, 1,024 V et 1,15 V avec les valeurs de test prudentes.
4. Vérifier que les changements sont nets et répétables.
5. Si la sortie reste à 0 V : vérifier CS, LDAC, MOSI et SCK.
6. Si la sortie est proche du double : le module ou la commande utilise peut-être le gain 2x. Corriger avant de poursuivre.

## 5. Préparer l'interface analogique du galvo

Le MCP4822 fournit une tension unipolaire. Le driver galvo attend souvent une consigne centrée autour de 0 V. Le module offset/gain effectue cette conversion.

1. Lire la sérigraphie et la documentation du driver galvo.
2. Identifier :
   - entrée X+ ou X ;
   - entrée X- ou GND signal ;
   - entrée Y ;
   - masse signal ;
   - tension d'alimentation des drivers.
3. Ne jamais supposer qu'un connecteur est identique à celui d'une photo AliExpress.
4. Alimenter uniquement le module offset/gain.
5. Injecter la sortie du DAC.
6. Régler l'offset pour obtenir 0,00 V lorsque le DAC est à `DAC_CENTER`.
7. Régler le gain pour que la petite plage de test reste inférieure à environ -0,5 V / +0,5 V.
8. Vérifier que la sortie revient à 0 V lorsque le Teensy est réinitialisé ou que le DAC est centré.

Si le kit n'accepte que des entrées différentielles, utiliser un module différentiel documenté ou demander le schéma au vendeur. Ne relier jamais arbitrairement X- à la masse.

## 6. Monter les galvos sur la planche, laser absent

1. Utiliser en priorité le support métallique livré avec le kit.
2. Visser ce support sur la planche avec quatre vis et rondelles.
3. Installer les deux drivers et leur alimentation dans une zone protégée.
4. Garder les câbles moteurs éloignés du câble OPT101.
5. Alimenter les deux axes :
   - X reçoit la consigne variable ;
   - Y reçoit la consigne neutre prévue par le fabricant.
6. Ne laisser pas l'axe Y sans driver si le faisceau traverse ses deux miroirs.
7. Régler `TEST_MODE` à `4`.
8. Mettre sous tension les galvos.
9. Vérifier que les miroirs se déplacent très peu et sans choc mécanique.
10. Si le galvo tape une butée, vibre fortement ou siffle brutalement, couper immédiatement.
11. Augmenter progressivement la plage seulement après validation du centre.

Le premier éventail doit être volontairement étroit. La largeur finale se règle plus tard avec `DAC_MIN` et `DAC_MAX`.

## 7. Monter l'OPT101 et tester avec une LED

### Montage mécanique simple

La solution par défaut ne nécessite pas de pièce imprimée :

1. visser le module OPT101 sur deux entretoises ;
2. placer devant le capteur un morceau de tube noir mat de 25 à 40 mm ;
3. orienter le tube vers la zone où les mains couperont les faisceaux ;
4. placer l'OPT101 près de l'origine des faisceaux, mais hors du trajet direct du laser.

### Câblage

- alimentation selon la fiche du module, 3,3 V si explicitement compatible ;
- GND commun ;
- sortie analogique vers A1 ;
- câble court, torsadé avec GND ou blindé.

### Test LED

1. Brancher une LED rouge avec une résistance de 220 à 470 Ω à la place de l'entrée laser TTL.
2. Régler `TEST_MODE` à `3`.
3. Ouvrir le moniteur série à 115200 bauds.
4. Placer la main devant la LED et le capteur.
5. Observer trois valeurs : ambient, lit et delta.
6. Le delta doit augmenter lorsque la main renvoie la lumière rouge.
7. Tourner doucement l'OPT101 pour maximiser le delta et réduire la lumière ambiante.

Résultat attendu : le capteur doit distinguer clairement main présente et main absente sans laser.

## 8. Installer le VL53L4CD pour les quatre octaves

1. Fixer le breakout à une petite équerre métallique ou à un support existant.
2. Le capteur pointe verticalement vers le haut.
3. Le placer 150 à 300 mm à gauche de la zone des faisceaux.
4. Relier :
   - VIN à 3,3 V ;
   - GND à GND ;
   - SDA à 18 ;
   - SCL à 19.
5. Régler `TEST_MODE` à `2`.
6. Ouvrir le moniteur série.
7. Déplacer la main à quatre hauteurs confortables.
8. Noter les distances réelles.
9. Adapter `HEIGHT_BOUNDARIES_MM` dans `config.h`.

Les zones par défaut sont :

- moins de 280 mm : octave -1 ;
- 280 à 520 mm : octave de base ;
- 520 à 780 mm : octave +1 ;
- au-dessus de 780 mm : octave +2.

La main d'octave ne doit pas traverser les faisceaux musicaux. Séparer physiquement les deux zones améliore nettement la jouabilité.

## 9. Câbler la chaîne de sécurité laser

### Alimentation physique

```text
5 V laser
  → arrêt d'urgence, contact NF
  → microcontact de capot, contact NF
  → V+ du module laser
```

Le firmware ne remplace pas cette chaîne.

### Surveillance par le Teensy

La broche 3 n'est pas tolérante au 5 V.

1. Prélever le 5 V après les deux contacts de sécurité.
2. Utiliser un diviseur 12 kΩ en haut et 22 kΩ vers GND.
3. Relier le point milieu à la broche 3.
4. Ajouter 100 nF vers GND si la ligne est longue ou bruitée.
5. Le firmware configure la broche en pull-down afin qu'un fil débranché soit lu comme défaut.

### TTL laser

1. Relier la broche 6 au TTL du laser par une résistance de 1 kΩ.
2. Ajouter 10 kΩ entre TTL et GND au niveau du laser.
3. Vérifier que le laser choisi accepte réellement un niveau haut de 3,3 V.
4. Le laser doit rester éteint pendant le démarrage et lorsque le Teensy est débranché.

## 10. Premier alignement optique

Cette phase utilise uniquement un laser visible connu et mesuré à 1 mW maximum.

1. Enfoncer l'arrêt d'urgence.
2. Placer une terminaison mate au-dessus de la zone de jeu.
3. Fermer le capot des drivers et alimentations.
4. Fixer le laser dans son support, sans le serrer définitivement.
5. Centrer les deux galvos à 0 V.
6. Relâcher l'arrêt d'urgence uniquement lorsque personne ne peut placer les yeux dans l'axe.
7. Armer brièvement le laser.
8. Ajuster le support pour que le point frappe le centre du premier miroir.
9. Vérifier ensuite le trajet vers le second miroir puis vers le haut.
10. Couper le laser avant chaque correction mécanique.
11. Serrer progressivement le support.

Ne jamais utiliser un miroir de renvoi libre, une surface brillante ou une vitre dans la zone finale.

## 11. Charger le firmware principal

1. Ouvrir `firmware/` dans PlatformIO.
2. Compiler l'environnement `teensy40`.
3. Téléverser.
4. Mettre l'arrêt d'urgence en position coupée.
5. Mettre sous tension la logique et les galvos.
6. Vérifier que le miroir revient au centre.
7. Relâcher l'arrêt d'urgence.
8. Appuyer sur ARM.
9. Attendre la calibration initiale, sans main dans les faisceaux.
10. Tester une corde à la fois.

Pendant la calibration initiale, ne place aucune main dans la zone. Sinon le firmware apprend une main comme niveau de fond, ce qui est une manière très élégante de fabriquer un instrument muet.

## 12. Régler les douze cordes

1. Commencer avec `DAC_MIN` et `DAC_MAX` proches de 2048.
2. Élargir symétriquement par petits pas.
3. Chercher le plus petit éventail qui sépare confortablement les douze positions.
4. Réduire `GALVO_SETTLE_US` par pas de 5 à 10 µs.
5. Dès qu'une corde voisine se déclenche ou qu'un point tremble, remonter de 15 à 25 µs.
6. Ajuster les seuils corde par corde dans `PER_BEAM_ON_DELTA` et `PER_BEAM_OFF_DELTA`.
7. Vérifier la première, la sixième et la douzième corde, car elles révèlent souvent les défauts d'angle.

## 13. Régler les octaves

1. Jouer C avec la main d'octave dans la zone basse.
2. Monter la main vers les trois autres zones.
3. Vérifier C3, C4, C5 et C6 dans le moniteur MIDI.
4. Maintenir une note puis déplacer la main d'octave.
5. La note tenue ne doit pas changer ; seule la prochaine attaque utilise la nouvelle octave.
6. Si la zone oscille, augmenter `HEIGHT_HYSTERESIS_MM`.

## 14. Valider la jouabilité

Effectuer la séquence suivante :

- 100 attaques lentes sur une corde ;
- 100 attaques rapides ;
- 100 relâchements ;
- accords de deux puis trois notes ;
- chromatisme C à B dans chaque octave ;
- maintien de notes pendant changement d'octave ;
- fonctionnement continu 30 minutes.

Aucune note ne doit rester bloquée. Le bouton ARM doit couper toutes les notes et recentrer le galvo.

## 15. Mesurer la latence

Le budget théorique du contrôleur est inférieur à 3 ms, mais il faut mesurer la chaîne réelle.

Méthode simple :

1. activer une broche GPIO de diagnostic au moment du franchissement de seuil ;
2. la remettre à zéro juste avant `usbMIDI.send_now()` ;
3. mesurer à l'oscilloscope ;
4. mesurer séparément la latence audio du synthétiseur.

Pour l'ordinateur, utiliser ASIO, CoreAudio ou JACK avec un tampon de 64 ou 128 échantillons.

## 16. Finition

Une fois l'instrument validé :

- fixer définitivement les câbles ;
- ajouter un capot sur les alimentations et les drivers ;
- ajouter des étiquettes aux borniers ;
- protéger le bord de la planche ;
- conserver un accès aux potentiomètres de l'interface galvo ;
- imprimer uniquement les adaptateurs réellement nécessaires.

La version finale doit rester démontable. Un instrument maintenable vaut mieux qu'un sarcophage de colle chaude.
