# teensyNASA
This repo contains the code for two teensy 4.0 boards (or any arduino) to communicate over I2C. The capabilities include sending data to control a stepper motor and/or falcon 500 motor and recieve the confirmation the data was processed. It's purpose is to provide a solid start for our NASA RMC rover's internal communication.

## Hardware and Software Used

- 2 Teensy 4.0
- breadboard
- stepper motor
- G251X Digital Step Drive
- Falcon 500
- 120V AC to 12V DC converter
- Arduino IDE

##Libraries
- [Wire (I2C)](https://www.arduino.cc/en/reference/wire)
- [Speedy Stepper](https://github.com/Stan-Reifel/SpeedyStepper)
- [Servo](https://github.com/arduino-libraries/Servo)

## Authors
Nikita Lukhanin - [nikilukhan](https://github.com/nikilukhan)

