#include "std_types.h"
#include "BIT_MATH.h"

#include "EXINT_interface.h"
#include "EXINT_private.h"
#include "EXINT_config.h"

void  (*EXINT_ISR[3])(void) = {NULL};

void EXINT_voidInit(void)
{
    /*Disable all External interrupt interrupt*/
    GICR_REG = 0;

    #if INT0_STATE == ENABLE
        /*set activation state for interrupt 0 */
        MCUCR_REG |= INT0_ACTIVATION_STATE;
        /*enable external interrupt 0 */
        SETBIT(GICR_REG,6);
    #endif

    #if INT1_STATE == ENABLE
        /*set activation state for interrupt 1*/
        MCUCR_REG |= INT1_ACTIVATION_STATE<<2;
        /*enable external interrupt 1 */
        SETBIT(GICR_REG,7);
    #endif

    #if INT2_STATE == ENABLE

        #if INT2_ACTIVATION_STATE == FALLING_EDGE
            CLRBIT(MCUCSR_REG,6);
        #elif INT2_ACTIVATION_STATE == RISING_EDGE
            SETBIT(MCUCSR_REG,6);
        #endif
        /*enable external interrupt 2 */
        SETBIT(GICR_REG,5);
    #endif
}

void EXINT_voidSet_Call_Back(Config_EXINT_INDEX Copy_EXINT, void (*Copy_ptrISR)(void) )
{
    EXINT_ISR[Copy_EXINT] = Copy_ptrISR;
}


void __vector_1 (void)
{
    if( EXINT_ISR[EXTINT_0] != NULL )
    {
        EXINT_ISR[EXTINT_0]();
    }
    SETBIT(GIFR_REG,6);
}
void __vector_2 (void) 
{
    if( EXINT_ISR[EXTINT_1] != NULL )
    {
        EXINT_ISR[EXTINT_1]();
    }
}
void __vector_3 (void)
{
    if( EXINT_ISR[EXTINT_2] != NULL )
    {
        EXINT_ISR[EXTINT_2]();
    }
}