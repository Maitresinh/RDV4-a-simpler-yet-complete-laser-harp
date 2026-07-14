# Panier AliExpress conseillé

Les liens ci-dessous ouvrent des **recherches AliExpress ciblées**, pas des annonces figées. Choisir une annonce uniquement si elle respecte les critères indiqués dans le BOM.

## Exception recommandée : Teensy 4.0

Acheter le Teensy auprès de PJRC ou d’un revendeur agréé.

- [Teensy 4.0 officiel PJRC](https://www.pjrc.com/store/teensy40.html)
- [Recherche AliExpress Teensy 4.0, comparaison seulement](https://fr.aliexpress.com/w/wholesale-teensy-4.0-development-board.html)

## Cœur optique et mouvement

- **Module MCP4822 SPI double canal ×1** : [VOUTA=X; VOUTB=Y neutre](https://fr.aliexpress.com/w/wholesale-mcp4822-dual-dac-module-spi.html)
- **Kit XY 20 kpps avec alimentation ×1** : le kit identifié avec entrées `X+/G/X-` et `Y+/G/Y-` devient le choix de référence.
- **Convertisseur différentiel double canal ×1** : [quatre sorties X+/X-/Y+/Y-](https://fr.aliexpress.com/w/wholesale-dual-channel-differential-analog-signal-converter-module.html)
- **Module rouge 650 nm TTL ×1** : [lentille réglable, puissance mesurée <=1 mW](https://fr.aliexpress.com/w/wholesale-650nm-1mw-ttl-laser-module-5v-12mm.html)
- **Support laser 12 mm** : ne rien acheter d’abord. Imprimer le support AixiZ existant du projet [ThingEngineer / Laser XY Scanner](https://www.thingiverse.com/thing:2710048), puis adapter seulement la base et la hauteur. Un support métallique reste une solution de repli si le modèle reçu n’est pas réellement cylindrique en 12 mm.
- **Module OPT101 ×1** : [vendeur avec photo nette et brochage](https://fr.aliexpress.com/w/wholesale-opt101-photodiode-amplifier-sensor-module.html)
- **Breakout VL53L4CD ×1** : [version STEMMA QT/Qwiic possible](https://fr.aliexpress.com/w/wholesale-vl53l4cd-stemma-qt-qwiic-distance-sensor.html)

## Alimentation et sécurité

- **Adaptateur USB 5 V 2 A + breakout à vis ×1** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-5v-2a-eu-usb-power-adapter-screw-terminal-breakout.html)
- **Arrêt urgence 22 mm, contact NF ×1** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-22mm-emergency-stop-normally-closed-nc.html)
- **Microcontact capot NF ×1** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-roller-microswitch-normally-closed-nc.html)
- **Bouton ARM momentané NO ×1** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-momentary-push-button-panel-mount-normally-open.html)
- **LED 3 mm + résistance 330 ohm ×1** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-3mm-led-resistor-330-ohm-assortment.html)
- **Kit résistances métal 1 % + condensateurs 100 nF ×1** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-1-percent-metal-film-resistor-kit-ceramic-capacitor-100nf.html)

## Connectique simplifiée

Aucun coffret WAGO ni kit JST à sertir n'est nécessaire.

- **Barrette à vis découpable 12 positions ×1** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-12-way-screw-terminal-block-strip.html)
- **Fil souple silicone 24 à 26 AWG, six couleurs ×1 lot** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-24awg-26awg-silicone-wire-kit-6-color.html)
- **Gaine thermorétractable ×1 assortiment** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-heat-shrink-tubing-assortment.html)
- **Câble Qwiic/STEMMA QT ×1**, seulement si le VL53L4CD possède ce connecteur : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-qwiic-stemma-qt-cable-4-pin.html)

Les fils fixes sont soudés directement aux modules et protégés à la gaine thermo. La barrette sert uniquement à distribuer les basses tensions sur la planche. Les câbles fournis avec le kit galvo sont conservés.

## Montage sur planche

- **Entretoises nylon M2/M2.5/M3 ×1** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-nylon-pcb-standoff-m2-m2.5-m3-kit.html)
- **Petites équerres métalliques ×4** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-small-metal-angle-bracket-20mm.html)
- **Colliers à embase vissée ×1** : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-screw-mount-cable-tie-base.html)
- **Filtre rouge 650 nm ×1**, facultatif : [ouvrir la recherche](https://fr.aliexpress.com/w/wholesale-650nm-red-optical-bandpass-filter.html)

Les autres pièces 3D sont décidées après réception et mesure : bride de tube OPT101 seulement si nécessaire, berceau VL53L4CD seulement si le breakout se fixe mal. Voir `REUSED_3D_PARTS.md`.

## Commande en deux temps

1. Commander le Teensy, MCP4822, OPT101, VL53L4CD, passifs, sécurité et câblage minimal.
2. Commander le kit galvo de 100 EUR avec alimentation, puis choisir l'interface différentielle adaptée à ses entrées.

## Contrôle avant paiement

- confirmer que le laser accepte un HIGH TTL de 3,3 V ;
- vérifier que le VL53L4CD n'est pas remplacé par un VL53L0X ;
- vérifier que le convertisseur fournit bien `X+`, `X-`, `Y+` et `Y-` ;
- ne pas acheter un coffret WAGO de 20 EUR pour ce prototype ;
- mesurer le corps réel du laser avant impression du support 12 mm ;
- privilégier livraison Choice ou entrepôt UE lorsque le surcoût reste faible.
