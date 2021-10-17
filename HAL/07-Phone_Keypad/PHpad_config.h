/*
 * PHpad_config.h
 *
 *  Created on: Oct 2, 2021
 *      Author: DELL
 */

#ifndef HAL_07_PHONE_KEYPAD_PHPAD_CONFIG_H_
#define HAL_07_PHONE_KEYPAD_PHPAD_CONFIG_H_


#define PHONE_PAD_INIT_PORT		PORTC

#define  PHONE_PAD_ROW_START	PIN0
#define  PHONE_PAD_ROW_END		PIN3

#define PHONE_PAD_ROW_0		PIN0
#define PHONE_PAD_ROW_1		PIN1
#define PHONE_PAD_ROW_2		PIN2
#define PHONE_PAD_ROW_3		PIN3

#define  PHONE_PAD_COL_START	PIN4
#define  PHONE_PAD_COL_END		PIN6

#define PHONE_PAD_COL_0		PIN4
#define PHONE_PAD_COL_1		PIN5
#define PHONE_PAD_COL_2		PIN6

u8 LOC_PHONE_PAD[4][3] = {
							{'1','2','3'},
							{'4','5','6'},
							{'7','8','9'},
							{'*','0','#'},
											};



#endif /* HAL_07_PHONE_KEYPAD_PHPAD_CONFIG_H_ */
