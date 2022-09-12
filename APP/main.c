#include "std_types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"

#include "LED_interface.h"
#include "CLCD_interface.h"
#include "KeyPad_interface.h"
#include "BUZZER_interface.h"

#define 		PASS_WORD_CHAR_NUM 						4
#define 		NOT_PRESSED								0
#define  		MAXIMUM_NUMBER_FOR_TRY					3

int main (void){

	u8  LOC_u8Flag = 0;
	u8  LOC_u8Iterator = 0;
	u8  LOC_u8Number_OF_CHAR = 0;
	u8  LOC_ptru8PassWord [4]="1234" ;
    u8  LOC_ptru8Pass_word_Check[4]  = "" ;
	u8  LOC_u8Pressed_Button =NOT_PRESSED ;
	LED_Config		LOC_strEnterance_LED = {PORTD ,PIN5 ,ACTIVE_HIGH};

	/*Init the system*/
	CLCD_voidInit();
	Buzzer_voidInit();
	Phonepad_void_Init();
	LED_voidinit( LOC_strEnterance_LED );

	/*wait until press any button to turn on the CLCD*/
	while(LOC_u8Pressed_Button == 0){LOC_u8Pressed_Button = Phonepad_u8Get_Number();}
	LOC_u8Pressed_Button = 0;
	/*clear the CLCD*/
	Clear_voidCLCD();

	/*give the user 3 tries to enter the password*/
	for( LOC_u8Iterator = 0;LOC_u8Iterator<MAXIMUM_NUMBER_FOR_TRY;LOC_u8Iterator++){

		/*ask the user to enter the password*/
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		CLCD_voidSend_String( (u8 *)"Enter Password:" );
		CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);

		for( LOC_u8Number_OF_CHAR = 0 ;LOC_u8Number_OF_CHAR<PASS_WORD_CHAR_NUM ;LOC_u8Number_OF_CHAR++){
				/*waiting for the user to press a button  */
				while( LOC_u8Pressed_Button == NOT_PRESSED ){ LOC_u8Pressed_Button = Phonepad_u8Get_Number(); }
				LOC_ptru8Pass_word_Check[LOC_u8Number_OF_CHAR] = LOC_u8Pressed_Button;
				/*display the button's value as a star*/
				CLCD_voidSend_Data('*');
				LOC_u8Pressed_Button = NOT_PRESSED;
				if( LOC_ptru8Pass_word_Check[LOC_u8Number_OF_CHAR] == LOC_ptru8PassWord[LOC_u8Number_OF_CHAR] ){
					LOC_u8Flag++;
				}
			}
			/*check if the password is right or not */
			if( LOC_u8Flag == PASS_WORD_CHAR_NUM ){

				Clear_voidCLCD();
				CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
				/*say welcome to the user for 1 sec*/
				CLCD_voidSend_String( (u8 *)"Welcome" );
				Timer1_voidDelay_Micro_Seconds(1000000);
				/*Turn on the enterance led*/
				LED_voidOn( LOC_strEnterance_LED );
				break;

			}else{
				/*display " wrong Password"*/
				Clear_voidCLCD();
				CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
				CLCD_voidSend_String( (u8 *)"Wrong Password" );

				/*check if the number of tries exceed the MAXIMUM_NUMBER_FOR_TRY*/
				if( LOC_u8Iterator+1 ==3){
					CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
					/*display "NO more tries"*/
					CLCD_voidSend_String( (u8 *)"NO more tries" );
					/*Turn on the alarm*/
					Buzzer_voidON();
					Timer1_voidDelay_Micro_Seconds(2000000);
					break;

				}else{
					/*give the user another chance */
					CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
					/*display "Try again" for 2 sec*/
					CLCD_voidSend_String( (u8 *)"Try again" );
					Timer1_voidDelay_Micro_Seconds(2000000);
				}
			}
			Clear_voidCLCD();
			LOC_u8Flag = 0;
	}
	return 0 ;
}
