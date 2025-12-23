

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

## STM32F401RE Nucleo – Pin Configuration

The table below shows the pin configuration used for the STM32F401RE Nucleo board.

| Notation | Configuration  | Remarks |
|---------|---------------|---------|
| U | GPIO_output | High-side switch control pin |
| V | GPIO_output | High-side switch control pin |
| W | GPIO_output | High-side switch control pin |
| ENu | GPIO_output | Used to disable/enable inverter leg U |
| ENv | GPIO_output | Used to disable/enable inverter leg V |
| ENw | GPIO_output | Used to disable/enable inverter leg W |
| ha | GPIO_input | Receives Hall sensor A signal |
| hb | GPIO_input | Receives Hall sensor B signal |
| hc | GPIO_input | Receives Hall sensor C signal |

**Notes:**
- EN pins pull the corresponding phase to **high impedance** when driven low.
- U, V, and W pins may be configured for **PWM output** if required.
- Hall sensor inputs are used for **rotor position detection**.


## Running Logic in Simple Terms

Forward:
6 → 4 → 5 → 1 → 3 → 2

1 → 001 101 → 3 <br>
2 → 010 011 → 6 <br>
3 → 010 110 → 2 <br>
4 → 100 110 → 5 <br>
5 → 001 011 → 1 <br>
6 → 100 101 → 4 <br>

Reverse:
2 → 3 → 1 → 5 → 4 → 6

1 → 100 110 → 5 <br>
2 → 001 101 → 3 <br>
3 → 001 011 → 1 <br>
4 → 010 011 → 6 <br>
5 → 100 101 → 4 <br>
6 → 010 110 → 2 <br>


