System Design: Smart Classroom Comfort Monitor

## 1. Hardware
* **Microcontroller:** Raspberry Pi 4b
* **Indicator:** Red LED
* **Safety Component:** 1k Ohm Resistor
* **Wiring Path:** 
  * Signal originates from **GPIO 17** (inside column, pin 11) to the breadboard.
  * Connects to the LED anode (longer leg).
  * Current passes through the LED to the cathode (shorter leg).
  * Passes through the 1k Ohm resistor to limit current.
  * Returns to the Raspberry Pi Ground pin (outside column, pin 6) to close the circuit.

## 2. Software
* **Language & Library:** C & the `pigpio` library for hardware interfacing.
* **Control Flow:** A `while (1)` loop acts as the primary controller, and gives user a Command Line Interface (CLI) menu that waits for user input.
* **Data Structures:** 
  * A `double` array stores all active session temperatures in memory.
  * A counter variable tracks the total number of readings for average calculation.
* **File I/O Management:**
  * `status.txt`: Opened in write mode (`"w"`) to constantly overwrite and reflect the most current state (`# NORMAL` or `# WARNING`).
  * `temperature_log.csv`: Opened in append mode (`"a"`) to preserve the history of past records.
