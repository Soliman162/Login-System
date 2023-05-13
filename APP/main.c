#include "std_types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"
//#include "ADC_interface.h"

#include "LED_interface.h"
#include "CLCD_interface.h"
#include "KeyPad_interface.h"
#include "BUZZER_interface.h"
#include "stepper_interface.h"
#include "LM35_interface.h"
#include "LDR_interface.h"
#include "EXINT_interface.h"

/***************************************************CPU Core Registers macros****************************************************/
#define STATUS_REG  *((volatile u8*)0x5F)
/********************************************************************************************************************************/
/***************************************************BIT number*******************************************************************/
#define ENABLE_INTERRUPT_BIT_NUM    7
/********************************************************************************************************************************/

static inline void CPU_Core_voidEnable_INTERRUPT(void)
{
    SETBIT(STATUS_REG,ENABLE_INTERRUPT_BIT_NUM);
}


#define 		PASS_WORD_CHAR_NUM 						4
#define 		NOT_PRESSED								0
#define  		MAXIMUM_NUMBER_FOR_TRY					3

#define 		OPEN_DOOR_OP		'+'
#define 		CHANGE_PASSWORD_OP	'-'

volatile u8  LOC_u8ISR_flag = 0;
volatile LED_Config	LOC_strEnterance_LED = {PORTD ,PIN3 ,ACTIVE_HIGH};
volatile	u8  LOC_u8Flag = 0;
volatile	u8  LOC_u8Pressed_Button =NOT_PRESSED ;



void EXint0_ISR(void)
{
	if((LOC_u8ISR_flag == 1) )
	{
		Clear_voidCLCD();
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		/*say welcome to the user for 1 sec*/
		CLCD_voidSend_String( (u8 *)"Welcome" );
		//Timer1_voidDelay_Micro_Seconds(200000);
		/*open door*/
		stepper_Rotate_CW(HALF_STEP,180);
		/*Turn on the enterance led*/
		LED_voidOn( LOC_strEnterance_LED );
		Timer1_voidDelay_Micro_Seconds(3000000);
		/*close door*/
		stepper_Rotate_CCW(HALF_STEP,180);
		LED_voidOff( LOC_strEnterance_LED );
						CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
				CLCD_voidSend_String( (u8 *)"Enter Password:" );
				CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
				LOC_u8Pressed_Button = NOT_PRESSED;
				LOC_u8Flag = 0;
	}
}


int main (void){

	u8  LOC_u8Iterator = 0;
	u8  LOC_u8Number_OF_CHAR = 0;
	u8  LOC_ptru8PassWord [PASS_WORD_CHAR_NUM]="1234" ;
    u8  LOC_ptru8Pass_word_Check[PASS_WORD_CHAR_NUM]  = "" ;
	u32 LM35_u32Temperature = 10;
	u32 LDR_u32Value = 10;
	
	
	LED_Config	LOC_strWarning_LED = {PORTD ,PIN4 ,ACTIVE_HIGH};
	//LED_Config	LOC_strAC_LED = {PORTD ,PIN7 ,ACTIVE_HIGH};

	/*Init the system*/
	Timer1_voidInit();
	CLCD_voidInit();
	Buzzer_voidInit();
	Stepper_voidInit();
	KEY_PAD_voidINIT();

	SetPin_enumDirection(PORTD,PIN2,DIO_INPUT);
	SetPin_enumValue(PORTD,PIN2,DIO_HIGH);
	EXINT_voidInit();
	EXINT_voidSet_Call_Back(EXTINT_0,EXint0_ISR);
/* 	LM35_voidInit();
	LDR_voidInit(); */

	LED_voidinit( LOC_strEnterance_LED );
	LED_voidinit(LOC_strWarning_LED);
	//LED_voidinit(LOC_strAC_LED);
	CPU_Core_voidEnable_INTERRUPT();
	LOC_u8ISR_flag = 1;

	while (1)
	{
			/*give the user 3 tries to enter the password*/
		for( LOC_u8Iterator = 0;LOC_u8Iterator<MAXIMUM_NUMBER_FOR_TRY;LOC_u8Iterator++){
				Clear_voidCLCD();
				/*ask the user to enter the password*/
				CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
				CLCD_voidSend_String( (u8 *)"Enter Password:" );
				CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
				LOC_u8Pressed_Button = NOT_PRESSED;
				LOC_u8Flag = 0;
				for( LOC_u8Number_OF_CHAR = 0 ;LOC_u8Number_OF_CHAR<PASS_WORD_CHAR_NUM ;LOC_u8Number_OF_CHAR++)
					{
						/*waiting for the user to press a button  */
						while( LOC_u8Pressed_Button == NOT_PRESSED ){ LOC_u8Pressed_Button = KEY_PAD_ptru8GET_PRESSED_VALUE(); }
						LOC_u8ISR_flag = 0;
						LOC_ptru8Pass_word_Check[LOC_u8Number_OF_CHAR] = LOC_u8Pressed_Button;
						/*display the button's value as a star*/
						CLCD_voidSend_Data('*');
						//CLCD_voidSend_Data(LOC_u8Pressed_Button);
						LOC_u8Pressed_Button = NOT_PRESSED;
						if( LOC_ptru8Pass_word_Check[LOC_u8Number_OF_CHAR] == LOC_ptru8PassWord[LOC_u8Number_OF_CHAR] ){
							LOC_u8Flag++;
						}
					}
					LOC_u8ISR_flag = 1;
					/*check if the password is right or not */
					if( LOC_u8Flag == PASS_WORD_CHAR_NUM )
					{
						LOC_u8ISR_flag = 0;
						LOC_u8Iterator = 0;
						LOC_u8Flag = 0;
						while(LOC_u8Flag==0)
						{
							Clear_voidCLCD();
							LOC_u8Pressed_Button = NOT_PRESSED;
							CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
							CLCD_voidSend_String((u8 *)"+:open door");

							CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
							CLCD_voidSend_String((u8 *)"-:Change Password");

							while(LOC_u8Pressed_Button == NOT_PRESSED){LOC_u8Pressed_Button = KEY_PAD_ptru8GET_PRESSED_VALUE();}
							Clear_voidCLCD();
							if(LOC_u8Pressed_Button == OPEN_DOOR_OP )
							{
								LOC_u8Flag++;
								CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
								/*say welcome to the user for 1 sec*/
								CLCD_voidSend_String( (u8 *)"Welcome" );
								//Timer1_voidDelay_Micro_Seconds(200000);
								/*open door*/
								stepper_Rotate_CW(HALF_STEP,180);
								/*Turn on the enterance led*/
								LED_voidOn( LOC_strEnterance_LED );
								Timer1_voidDelay_Micro_Seconds(3000000);
								/*close door*/
								stepper_Rotate_CCW(HALF_STEP,180);
								LED_voidOff( LOC_strEnterance_LED );
								//Clear_voidCLCD();

							}else if(LOC_u8Pressed_Button == CHANGE_PASSWORD_OP )
							{
								CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
								CLCD_voidSend_String((u8 *)"Enter New Pass:");
								CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
								for(LOC_u8Number_OF_CHAR=0;LOC_u8Number_OF_CHAR<PASS_WORD_CHAR_NUM;LOC_u8Number_OF_CHAR++)
								{
									LOC_u8Pressed_Button = NOT_PRESSED;
									/*wait until press any button to turn on the CLCD*/
									while(LOC_u8Pressed_Button == NOT_PRESSED){LOC_u8Pressed_Button = KEY_PAD_ptru8GET_PRESSED_VALUE();}
									LOC_ptru8Pass_word_Check[LOC_u8Number_OF_CHAR] = LOC_u8Pressed_Button;
									CLCD_voidSend_Data('*');
								}	
								Clear_voidCLCD();
								CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
								CLCD_voidSend_String((u8 *)"Enter Pass again:");
								CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
								for(LOC_u8Number_OF_CHAR=0;LOC_u8Number_OF_CHAR<PASS_WORD_CHAR_NUM;LOC_u8Number_OF_CHAR++)
								{
									LOC_u8Pressed_Button = NOT_PRESSED;
									while(LOC_u8Pressed_Button == NOT_PRESSED){LOC_u8Pressed_Button = KEY_PAD_ptru8GET_PRESSED_VALUE();}
									if( LOC_ptru8Pass_word_Check[LOC_u8Number_OF_CHAR] == LOC_u8Pressed_Button)
									{
										LOC_u8Flag++;
									}
									CLCD_voidSend_Data('*');
								}	
								Clear_voidCLCD();
								CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
								if(LOC_u8Flag==4)
								{
									LOC_u8Pressed_Button = NOT_PRESSED;
									for(LOC_u8Number_OF_CHAR = 0;LOC_u8Number_OF_CHAR<PASS_WORD_CHAR_NUM;LOC_u8Number_OF_CHAR++)
									{
										LOC_ptru8PassWord[LOC_u8Number_OF_CHAR] = LOC_ptru8Pass_word_Check[LOC_u8Number_OF_CHAR]; 
									}
									CLCD_voidSend_String((u8 *)"new pass saved");
								}else
								{
									CLCD_voidSend_String((u8 *)"pass doesn't match");
									LOC_u8Flag = 0;
								}
								Timer1_voidDelay_Micro_Seconds(2000000);
							}
							else
							{
								Clear_voidCLCD();
								CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
								CLCD_voidSend_String( (u8 *)"Wrong Choice" );

								CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
								CLCD_voidSend_String( (u8 *)"try again" );
								Timer1_voidDelay_Micro_Seconds(100000);
							}
						}
						break;
					}else
					{
						LOC_u8ISR_flag = 0; 
						/*display " wrong Password"*/
						Clear_voidCLCD();
						CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
						CLCD_voidSend_String( (u8 *)"Wrong Password" );
						/*check if the number of tries exceed the MAXIMUM_NUMBER_FOR_TRY*/
						if( LOC_u8Iterator+1 == 3){
							
							CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
							/*display "NO more tries"*/
							CLCD_voidSend_String( (u8 *)"wait 5 sec" );
							/*Turn on the alarm*/
							Buzzer_voidON();
							LED_voidOn(LOC_strWarning_LED);
							Timer1_voidDelay_Micro_Seconds(5000000);
							LED_voidOff(LOC_strWarning_LED);
							break;
						}else{
							/*give the user another chance */
							CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
							/*display "Try again" for 2 sec*/
							CLCD_voidSend_String( (u8 *)"Try again" );
							Timer1_voidDelay_Micro_Seconds(2000000);
						}
						LOC_u8ISR_flag = 1;
					}
					LOC_u8ISR_flag = 1;
		}
	}
	return 0 ;
}

/* 								while(1)
								{
									LM35_u32Temperature = LM35_u32Read_Temp();
									Timer1_voidDelay_Micro_Seconds(1000000);
									CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
									if(LM35_u32Temperature <= 27)
									{
										CLCD_voidSend_String( (u8 *)"AC is OFF " );
										LED_voidOn(LOC_strAC_LED);
									}else if(LM35_u32Temperature>27)
									{
										CLCD_voidSend_String( (u8 *)"AC is ON " );
										LED_voidOn(LOC_strAC_LED);
									}
									//CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
									CLCD_void_Send_Number(LM35_u32Temperature);

									LDR_u32Value = LDR_u32Read_Light_Indensty();
									CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);

									CLCD_void_Send_Number(LDR_u32Value);
									Timer1_voidDelay_Micro_Seconds(1000000);
								} */