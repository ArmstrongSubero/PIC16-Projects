> Libraries and Projects for the 8-bit PIC16 Microcontrollers written in C and Assembly written by Armstrong Subero

# PIC16 Projects

Welcome to the **PIC16 Projects** repository! This repository contains a collection of projects, libraries, and code examples for Microchip's PIC16 series microcontrollers. These projects are intended for makers, engineers, and students who want to explore the capabilities of the PIC16 microcontrollers through hands-on experimentation.

The repository was recently revamped and updated, moving from the PIC16F1717 to the **PIC16F1718** as the primary target device, though the projects should work with both microcontrollers with minimal or no modification.

## Table of Contents
- [Introduction](#introduction)
- [Project List](#project-list)
  - [C Projects](#c-projects)
  - [Assembly Projects (Legacy MPASM)](#assembly-projects-legacy-mpasm)
- [Getting Started](#getting-started)
- [Requirements](#requirements)
- [How to Use](#how-to-use)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This repository provides example code and complete projects to help you get started with PIC16 microcontrollers. Whether you're controlling an LED, working on a sensor application, interfacing with displays, implementing machine learning on an 8-bit MCU, or creating games, this collection is designed to provide useful starting points and inspiration. It contains near everything you will need to work with 8-bit PIC microcontroller devices!

## Project List

### C Projects

| # | Project | Description |
|---|---------|-------------|
| 00 | **00_Archive** | Archived legacy projects |
| 00 | **00_Documents** | Documentation and reference materials |
| 00 | **00_PIC16F1719_Archive** | PIC16F1719-specific archived projects |
| 01 | **01_Blink.X** | Basic blinking LED program |
| 02 | **02_Pushbutton.X** | Control an LED with a pushbutton |
| 03 | **03_Timer0.X** | Timer0-based delay implementation |
| 04 | **04_Timer0_Counter.X** | Simple counter using Timer0 |
| 05 | **05_Timer0_Interrupt.X** | Timer0 interrupt demonstration |
| 06 | **06_Timer0_Ext_Interrupt.X** | Timer0 with an external interrupt |
| 07 | **07_Timer1.X** | Timer1 usage example |
| 08 | **08_Timer2.X** | Timer2 usage example |
| 09 | **09_Watchdog_Timer.X** | Watchdog timer reset demonstration |
| 10 | **10_Interrupt_OC.X** | Interrupt-On-Change (IOC) functionality |
| 11 | **11_UART.X** | UART communication between the PIC and a PC |
| 12 | **12_SPI.X** | SPI communication implementation |
| 13 | **13_I2C.X** | I2C communication implementation |
| 14 | **14_EEPROM_24AA512.X** | Interface with 24AA512 EEPROM via I2C |
| 15 | **15_OLED_SSD1306.X** | Interface with an SSD1306 OLED display |
| 16 | **16_ADC.X** | Analog-to-Digital Conversion example |
| 17 | **17_Comparator.X** | Internal comparator module usage |
| 18 | **18_FVR.X** | Fixed Voltage Reference (FVR) demonstration |
| 19 | **19_DAC.X** | Generate analog signals using the DAC |
| 20 | **20_Ramp_Waveform_Generation.X** | Generate a ramp waveform output |
| 21 | **21_Sine_Waveform_Generation.X** | Generate a sine wave output |
| 22 | **22_PWM.X** | Generate PWM signals for motor control |
| 23 | **23_NCO.X** | Numerically Controlled Oscillator (NCO) usage |
| 24 | **24_Piezo.X** | Generate sound using a piezo buzzer |
| 25 | **25_Servo.X** | Control a servo motor with PWM |
| 26 | **26_COG.X** | Complementary Output Generator (COG) usage |
| 27 | **27_CLC.X** | Configurable Logic Cell (CLC) example |
| 28 | **28_LM35_Temperature.X** | Read temperature from LM35 sensor |
| 29 | **29_MCP9700_Temperature.X** | Read temperature from MCP9700 sensor |
| 30 | **30_TCRT5000_Proximity.X** | Proximity detection with TCRT5000 sensor |
| 31 | **31_LDR_Light.X** | Light sensing with a Light Dependent Resistor |
| 32 | **32_Smart_LED.X** | Smart LED control |
| 33 | **33_HCSR04_Distance.X** | Ultrasonic distance measurement with HC-SR04 |
| 34 | **34_SD_Card_SDSC.X** | SD card interface (Standard Capacity) |
| 35 | **35_SD_Card_SDHC.X** | SD card interface (High Capacity) |
| 36 | **36_SD_Card_FAT32.X** | SD card with FAT32 filesystem |
| 37 | **37_SD_Card_FATFS.X** | SD card with FatFS library |
| 38 | **38_SD_Card_File_Folder.X** | SD card file and folder operations |
| 39 | **39_SSEG_Display.X** | Seven-segment display driver |
| 40 | **40_SSEG_Multiplexing.X** | Multiplexed seven-segment displays |
| 41 | **41_SSEG_Quad_Multiplexing.X** | Quad multiplexed seven-segment displays |
| 42 | **42_SSEG_Countdown_Timer.X** | Countdown timer on seven-segment displays |
| 43 | **43_SSEG_Countdown_Buzzer.X** | Countdown timer with buzzer alert |
| 44 | **44_DS1302_RTC.X** | Real-Time Clock using DS1302 |
| 45 | **45_DHT11_Humidity.X** | Humidity and temperature with DHT11 sensor |
| 46 | **46_Bluetooth_HC05.X** | Bluetooth communication via HC-05 module |
| 47 | **47_NRF24L01.X** | Wireless communication with NRF24L01 |
| 48 | **48_Soft_UART.X** | Software UART implementation |
| 49 | **49_GPS_Neo6M.X** | GPS data reading with Neo-6M module |
| 50 | **50_PN532_NFC.X** | NFC communication with PN532 module |
| 51 | **51_Machine_Learning.X** | Machine learning on an 8-bit PIC |
| 52 | **52_RF_Machine_Learning.X** | Random Forest machine learning implementation |
| 53 | **53_EMIC2_TTS.X** | Text-to-Speech with EMIC2 module |
| 54 | **54_NCO_AM_Transmitter.X** | AM transmitter using NCO |
| 55 | **55_CCP_AM_Transmitter.X** | AM transmitter using CCP module |
| 56 | **56_SSD1306_Low_RAM.X** | SSD1306 OLED driver (low RAM optimized) |
| 57 | **57_Space_Invaders.X** | Space Invaders game |
| 58 | **58_Tetris.X** | Tetris game |
| 59 | **59_PacMan.X** | Pac-Man game |
| 60 | **60_K_Type_Thermocouple.X** | K-Type thermocouple interface (MAX6675) |

### Assembly Projects (Legacy MPASM)

Projects using the PIC16F506 microcontroller written in MPASM assembly:

| # | Project | Description |
|---|---------|-------------|
| A01 | **A01_Led_On** | Turns an LED on |
| A02 | **A02_Blink** | Blinks an LED |
| A03 | **A03_Modules** | Demonstrates using ASM modules |
| A04 | **A04_Switch** | Demonstrates using a switch |
| A05 | **A05_Timer0** | Uses the Timer0 module |
| A06 | **A06_Counter** | Uses the counter module |
| A07 | **A07_Sleep** | Demonstrates sleep mode |
| A08 | **A08_WPUC** | Uses Weak Pull-Up Control |
| A10 | **A10_Watchdog_Timer** | Uses watchdog timer |
| A11 | **A11_Comparator** | Uses comparator module |
| A12 | **A12_Comparator_Wake** | Comparator and sleep mode |
| A13 | **A13_ADC** | Uses the internal ADC module |
| A14 | **A14_Software_PWM** | Uses the software PWM module |
| A15 | **A15_Sound** | Generates sound |

Each project has its own folder with source code, schematics, and relevant documentation.

## Getting Started

### Prerequisites

To work with the projects in this repository, you will need:

- A PIC16 microcontroller (e.g., PIC16F1718, PIC16F1717, etc.).
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

### Migration Note

This repository was updated from targeting the **PIC16F1717** to the **PIC16F1718**. The PIC16F1718 offers additional peripherals and memory while maintaining pin compatibility. Legacy PIC16F1717-specific projects can be found in the `00_PIC16F1719_Archive` folder. Most projects should compile and run on either device without modification.

## Requirements

- **Hardware**: PIC16F1718 (or PIC16F1717) microcontroller, breadboard, resistors, capacitors, LEDs, sensors, etc.
- **Software**: MPLAB X IDE, XC8 Compiler.
- **Programmer**: PICkit 3/4 or any compatible programmer.

## How to Use

- Each project contains a `.X` MPLAB project folder that can be opened directly in MPLAB X IDE.
- Review the README file in each project folder for specific setup instructions.
- Build the project in MPLAB X IDE and program it onto your PIC16 microcontroller.

### Example: Running the Blink Project

1. Connect an LED with a resistor to the GPIO pin specified in the code (e.g., PIN D1).
2. Open the `01_Blink.X` project in MPLAB X.
3. Build the project and program it onto your PIC16F1718.
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
- **Email**: [armstrongsubero@gmail.com](mailto:armstrongsubero@gmail.com)

If you find this repository helpful, please give it a star ⭐ and share it with others who might be interested in PIC16 microcontroller projects!










