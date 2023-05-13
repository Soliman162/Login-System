#include "std_types.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"

u8 string[20];
void  (*UART_ISR[2])(void) = {NULL};

void UART_voidInit(void)
{
    UCSRA = 0b00000000;
	UCSRB = 0b00011000;
	UCSRC = 0b10000110;

    // buad rate 9600 -> 51  115200 -> 3
	UBRRL = 51;
	UBRRH = 0;
}
u8 UART_u8Receive_Char(void)
{
    while(GETBIT(UCSRA,7) != 1);
    return UDR;
}
void UART_voidTransmit_Char(u8 Copy_u8Data)
{
    UDR = Copy_u8Data;
    while(GETBIT(UCSRA,6) != 1 );
    while(GETBIT(UCSRA,5) != 1 );
}

u8 * UART_u8ptrReceive_String(void)
{
    u8 Received_Data = 0;
    u8 Iterator = 0;
    while( Received_Data = UART_u8Receive_Char() != 13 )
    {
        string[Iterator++] = Received_Data;
    }
    return string;
}
void UART_voidTransmit_String(u8 *Copy_u8Data)
{
    u8 Iterator = 0;
    while( Copy_u8Data[Iterator] != '\0' )
    {
        UART_voidTransmit_Char(Copy_u8Data[Iterator++]);
    }
}

void UART_voidInterruptEnable(u8 Copy_u8Interrupt,void (*Copy_ptrISR)(void))
{
    SETBIT(UCSRB,Copy_u8Interrupt);
    UART_ISR[Copy_u8Interrupt-TRANSMIT_INTERRUPT] = Copy_ptrISR;
}

void __vector_13 (void)
{
    if(UART_ISR[1] != NULL)
    {
        UART_ISR[1]();
    }
}
void __vector_15 (void)
{
    if(UART_ISR[0] != NULL)
    {
        UART_ISR[0]();
    }
}
