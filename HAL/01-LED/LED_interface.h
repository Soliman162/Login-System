#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#define ACTIVE_HIGH 1
#define ACTIVE_LOW  0

typedef struct{

	u8 port;
	u8 pin;
	u8 active_state;

}LED_Config;

void LED_voidinit (LED_Config New_Led);
void LED_voidOn   (LED_Config New_Led);
void LED_voidOff  (LED_Config New_Led);


#endif /* HAL_01_LED_LED_INTERFACE_H_ */
