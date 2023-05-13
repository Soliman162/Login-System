#ifndef EXINT_INTERFACE_H
#define EXINT_INTERFACE_H

typedef enum{

    EXTINT_0 =0,
    EXTINT_1,
    EXTINT_2

}Config_EXINT_INDEX;

void EXINT_voidInit(void);

void EXINT_voidSet_Call_Back(Config_EXINT_INDEX Copy_EXINT, void (*Copy_ptrISR)(void) );





#endif