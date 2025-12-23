

# BLDC Motor – Six Step Commutation

The BLDC motor is commutated using **six-step commutation**.
To achieve proper rotation, it is essential to know:

* The **rotor position**, obtained from Hall sensors
* The **sequence of phase excitation** required to produce electromagnetic torque

The motor considered here rotates in the **clockwise (CW) direction** using the Hall sensor and phase excitation relationship shown below.

## Hall Sensor to Phase Excitation Mapping (CW Rotation)

| Hall A | Hall B | Hall C | Decimal | Phase U | Phase V | Phase W |
| -----: | -----: | -----: | ------: | :-----: | :-----: | :-----: |
|      0 |      0 |      1 |       1 |    Z    |    −    |    +    |
|      1 |      0 |      1 |       5 |    +    |    −    |    Z    |
|      1 |      0 |      0 |       4 |    +    |    Z    |    −    |
|      1 |      1 |      0 |       6 |    Z    |    +    |    −    |
|      0 |      1 |      0 |       2 |    −    |    +    |    Z    |
|      0 |      1 |      1 |       3 |    −    |    Z    |    +    |

## Legend

* **+** : High-side switch ON (phase sourcing current, typically PWM controlled)
* **−** : Low-side switch ON (phase sinking current)
* **Z** : Phase floating (high-impedance state)

Each Hall sensor combination corresponds to a **60° electrical sector** of rotor position.
Applying the correct phase excitation for each sector produces continuous torque, resulting in smooth clockwise rotation of the BLDC motor.

<img width="50%" height="auto" alt="image" src="https://github.com/user-attachments/assets/ef4d9635-c2f5-46ab-8abc-1ec78887dc37" />

## Running Logic in Simple Terms

Forward:
6 → 4 → 5 → 1 → 3 → 2

1 → 001 101 → 3 <br />
2 → 010 011 → 6
3 → 010 110 → 2
4 → 100 110 → 5
5 → 001 011 → 1
6 → 100 101 → 4

Reverse:
2 → 3 → 1 → 5 → 4 → 6

1 → 100 110 → 5
2 → 001 101 → 3
3 → 001 011 → 1
4 → 010 011 → 6
5 → 100 101 → 4
6 → 010 110 → 2


