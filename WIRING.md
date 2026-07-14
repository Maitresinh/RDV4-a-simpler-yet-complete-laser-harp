# Câblage détaillé

Le schéma KiCad correspondant est dans `hardware/kicad/RDV4_wiring.sch`.

## Philosophie de connectique

Le prototype de référence n'utilise ni coffret WAGO ni assortiment JST générique.

La solution la plus simple est :

- une barrette à vis découpable de 12 positions pour distribuer `5 V`, `3,3 V` et `GND` ;
- du fil souple silicone 24 à 26 AWG, soudé directement aux broches ou pastilles des modules ;
- de la gaine thermorétractable sur chaque soudure ;
- le câble Qwiic/STEMMA QT du VL53L4CD lorsqu'il est présent ;
- les câbles fournis avec le kit galvo, sans les remplacer.

Un connecteur « JST » n'est pas une référence suffisante : il existe de nombreuses séries et plusieurs pas. Ici, aucune pince à sertir JST n'est nécessaire. Les petits connecteurs amovibles pourront être ajoutés plus tard, après validation du prototype.

Les WAGO 221 restent pratiques pour un essai temporaire ou une réparation, mais ne sont pas nécessaires dans la version fixée sur planche. Ne pas laisser de connecteur volant sans maintien mécanique.

### Barrette basse tension

La barrette à vis est réservée à la basse tension. Exemple de répartition :

```text
1-2 : +5 V auxiliaire
3-4 : GND auxiliaire / logique
5-6 : +3,3 V logique
7-8 : retour chaîne interlocks
9-12 : réserve ou signaux nécessitant une dérivation
```

Ne jamais placer le secteur 230 V sur la même barrette. La partie secteur reste dans un capot séparé, utilise les bornes de l'alimentation galvo et une entrée secteur avec serre-câble, fusible et terre.

## Teensy 4.0

| Fonction | Broche |
|---|---:|
| bouton ARM vers GND | 2 |
| surveillance chaîne laser | 3 |
| TTL laser | 6 |
| LED état | 7 |
| CS MCP4822 | 10 |
| MOSI SPI | 11 |
| SCK SPI | 13 |
| sortie OPT101 | A1 |
| SDA VL53L4CD | 18 |
| SCL VL53L4CD | 19 |

Le Teensy 4.0 n'est pas tolérant au 5 V sur ses GPIO.

## Masse et alimentations

Créer un point de masse logique commun sur la barrette à vis :

- GND Teensy ;
- GND MCP4822 ;
- GND OPT101 ;
- GND VL53L4CD ;
- GND TTL laser ;
- masse signal de l'interface galvo selon le manuel du kit.

Ne pas mélanger au hasard la masse de puissance galvo et la masse logique. La connexion éventuelle se fait en un seul point, selon le manuel du kit et du module d'interface.

Le laser et les auxiliaires utilisent une alimentation USB 5 V séparée. Son GND rejoint le GND logique pour donner une référence à l'entrée TTL, mais son +5 V passe par la chaîne de sécurité.

## MCP4822

| MCP4822 | Connexion |
|---|---|
| VDD | 3,3 V |
| VSS | GND logique |
| SDI | Teensy 11 |
| SCK | Teensy 13 |
| CS | Teensy 10 |
| LDAC | GND |
| VOUTA | entrée X de l'interface différentielle |
| VOUTB | entrée Y de l'interface différentielle |

Placer 100 nF entre VDD et GND près du module si le breakout n'en possède pas.

Le firmware utilise :

- canal A pour balayer les douze cordes sur X ;
- canal B pour maintenir Y à sa position neutre.

## OPT101

- alimentation selon la fiche du module ;
- utiliser 3,3 V seulement si le module l'accepte explicitement ;
- sortie analogique vers A1 ;
- masse commune au Teensy ;
- câble court, torsadé avec GND ou blindé ;
- tube noir mat devant la photodiode.

La sortie ne doit jamais dépasser 3,3 V. Vérifier au multimètre avant connexion à A1.

## VL53L4CD

Avec connecteur Qwiic/STEMMA QT, utiliser un câble quatre fils adapté. Sinon souder directement :

- VIN vers 3,3 V ;
- GND commun ;
- SDA vers 18 ;
- SCL vers 19.

## Alimentation et TTL laser

### Coupure physique

```text
5 V auxiliaire
  → arrêt d'urgence NF
  → contact capot NF
  → V+ module laser
```

Souder les fils sur les cosses des interrupteurs puis protéger à la gaine thermo. Aucun WAGO n'est requis.

Le GND du module laser reste relié au GND logique afin que la commande TTL ait une référence commune.

### Commande TTL

```text
Teensy pin 6 → 1 kΩ → entrée TTL laser
                           ↓
                         10 kΩ
                           ↓
                          GND
```

Choisir un module dont l'entrée TTL reconnaît 3,3 V comme niveau haut.

## Surveillance de la chaîne laser

Prélever la tension après l'arrêt d'urgence et le contact capot :

```text
5 V après interlocks → 12 kΩ → pin 3 → 22 kΩ → GND
                                    ↓
                                  100 nF
                                    ↓
                                   GND
```

Avec 5 V, la broche reçoit environ 3,2 V. Ne jamais relier directement le 5 V à la broche 3.

## Interface galvo différentielle

Le kit retenu possède des entrées `X+ / G / X-` et `Y+ / G / Y-`.

```text
MCP4822 VOUTA → interface différentielle X → X+ et X-
MCP4822 VOUTB → interface différentielle Y → Y+ et Y-
GND logique / interface → G selon le manuel du kit
```

- régler une différence de 0 V entre `X+` et `X-` lorsque le canal A vaut 2048 ;
- commencer avec une amplitude différentielle inférieure à ±0,5 V ;
- régler une différence de 0 V entre `Y+` et `Y-` lorsque le canal B vaut 2048 ;
- ne relier ni `X-` ni `Y-` directement au GND.

## Schéma KiCad

Ouvrir `hardware/kicad/RDV4_wiring.sch`. KiCad 6 à 9 importe ce schéma legacy puis le convertit au format moderne `.kicad_sch` lors de l'enregistrement.

## Couleurs de fils conseillées

- rouge : 5 V ;
- orange : 3,3 V ;
- noir : GND ;
- jaune : TTL laser ;
- bleu : I²C ;
- vert : SPI ;
- blanc : signaux analogiques ;
- violet : surveillance de sécurité.

Étiqueter les deux extrémités de chaque câble avant de fermer les capots.