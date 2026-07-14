# Calibration

## 1. Course du galvo

Commencer avec `DAC_MIN` et `DAC_MAX` très proches du centre. Élargir par pas de 25 unités. Le bon réglage est le plus petit éventail permettant de distinguer les douze cordes.

## 2. Stabilisation

Réduire `GALVO_SETTLE_US` jusqu'à apparition de déclenchements voisins ou de positions instables, puis remonter de 15 à 25 µs.

## 3. OPT101

Pour chaque corde, relever :

- signal sans main ;
- signal avec main claire ;
- signal avec manche sombre ;
- signal sous éclairage normal.

Définir `PER_BEAM_ON_DELTA` au-dessus du bruit maximal et `PER_BEAM_OFF_DELTA` à environ 55 à 70 % du seuil ON.

## 4. Octaves

Les frontières par défaut sont 280, 520 et 780 mm. Monter ou baisser la main dans la colonne d'octave et adapter les valeurs à la hauteur réelle de l'instrument.

Une hystérésis de 35 mm empêche les oscillations. L'octave est capturée au Note On et reste inchangée jusqu'au Note Off.

## 5. Validation

- 100 attaques simples ;
- 100 attaques rapides ;
- accords de deux puis trois notes ;
- passage entre les quatre octaves ;
- vérification de tous les Note Off ;
- fonctionnement continu de 30 minutes.

## 6. Latence

Valeurs initiales :

- stabilisation galvo : 90 µs ;
- montée laser : 10 µs ;
- maintien visuel : 22 µs ;
- 2 mesures ADC ambiantes et 2 éclairées ;
- confirmation d'attaque : 1 balayage ;
- confirmation de relâchement : 2 balayages.

Le budget théorique est d'environ 1,7 ms par balayage. La valeur réelle dépend du galvo, de l'angle, du photodétecteur et du synthétiseur.
