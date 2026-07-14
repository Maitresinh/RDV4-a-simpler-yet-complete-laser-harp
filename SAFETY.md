# Sécurité laser et électrique

Ce projet est un prototype basse puissance, pas un appareil scénique certifié.

## Pendant le développement

- utiliser une LED rouge pour les premiers tests de détection ;
- utiliser ensuite un laser visible mesuré à 1 mW maximum ;
- ne jamais utiliser un module dont la puissance réelle est inconnue ;
- ne jamais regarder dans l'ouverture, même lorsque le faisceau semble éteint ;
- enlever montres, bijoux, outils chromés et surfaces réfléchissantes de la zone ;
- terminer les faisceaux sur une surface mate et non inflammable ;
- garder l'arrêt d'urgence à portée de main.

## Sécurité matérielle obligatoire

- arrêt d'urgence à contact normalement fermé ;
- microcontact de capot normalement fermé ;
- les deux contacts coupent physiquement le 5 V du laser ;
- rappel de 10 kΩ qui force le TTL à OFF ;
- broche de surveillance protégée par un diviseur résistif ;
- capot sur alimentations et drivers ;
- aucune borne secteur accessible ;
- mise à la terre des éléments métalliques lorsque l'alimentation l'exige.

Le firmware éteint le laser entre les positions, mais le logiciel n'est jamais la seule sécurité.

## Orientation

- faisceaux dirigés vers le haut ;
- aucun faisceau horizontal à hauteur d'œil ;
- aucun miroir libre dans la pièce ;
- aucune fenêtre ou plaque de verre au-dessus de l'instrument ;
- terminaison mate au plafond ou sur un portique dédié.

## Visibilité et brouillard

Un laser faible puissance balayé sur douze positions peut être peu visible sans haze. Ne compenser pas automatiquement par une diode plus puissante. Réduire l'éclairage ambiant, utiliser une brume scénique légère adaptée et limiter l'angle de balayage.

## Utilisation devant du public

Ne pas utiliser ce prototype devant du public sans évaluation des risques, conformité locale, mesures de puissance et dispositifs appropriés. La présence d'un bouton rouge et d'un README ne transforme pas un prototype en équipement certifié.
