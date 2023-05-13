#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#define RECIEVE_INTERRUPT       7
#define TRANSMIT_INTERRUPT      6

void UART_voidInit(void);
u8 UART_u8Receive_Char(void);
void UART_voidTransmit_Char(u8 Copy_u8Data);
u8 * UART_u8ptrReceive_String(void);
void UART_voidTransmit_String(u8 *Copy_u8Data);
void UART_voidInterruptEnable(u8 Copy_u8Interrupt,void (*Copy_ptrISR)(void));





#endif
