#ifndef STEPPER_CONFIG_H
#define STEPPER_CONFIG_H

/**
 * @brief 
 * stepper motor connected to which port
 * 
 * PORTA
 * PORTB
 * PORTC
 */
#define STEPPER_MOTOR_PORT  PORTA

/**
 * @brief 
 * FROM 0 --> 15
 * 4 pins of the motor
 */
#define COIL_PIN_1      PIN0
#define COIL_PIN_2      PIN1
#define COIL_PIN_3      PIN2
#define COIL_PIN_4      PIN3

/**
 * @brief 
 * max delay between 2 step in (ms)
 */
#define MAX_DELAY   2

/**
 * @brief 
 * rotate degree for each step
 */
#define DEGREE_PER_STEP     0.09F     

#endif