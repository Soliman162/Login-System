#ifndef EXINT_CONFIG_H
#define EXINT_CONFIG_H

/**
 * Options:-
 *      ENABLE
 *      DISABLE
 */
#define INT0_STATE  ENABLE
#define INT1_STATE  DISABLE
#define INT2_STATE  DISABLE

/**
 *  Options:-
 * 
 *      -LOW_LEVEL         
 *      -ANY_LOGICAL_CHANGE
 *      -FALLING_EDGE      
 *      -RISING_EDGE       
 * 
 */
#define INT0_ACTIVATION_STATE  RISING_EDGE
#define INT1_ACTIVATION_STATE  FALLING_EDGE

/**
 *  Options:-
 * 
 *      -FALLING_EDGE      
 *      -RISING_EDGE       
 */
#define INT2_ACTIVATION_STATE   FALLING_EDGE



#endif