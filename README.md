# Login-System
using AVR-Atmega32, LCD, Buzzer, LED and Phone Keypad

1.The system will wait until someone press any button on the keypad to start the system.

2.Then give the user 3 tries to enter the password.

	- If the password is correct the LCD will display Welcome for 1 second and turn the led on then the system will stop.

	- If the password is wrong the LCD will display > wrong password and > Try again.
	
	- If the password is wrong after 3 tries the LCD will dispaly "wrong password" and "No more tries" and the Buzzer will be turned on for 2 seconds then the system will stop.


# The hardware that has been used is:  
1. AVR-Atmega32
2. Keypad
3. Buzzer
4. LED Display
5. LCD Display

# Architecture Layer Applied:

- APP Folder has the Main Application --> `main.c`
  
- HAL Folder has : 
1.LED Display Driver
2.Keypad Driver
3.Buzzer Driver
4.LED Display Driver
5.LCD Display Driver
       
- MCAL Folder has DIO Driver (which is needed because HAL Layer Connecting to MCAL Layer).
- LIB Folder has .h Files has useful Macros to make the code easier and more readable.
