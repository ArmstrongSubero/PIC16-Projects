> Libraries and Projects for the 8-bit PIC16 Microcontrollers written in C and Assembly

# PIC16 Projects

Welcome to the **PIC16 Projects** repository! This repository contains a collection of projects and code examples for Microchip's PIC16 series microcontrollers. These projects are intended for makers, engineers, and students who want to explore the capabilities of the PIC16 microcontrollers through hands-on experimentation.

## Table of Contents
- [Introduction](#introduction)
- [Project List](#project-list)
- [Getting Started](#getting-started)
- [Requirements](#requirements)
- [How to Use](#how-to-use)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This repository provides example code and complete projects to help you get started with PIC16 microcontrollers. Whether you're controlling an LED, working on a sensor application, or creating something more complex, this collection is designed to provide useful starting points and inspiration. It contains near everything you will need to work with 8-bit PIC microcontroller devices!

## Project List

Below is a list of projects included in this repository:

1. **01_Blink.X**: A basic blinking LED program for PIC16.
2. **02_Pushbutton.X**: Control an LED with a pushbutton.
3. **03_Timer0.X**: Timer0-based delay implementation.
4. **04_Counter.X**: Simple counter using Timer0.
5. **05_Timer0_Interrupts.X**: Timer0 interrupt demonstration.
6. **06_TMR0_Ext_Interrupt.X**: Use Timer0 with an external interrupt.
7. **07_Sleep.X**: Demonstrate sleep mode to save power.
8. **08_Watchdog_Timer.X**: Use the watchdog timer to reset the microcontroller.
9. **09_IOC.X**: Demonstrate Interrupt-On-Change (IOC) functionality.
10. **10_Comparator.X**: Use the internal comparator module.
11. **11_FVR.X**: Fixed Voltage Reference (FVR) demonstration.
12. **12_DAC.X**: Generate analog signals using the DAC.
13. **13_Timer1.X**: Timer1 usage example.
14. **14_Timer2.X**: Timer2 usage example.
15. **15_PWM.X**: Generate PWM signals for motor control.
16. **16_NCO.X**: Use the Numerically Controlled Oscillator (NCO).
17. **17_Sound.X**: Generate sound using a buzzer.
18. **18_UART.X**: UART communication between the PIC and a PC.
19. **19_I2C.X**: Implement I2C communication.
20. **20_SPI.X**: Implement SPI communication.
21. **21_ADC.X**: Analog-to-Digital Conversion example.
22. **22_Internal_Temp_Indicator.X**: Read internal temperature sensor.
23. **23_COG.X**: Complementary Output Generator (COG) usage.
24. **24_CLC.X**: Configurable Logic Cell (CLC) example.
25. **25_Servo.X**: Control a servo motor with PWM.
26. **26_Servo_Std.X**: Standard servo control demonstration.
27. **27_Software_UART.X**: Software UART implementation.
28. **28_Seven_Segment.X**: Drive a seven-segment display.
29. **29_Seven_Segment_Mul.X**: Multiplex multiple seven-segment displays.
30. **30_Countdown_Timer.X**: Create a countdown timer.
31. **31_Motor_On_Off.X**: Simple DC motor on/off control.
32. **32_Motor_PWM.X**: Control motor speed using PWM.
33. **33_Motor_BTS7960.X**: Control motor with BTS7960 driver.
34. **34_Motor_Encoder.X**: Read encoder feedback for motor control.
35. **35_Motor_PID_Control.X**: Implement PID control for a motor.
36. **36_Photoresistor.X**: Read values from a photoresistor.
37. **37_Analog_Joystick.X**: Interface with an analog joystick.
38. **38_Sine_Wave_Generation.X**: Generate a sine wave output.
39. **39_Square_Wave_Generation.X**: Generate a square wave output.
40. **40_Triangle_Wave_Generation.X**: Generate a triangle wave output.
41. **41_Knight_Rider.X**: LED pattern resembling the Knight Rider effect.
42. **42_CLC.X**: Another example of using the Configurable Logic Cell.
43. **43_SSD1306.X**: Interface with an SSD1306 OLED display.
44. **44_Nokia_5110.X**: Interface with a Nokia 5110 LCD.
45. **45_ESP8266.X**: Communicate with an ESP8266 Wi-Fi module.
46. **46_UBLOX_GSM.X**: Interface with a UBLOX GSM module.
47. **47_GPS.X**: Read data from a GPS module.
48. **48_Touch_Display.X**: Interface with a touch display.
49. **49_Bluetooth.X**: Communicate via Bluetooth module.
50. **50_Temperature_Controlled_Fan.X**: Control a fan based on temperature readings.
51. **51_UART_To_Browser_Bridge.X**: Bridge UART data to a web browser.
52. **52_Inductance_Meter**: A PIC16F Based Inductance Meter

### (LEGACY MPASM) Assembly Libraries and Projects using PIC16F506 Microcontroller

- A01_Led_On                : 	Turns an LED on
- A02_Blink                 : 	Blinks an LED
- A03_Modules               : 	Demonstrates using ASM modules
- A04_Switch                : 	Demonstrates using a switch
- A05_Timer0				: 	Uses the Timer0 module
- A06_Counter				: 	Uses the counter module
- A07_Sleep					: 	Demonstrates sleep mode
- A08_WPUC                  : 	Uses WPUC
- A10_Watchdog_Timer        : 	Uses watchdog timer
- A11_Comparator            : 	Uses comparator module
- A12_Comparator Wake       : 	Comparator and sleep mode
- A13_ADC                   : 	Uses the internal ADC module
- A14_Software_PWM          : 	Uses the software PWM module
- A15_Sound                 : 	Generates sound

Each project has its own folder with source code, schematics, and relevant documentation.


## Getting Started

### Prerequisites
To work with the projects in this repository, you will need:

- A PIC16 microcontroller (e.g., PIC16F1717, PIC16F877A, etc.).
- MPLAB X IDE: [Download here](https://www.microchip.com/mplab/mplab-x-ide).
- XC8 Compiler: [Download here](https://www.microchip.com/mplab/compilers).
- PICkit Programmer (or equivalent) to upload the code to your microcontroller.

### Setting Up
1. Clone the repository to your local machine:
    ```sh
    git clone https://github.com/ArmstrongSubero/PIC16-Projects.git
    cd PIC16-Projects
    ```

2. Open MPLAB X IDE and import the project you want to work on.
3. Compile and program the microcontroller using your PICkit or other compatible programmer.

## Requirements

- **Hardware**: PIC16 microcontroller, breadboard, resistors, capacitors, LEDs, sensors, etc.
- **Software**: MPLAB X IDE, XC8 Compiler.
- **Programmer**: PICkit 3/4 or any compatible programmer.

## How to Use

- Each project contains a `.X` MPLAB project folder that can be opened directly in MPLAB X IDE.
- Review the README file in each project folder for specific setup instructions.
- Build the project in MPLAB X IDE and program it onto your PIC16 microcontroller.

### Example: Running the Blink Project
1. Connect an LED with a resistor to the GPIO pin specified in the code (e.g., PIN D1).
2. Open the `01_Blink` project in MPLAB X.
3. Build the project and program it onto your PIC16F1717.
4. Observe the LED blinking on the breadboard.

## Contributing

Contributions are welcome! If you have a new project, improvements, or bug fixes:
1. Fork this repository.
2. Create a new branch (`git checkout -b feature-branch-name`).
3. Commit your changes (`git commit -m 'Add new project or feature'`).
4. Push to the branch (`git push origin feature-branch-name`).
5. Create a pull request for review.

Feel free to suggest new projects or improvements to existing ones!

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.


## Contact

For any questions or discussions related to PIC16 Projects:
- **GitHub**: [ArmstrongSubero](https://github.com/ArmstrongSubero)
- **Email**: [armstrong.subero@example.com](mailto:armstrong.subero@gmail.com)

If you find this repository helpful, please give it a star ⭐ and share it with others who might be interested in PIC16 microcontroller projects!










