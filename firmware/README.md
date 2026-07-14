# Firmware

## Compilation du firmware principal

```bash
platformio run -e teensy40
```

Dans l'IDE Arduino, sélectionner Teensy 4.0 et un type USB incluant MIDI + Serial.

## Diagnostic par étapes

Ouvrir `examples/diagnostics/diagnostics.ino`, modifier `TEST_MODE`, puis téléverser :

- `0` : USB-MIDI et bouton ARM ;
- `1` : MCP4822 au multimètre ;
- `2` : VL53L4CD et distances ;
- `3` : OPT101 avec LED rouge ;
- `4` : petite course galvo, laser débranché.

## Tests natifs

```bash
../tools/run_native_tests.sh
```

## Réglages principaux

Tous les réglages utiles sont dans `include/config.h` :

- course DAC ;
- temps de stabilisation ;
- seuils par corde ;
- frontières des quatre octaves ;
- puissance visuelle via le temps de maintien.

## Comportement d'octave

Le capteur tourne en continu. Le firmware stocke la dernière zone valide. Lorsqu'une corde déclenche un Note On, sa note MIDI est calculée avec cette octave et conservée jusqu'au Note Off.
