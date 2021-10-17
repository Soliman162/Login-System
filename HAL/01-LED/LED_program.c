#include "..\..\LIB\std_types.h"
#include "..\..\LIB\BIT_MATH.h"

#include "..\..\MCAL\01-DIO\DIO_interface.h"

#include "LED_interface.h"

void LED_voidinit (LED_Config New_Led){

	SetPin_enumDirection ( New_Led.port ,New_Led.pin , DIO_OUTPUT);

}
void LED_voidOn   (LED_Config New_Led){

	if(New_Led.active_state==ACTIVE_HIGH){

		SetPin_enumValue     (New_Led.port ,New_Led.pin , DIO_HIGH);

	}else if(New_Led.active_state==ACTIVE_LOW){

		SetPin_enumValue     (New_Led.port ,New_Led.pin , DIO_LOW);

	}
}
void LED_voidOff  (LED_Config New_Led){

	if(New_Led.active_state==ACTIVE_LOW){

			SetPin_enumValue     (New_Led.port ,New_Led.pin , DIO_HIGH);

		}else if(New_Led.active_state==ACTIVE_HIGH){

			SetPin_enumValue     (New_Led.port ,New_Led.pin , DIO_LOW);

		}


}
