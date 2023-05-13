#include "std_types.h"

#include "DIO_interface.h"
#include "ADC_interface.h"

#include "LM35_interface.h"
#include "LM35_private.h"
#include "LM35_config.h"

u32 Temp_u32 = 0;

void LM35_voidInit(void)
{
    SetPin_enumDirection(PORTA,LM35_PIN,DIO_INPUT);
    ADC_voidInit();
}
u32 LM35_u32Read_Temp(void)
{
    ADC_voidSelect_SingleEnded_Channel(LM35_PIN);
    ADC_voidStart_Conversion();
    Temp_u32 = ((u32)ADC_u16GET_Conversion_Data()*Vin_mv)/RESOLUTION;
    Temp_u32/=LM_35_STEP_SIZE;
  
    return Temp_u32;
}