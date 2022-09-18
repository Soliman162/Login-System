#include "std_types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"

#include "KeyPad_interface.h"
#include "KeyPad_config.h"

void KEY_PAD_voidINIT(void)
{
	Timer1_voidInit();

	SetPin_enumDirection ( KEY_PAD_INIT_PORT, KEY_PAD_ROW_0 , DIO_INPUT );
	SetPin_enumDirection ( KEY_PAD_INIT_PORT, KEY_PAD_ROW_1 , DIO_INPUT );
	SetPin_enumDirection ( KEY_PAD_INIT_PORT, KEY_PAD_ROW_2 , DIO_INPUT );
	SetPin_enumDirection ( KEY_PAD_INIT_PORT, KEY_PAD_ROW_3 , DIO_INPUT );

	SetPin_enumValue(KEY_PAD_INIT_PORT, KEY_PAD_ROW_0 , DIO_HIGH);
	SetPin_enumValue(KEY_PAD_INIT_PORT, KEY_PAD_ROW_1 , DIO_HIGH);
	SetPin_enumValue(KEY_PAD_INIT_PORT, KEY_PAD_ROW_2 , DIO_HIGH);
	SetPin_enumValue(KEY_PAD_INIT_PORT, KEY_PAD_ROW_3 , DIO_HIGH);


	SetPin_enumDirection ( KEY_PAD_INIT_PORT, KEY_PAD_COL_0 , DIO_OUTPUT);
	SetPin_enumDirection ( KEY_PAD_INIT_PORT, KEY_PAD_COL_1 , DIO_OUTPUT);
	SetPin_enumDirection ( KEY_PAD_INIT_PORT, KEY_PAD_COL_2 , DIO_OUTPUT);

	SetPin_enumValue(KEY_PAD_INIT_PORT,  KEY_PAD_COL_0 , DIO_HIGH);
	SetPin_enumValue(KEY_PAD_INIT_PORT,  KEY_PAD_COL_1 , DIO_HIGH);
	SetPin_enumValue(KEY_PAD_INIT_PORT,  KEY_PAD_COL_2 , DIO_HIGH);
}

u8 KEY_PAD_ptru8GET_PRESSED_VALUE(void){

	u8 LOC_u8COLItrator = 0;
	u8 LOC_u8ROWIterator = 0;
	u8 LOC_u8Get_Pressed = 1 ;
	u8 LOC_u8Return_Value = 0;

	for( LOC_u8COLItrator=KEY_PAD_COL_START; LOC_u8COLItrator<=KEY_PAD_COL_END; LOC_u8COLItrator++ ){

		SetPin_enumValue(KEY_PAD_INIT_PORT,LOC_u8COLItrator,DIO_LOW);

		for( LOC_u8ROWIterator=KEY_PAD_ROW_START; LOC_u8ROWIterator<=KEY_PAD_ROW_END; LOC_u8ROWIterator++ ){

			GetPin_enumValue(KEY_PAD_INIT_PORT,LOC_u8ROWIterator,&LOC_u8Get_Pressed);
			if(LOC_u8Get_Pressed == 0){

				Timer1_voidDelay_Micro_Seconds(50000);
				GetPin_enumValue(KEY_PAD_INIT_PORT,LOC_u8ROWIterator,&LOC_u8Get_Pressed);

				if(LOC_u8Get_Pressed == 0){

					LOC_u8Return_Value = Key_pad[LOC_u8ROWIterator-KEY_PAD_ROW_START][LOC_u8COLItrator-KEY_PAD_COL_START];

				}
				while(LOC_u8Get_Pressed==0){
					GetPin_enumValue(KEY_PAD_INIT_PORT,LOC_u8ROWIterator,&LOC_u8Get_Pressed);
				}
				break;
			}
		}
		SetPin_enumValue(KEY_PAD_INIT_PORT,LOC_u8COLItrator,DIO_HIGH);
	}
	return LOC_u8Return_Value;
}
