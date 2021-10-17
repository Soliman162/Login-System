/*
 * BUZZER_program.c
 *
 *  Created on: Oct 5, 2021
 *      Author: DELL
 */

#include "..\..\LIB\std_types.h"
#include "..\..\LIB\BIT_MATH.h"
#include  <util/delay.h>

#include "..\..\MCAL\01-DIO\DIO_interface.h"

#include "BUZZER_interface.h"
#include "BUZZER_config.h"


void Buzzer_voidInit(void){

	SetPin_enumDirection(BUZZER_PORT,BUZZER_PIN,DIO_OUTPUT);
	SetPin_enumValue(BUZZER_PORT,BUZZER_PIN,DIO_LOW);
}
void Buzzer_voidON(void){

	SetPin_enumValue(BUZZER_PORT,BUZZER_PIN,DIO_HIGH);

}
void Buzzer_voidOFF(void){

	SetPin_enumValue(BUZZER_PORT,BUZZER_PIN,DIO_LOW);

}
void Buzzer_voidTOG(void){

	SetPin_enumValue(BUZZER_PORT,BUZZER_PIN,DIO_HIGH);
	_delay_ms(1000);
	SetPin_enumValue(BUZZER_PORT,BUZZER_PIN,DIO_LOW);
	_delay_ms(1000);

}
