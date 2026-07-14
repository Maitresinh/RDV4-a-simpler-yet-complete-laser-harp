# Checklist de première mise sous tension

## Avant toute alimentation

- [ ] laser physiquement débranché ;
- [ ] arrêt d'urgence enfoncé ;
- [ ] aucune carte posée directement sur la planche ;
- [ ] aucune vis sous une carte ;
- [ ] polarités vérifiées au multimètre ;
- [ ] Teensy et modules logiques reliés à une masse commune ;
- [ ] alimentation galvo séparée et conforme au kit ;
- [ ] axe Y relié à sa consigne neutre ;
- [ ] sortie de l'interface galvo réglée à 0 V au centre ;
- [ ] broche Teensy 3 protégée du 5 V par le diviseur 12 kΩ / 22 kΩ ;
- [ ] TTL laser muni de la résistance série et du rappel vers GND.

## Mise sous tension logique

- [ ] Teensy reconnu en USB-MIDI ;
- [ ] DAC centré ;
- [ ] VL53L4CD détecté ;
- [ ] OPT101 dans une plage ADC normale ;
- [ ] bouton ARM fonctionnel ;
- [ ] ouverture de la chaîne de sécurité produit un état FAULT.

## Mise sous tension galvo

- [ ] laser toujours débranché ;
- [ ] miroir centré sans choc ;
- [ ] petite course stable ;
- [ ] aucune butée ;
- [ ] aucune chauffe anormale après cinq minutes.

## Mise sous tension laser

- [ ] module connu et mesuré à 1 mW maximum ;
- [ ] terminaison mate en place ;
- [ ] aucune personne dans l'axe ;
- [ ] capot fermé ;
- [ ] e-stop testé ;
- [ ] contact de capot testé ;
- [ ] laser éteint Teensy débranché ;
- [ ] laser éteint en état SAFE_OFF ;
- [ ] laser éteint entre les positions.
