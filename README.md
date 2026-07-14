# RDV4, a simpler yet complete laser harp

Harpe laser ouverte à **un seul laser**, **un bloc de galvanomètres**, **12 cordes chromatiques**, **quatre octaves sélectionnées par hauteur** et **USB-MIDI natif**.

Le projet vise trois priorités, dans cet ordre :

1. simplicité de construction et de réglage ;
2. coût global raisonnable ;
3. faible latence et jouabilité réelle.

Il n'utilise aucun PCB personnalisé. Les éléments critiques sont des modules du commerce fixés sur une planche et reliés par borniers ou connecteurs.

## Résultat visé

- 12 faisceaux : C, C#, D, D#, E, F, F#, G, G#, A, A#, B ;
- 4 zones d'octave : C3-B3, C4-B4, C5-B5, C6-B6 ;
- octave mémorisée au moment du Note On ;
- polyphonie sur les douze faisceaux ;
- USB-MIDI natif, sans convertisseur série ;
- balayage complet visé sous 2,5 ms après réglage ;
- détection par réflexion avec soustraction de la lumière ambiante ;
- montage sur une planche de contreplaqué, sans châssis complexe ;
- pièces imprimées limitées au strict nécessaire ;
- arrêt d'urgence et contact de capot coupant physiquement le laser.

## Montage mécanique recommandé

La version de référence utilise une planche de contreplaqué noir mat de **600 x 300 x 12 à 18 mm**.

- le bloc galvo est vissé avec son support métallique d'origine ;
- le laser utilise de préférence un support métallique 12 mm du commerce ou un support 3D existant ;
- le Teensy, le DAC et les capteurs sont montés sur entretoises nylon ;
- le VL53L4CD est fixé à une petite équerre métallique ;
- l'OPT101 utilise un tube noir du commerce avant de recourir à une pièce imprimée ;
- les fichiers OpenSCAD éventuels sont des solutions de secours, pas le premier choix.

Voir `MECHANICS.md`.

## Tutoriel détaillé

Le guide complet est dans `TUTORIAL.md`. Il suit un ordre qui évite de brancher simultanément cinq sous-systèmes inconnus :

1. préparation de la planche ;
2. USB-MIDI ;
3. DAC seul ;
4. galvos sans laser ;
5. détection avec LED rouge ;
6. capteur d'octave ;
7. chaîne de sécurité ;
8. alignement du laser faible puissance ;
9. calibration et validation de latence.

Un sketch de diagnostic multi-mode est fourni dans `firmware/examples/diagnostics/`.

## Schéma KiCad et panier

- schéma de câblage KiCad : `hardware/kicad/RDV4_wiring.sch` ;
- guide d'import KiCad : `hardware/kicad/README.md` ;
- panier AliExpress : `ALIEXPRESS_CART.md` ;
- BOM avec liens d'achat : `BOM.csv`.

Le schéma représente le câblage des modules, pas un PCB. Le canal A du MCP4822 pilote X et le canal B maintient Y au neutre.

Les liens AliExpress sont des recherches ciblées plutôt que des annonces figées, car les vendeurs et identifiants changent régulièrement. Le Teensy 4.0 reste recommandé chez PJRC ou un revendeur agréé.

## Architecture

```text
main droite / mains de jeu
        ↓ réflexion du faisceau
OPT101 ───────────────→ ADC Teensy 4.0
                              │
VL53L4CD, zone octave ─I²C────┤
                              ├─USB natif──→ MIDI
Teensy 4.0 ─SPI→ MCP4822 ─→ interface bipolaire double canal ─→ drivers X/Y
                              │
                              └─TTL──→ laser 650 nm <= 1 mW

5 V laser → arrêt d'urgence NF → contact capot NF → module laser
```

Le kit XY complet reste alimenté : l'axe X balaie les cordes et l'axe Y reçoit une consigne neutre depuis le canal B du MCP4822.

## Par où commencer

1. `PURCHASE_CHECKLIST.md`
2. `ALIEXPRESS_CART.md`
3. `BOM.csv`
4. `MECHANICS.md`
5. `TUTORIAL.md`
6. `WIRING.md`
7. `hardware/kicad/RDV4_wiring.sch`
8. `CALIBRATION.md`
9. `SAFETY.md`

## Statut

- logique musicale, hystérésis et quantification d'octave testées nativement ;
- firmware écrit pour Teensy 4.0 et PlatformIO ;
- tutoriel et sketch de diagnostic fournis ;
- schéma KiCad de câblage par modules fourni ;
- validation matérielle encore nécessaire avec le kit galvo choisi ;
- aucun Gerber fourni, volontairement.

## Sécurité

Le prototype est prévu pour un laser visible mesuré à **1 mW maximum**. Il ne constitue pas un appareil scénique certifié. Lire `SAFETY.md` avant tout branchement du module laser.

## Licence

Le projet est publié sous **GNU GPL v3**, conformément au fichier `LICENSE` déjà présent dans le dépôt. Les modèles et projets tiers conservent leurs licences respectives. Voir `NOTICE.md`, `SOURCES.md` et `MECHANICS.md`.
