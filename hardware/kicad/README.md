# Schéma KiCad de câblage

`RDV4_wiring.sch` est un schéma **KiCad legacy Eeschema v4** volontairement utilisé pour rester lisible et importable sans bibliothèque de symboles embarquée.

## Ouvrir avec KiCad 6, 7, 8 ou 9

1. Ouvrir KiCad.
2. `Fichier > Ouvrir un schéma existant`.
3. Sélectionner `RDV4_wiring.sch`.
4. Accepter la conversion.
5. Enregistrer : KiCad créera un fichier moderne `.kicad_sch`.

Le schéma est un **wiring diagram par modules**, pas un PCB.

## Point important : axe Y

Le MCP4822 utilise ses deux sorties :

- canal A : balayage X ;
- canal B : consigne neutre Y.

Le module analogique doit donc avoir deux canaux, ou il faut deux modules identiques. Le firmware initialise le canal B à la valeur centrale.

## À confirmer avant branchement

- brochage réel du module MCP4822 acheté ;
- tension et polarité du module de conversion bipolaire ;
- entrée simple ou différentielle des drivers galvo ;
- tension d'alimentation du module OPT101 ;
- compatibilité TTL 3,3 V du laser.

Ne relier ni `X-` ni `Y-` à la masse sans documentation du driver.
