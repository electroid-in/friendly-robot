# friendly-robot
Project Description: Interactive Robot with OLED Display and Servo Motor Control

This project involves an interactive robot that uses an Arduino microcontroller, an OLED display, and multiple servo motors to exhibit various behaviors and responses based on button inputsThe robot features eye animations on the OLED display and can perform different servo movements corresponding to different modes. The goal is to create an engaging and responsive robot with a combination of visual and mechanical actions.

Components
Arduino: The main microcontroller that controls all operations.
Adafruit SSD1306 OLED Display: Displays eye animations.
Servo Motors: Three servo motors connected to pins 5, 6, and 11.
Push Buttons: Multiple buttons connected to various pins for triggering different modes and actions.

Features

Eye Animations:
The OLED display shows eye animations that change based on different modes and button inputs.
The eyes move and blink, providing a lively visual effect.

Servo Motor Control:
Servo on Pin 11: This servo performs random movements between 15 and 20 degrees every 2 minutes and triggers a random mode change.
Servo on Pin 5 and Pin 6: These servos perform coordinated movements in specific modes.

Button Inputs:
Button on Pin 3: Moves the servo on pin 11 to the left and back to the center.
Button on Pin 4: Activates Mode 3, where servos on pins 5 and 6 move to and fro 15 degrees, then revert to Mode 1 after 5 seconds.
Button on Pin 7: Activates Mode 2, where the servo on pin 5 moves to a specific angle and then returns to its original position, reverting to Mode 1 after 5 seconds.
Button on Pin 9: Moves the servo on pin 11 to the right and back to the center.
Button on Pin 10: Moves the servo on pin 11 to the left and back to the center.
Buttons on Pins 8 and 11: Used for changing the mood and controlling the eye animations on the OLED display.

Modes
Default Mode (Mode 1): The default state where the eyes animate normally and servos are in their initial positions.
Mode 2 (Triggered by Button 7): The servo on pin 5 moves to a specific angle, then moves to and fro by 15 degrees before returning to its original position.
Mode 3 (Triggered by Button 4): The servos on pins 5 and 6 move to and fro by 15 degrees and then revert to their original positions after 5 seconds.
Mode 4 (Random Mode Change): The servo on pin 11 moves randomly between 15 and 20 degrees, and the mode changes to either Mode 2 or Mode 3 every 2 minutes.

Code Overview
Setup Function: Initializes the OLED display, sets pin modes for buttons and servos, and sets the initial positions of the servos.
Loop Function: Continuously checks for button presses and performs actions based on the inputs. It includes logic for random servo movements and mode changes.
Eye Animations: Uses predefined bitmaps to display different eye expressions and animations on the OLED display.
Servo Movements: Controls the positions of the servos based on button inputs and mode changes.

Usage
Power the Arduino and connect it to the OLED display and servos as per the pin configuration.
Press the buttons to trigger different modes and observe the eye animations and servo movements.
Monitor the behavior of the servo on pin 11, which will randomly move and change modes every 2 minutes.

Applications
This project can be used for educational purposes to demonstrate how to integrate multiple sensors and actuators with an Arduino.
It can serve as a foundation for creating more advanced interactive robots with additional features like voice recognition or autonomous behavior.
The project is also a fun way to learn about programming, electronics, and robotics.
