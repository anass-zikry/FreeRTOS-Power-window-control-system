# FreeRTOS Power Window Control System

## Overview
This project involves the design and implementation of an advanced **Power Window Control System** using a Tiva C microcontroller integrated with **FreeRTOS**. The system is specifically designed to manage the front passenger door window, offering user-friendly control interfaces accessible from both the passenger and driver positions. This project was developed as part of the **CSE411 Real Time and Embedded Systems** course at the Faculty of Engineering, Ain Shams University.

### Key Features
- **Manual Open/Close**: Allows the user to manually adjust the window position.
- **One-Touch Auto Open/Close**: Fully opens or closes the window with a single press of a button.
- **Window Lock**: Prevents unauthorized operation of the window controls.
- **Jam Protection**: Automatically stops the window operation if an obstruction is detected.

### Hardware Components
- **Tiva C Microcontroller**: Acts as the central control unit.
- **FreeRTOS**: Ensures efficient task scheduling and system responsiveness.
- **DC Motor**: Powers the window's movement.
- **Top and Bottom Limit Switches**: Detects the window's fully open and fully closed positions.
- **Push Buttons**: Serves as user input for various controls.
- **ON/OFF Switch**: Enables or disables the window control system.

## System Architecture
The system employs a modular architecture with the following components:
- **Control Logic**: Implements the operational features.
- **Input Handling**: Processes input from buttons and switches.
- **Safety Mechanisms**: Monitors for jams and enforces window lock features.

### Integration
- The microcontroller runs tasks on **FreeRTOS** to manage input handling, motor control, and safety mechanisms concurrently.
- Hardware components are integrated via GPIO pins for switches and buttons, and PWM for motor control.

## Usage
1. **Enable the System**: Use the ON/OFF switch to activate window controls.
2. **Operate the Window**: Use the push buttons for manual or one-touch operations.
3. **Enable Window Lock**: Activate the lock feature to restrict window operation.
4. **Jam Protection**: The system automatically stops the motor if an obstruction is detected.

## Links
- [**Project Video Demonstration**](https://drive.google.com/file/d/1Y8SeqV5EteSBCAezK8ta4yPvy_dZDSqJ/view?usp=sharing)
- [**Project Report**](https://drive.google.com/file/d/1YPZejfO_vy2oFck-zmoMBJg4OObD0Eax/view?usp=sharing)

