#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H


#define KEY_PAD_INIT_PORT		PORTC

#define  KEY_PAD_ROW_START		PIN0
#define  KEY_PAD_ROW_END		PIN3

#define KEY_PAD_ROW_0			PIN0
#define KEY_PAD_ROW_1			PIN1
#define KEY_PAD_ROW_2			PIN2
#define KEY_PAD_ROW_3			PIN3

#define  KEY_PAD_COL_START		PIN4
#define  KEY_PAD_COL_END		PIN6

#define KEY_PAD_COL_0			PIN4
#define KEY_PAD_COL_1			PIN5
#define KEY_PAD_COL_2			PIN6

u8 Key_pad[4][3] = {
							{'1','2','3'},
							{'4','5','6'},
							{'7','8','9'},
							{'*','0','#'},
											};

#endif
