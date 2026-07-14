# Câblage détaillé

Le schéma KiCad correspondant est dans `hardware/kicad/RDV4_wiring.sch`.

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

Créer un point de masse logique commun près des borniers :

- GND Teensy ;
- GND MCP4822 ;
- GND OPT101 ;
- GND VL53L4CD ;
- GND TTL laser ;
- masse signal de l'interface galvo, uniquement si le fabricant autorise une entrée simple-ended.

Ne pas mélanger au hasard la masse de puissance galvo et la masse logique. La connexion éventuelle se fait en un seul point, selon le manuel du kit et du module d'interface.

Le laser et les auxiliaires utilisent une alimentation USB 5 V séparée. Son GND doit rejoindre le GND logique pour donner une référence à l'entrée TTL, mais son +5 V passe par la chaîne de sécurité.

## MCP4822

| MCP4822 | Connexion |
|---|---|
| VDD | 3,3 V |
| VSS | GND logique |
| SDI | Teensy 11 |
| SCK | Teensy 13 |
| CS | Teensy 10 |
| LDAC | GND |
| VOUTA | entrée X du module offset/gain |
| VOUTB | entrée Y du module offset/gain |

Placer 100 nF entre VDD et GND près du module si le breakout n'en possède pas.

Le firmware utilise :

- canal A pour balayer les douze cordes sur X ;
- canal B pour maintenir Y à sa position neutre.

Il faut donc un convertisseur bipolaire double canal, ou deux convertisseurs identiques.

## OPT101

- alimentation selon la fiche du module ;
- utiliser 3,3 V seulement si le module l'accepte explicitement ;
- sortie analogique vers A1 ;
- masse commune au Teensy ;
- câble court, torsadé avec GND ou blindé ;
- tube noir mat devant la photodiode.

La sortie ne doit jamais dépasser 3,3 V. Vérifier au multimètre avant connexion à A1.

## VL53L4CD

- VIN vers 3,3 V ;
- GND commun ;
- SDA vers 18 ;
- SCL vers 19 ;
- utiliser un breakout documenté pour logique 3,3 V.

## Alimentation et TTL laser

### Coupure physique

```text
5 V auxiliaire
  → arrêt d'urgence NF
  → contact capot NF
  → V+ module laser
```

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

Avec 5 V, la broche reçoit environ 3,2 V. Le firmware utilise un pull-down interne, donc un fil débranché ou une alimentation coupée est lu comme défaut.

Ne jamais relier directement le 5 V à la broche 3.

## Interface galvo double canal

Le MCP4822 ne commande pas directement les drivers.

```text
MCP4822 VOUTA 0..2,048 V → interface canal X → tension centrée 0 V → driver X
MCP4822 VOUTB 0..2,048 V → interface canal Y → 0 V calibré          → driver Y
```

- régler 0 V lorsque chaque canal DAC vaut 2048 ;
- commencer avec une amplitude X inférieure à ±0,5 V ;
- régler Y à son neutre et ne plus le balayer ;
- confirmer si chaque entrée est simple ou différentielle ;
- ne relier ni X- ni Y- à GND sans documentation ;
- laisser les deux drivers galvo alimentés si le faisceau traverse les deux miroirs.

## Schéma KiCad

Ouvrir `hardware/kicad/RDV4_wiring.sch`. KiCad 6 à 9 importe ce schéma legacy puis le convertit au format moderne `.kicad_sch` lors de l'enregistrement.

Le dossier contient aussi `net-labels.csv`, utile pour étiqueter les deux extrémités de chaque câble.

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
