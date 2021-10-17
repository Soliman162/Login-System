/*
 * PHpad_program.c
 *
 *  Created on: Oct 2, 2021
 *      Author: DELL
 */

#include "..\..\LIB\std_types.h"
#include "..\..\LIB\BIT_MATH.h"
#include  <util/delay.h>

#include "..\..\MCAL\01-DIO\DIO_interface.h"

#include "../07-Phone_Keypad/PHpad_config.h"
#include "../07-Phone_Keypad/PHpad_interface.h"

void Phonepad_void_Init(void){

	SetPin_enumDirection ( PHONE_PAD_INIT_PORT, PHONE_PAD_ROW_0 , DIO_INPUT );
	SetPin_enumDirection ( PHONE_PAD_INIT_PORT, PHONE_PAD_ROW_1 , DIO_INPUT );
	SetPin_enumDirection ( PHONE_PAD_INIT_PORT, PHONE_PAD_ROW_2 , DIO_INPUT );
	SetPin_enumDirection ( PHONE_PAD_INIT_PORT, PHONE_PAD_ROW_3 , DIO_INPUT );

	SetPin_enumValue(PHONE_PAD_INIT_PORT, PHONE_PAD_ROW_0 , DIO_HIGH);
	SetPin_enumValue(PHONE_PAD_INIT_PORT, PHONE_PAD_ROW_1 , DIO_HIGH);
	SetPin_enumValue(PHONE_PAD_INIT_PORT, PHONE_PAD_ROW_2 , DIO_HIGH);
	SetPin_enumValue(PHONE_PAD_INIT_PORT, PHONE_PAD_ROW_3 , DIO_HIGH);


	SetPin_enumDirection ( PHONE_PAD_INIT_PORT, PHONE_PAD_COL_0 , DIO_OUTPUT);
	SetPin_enumDirection ( PHONE_PAD_INIT_PORT, PHONE_PAD_COL_1 , DIO_OUTPUT);
	SetPin_enumDirection ( PHONE_PAD_INIT_PORT, PHONE_PAD_COL_2 , DIO_OUTPUT);

	SetPin_enumValue(PHONE_PAD_INIT_PORT,  PHONE_PAD_COL_0 , DIO_HIGH);
	SetPin_enumValue(PHONE_PAD_INIT_PORT,  PHONE_PAD_COL_1 , DIO_HIGH);
	SetPin_enumValue(PHONE_PAD_INIT_PORT,  PHONE_PAD_COL_2 , DIO_HIGH);


}
u8 Phonepad_u8Get_Number(void){

	u8 LOC_u8COLItrator = 0;
	u8 LOC_u8ROWIterator = 0;
	u8 LOC_u8Get_Pressed = 1 ;
	u8 LOC_u8Return_Value = 0;



	for( LOC_u8COLItrator=PHONE_PAD_COL_START; LOC_u8COLItrator<=PHONE_PAD_COL_END; LOC_u8COLItrator++ ){

		SetPin_enumValue(PHONE_PAD_INIT_PORT,LOC_u8COLItrator,DIO_LOW);

		for( LOC_u8ROWIterator=PHONE_PAD_ROW_START; LOC_u8ROWIterator<=PHONE_PAD_ROW_END; LOC_u8ROWIterator++ ){

			GetPin_enumValue(PHONE_PAD_INIT_PORT,LOC_u8ROWIterator,&LOC_u8Get_Pressed);
			if(LOC_u8Get_Pressed == 0){

				_delay_ms(50);
				GetPin_enumValue(PHONE_PAD_INIT_PORT,LOC_u8ROWIterator,&LOC_u8Get_Pressed);

				if(LOC_u8Get_Pressed == 0){

					LOC_u8Return_Value = LOC_PHONE_PAD[LOC_u8ROWIterator-PHONE_PAD_ROW_START][LOC_u8COLItrator-PHONE_PAD_COL_START];

				}
				while(LOC_u8Get_Pressed==0){
					GetPin_enumValue(PHONE_PAD_INIT_PORT,LOC_u8ROWIterator,&LOC_u8Get_Pressed);
				}
				break;
			}

		}

		SetPin_enumValue(PHONE_PAD_INIT_PORT,LOC_u8COLItrator,DIO_HIGH);


	}

	return LOC_u8Return_Value;


}
