#include "std_types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"

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
void Buzzer_voidTOG(void)
{
	SetPin_enumValue(BUZZER_PORT,BUZZER_PIN,DIO_HIGH);
	Timer1_voidDelay_Micro_Seconds_Sync(1000000);
	SetPin_enumValue(BUZZER_PORT,BUZZER_PIN,DIO_LOW);
	Timer1_voidDelay_Micro_Seconds_Sync(1000000);
}
