#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

#define UDR   *((volatile u8 *)0X2C)
#define UCSRA *((volatile u8 *)0x2B)
#define UCSRB *((volatile u8 *)0x2A)
#define UCSRC *((volatile u8 *)0x40)
#define UBRRL *((volatile u8 *)0x29)
#define UBRRH *((volatile u8 *)0x40)   

/*recieve*/
void __vector_13 (void) __attribute__((signal));
/*transmit*/
void __vector_15 (void) __attribute__((signal));

#endif
