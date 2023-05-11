#include "std_types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"

#include "stepper_interface.h"
#include "stepper_private.h"
#include "stepper_config.h"

void Stepper_voidInit(void)
{
    SetPin_enumDirection(STEPPER_MOTOR_PORT,COIL_PIN_1,DIO_OUTPUT);
    SetPin_enumDirection(STEPPER_MOTOR_PORT,COIL_PIN_2,DIO_OUTPUT);
    SetPin_enumDirection(STEPPER_MOTOR_PORT,COIL_PIN_3,DIO_OUTPUT);
    SetPin_enumDirection(STEPPER_MOTOR_PORT,COIL_PIN_4,DIO_OUTPUT);

    SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_1,DIO_LOW);
    SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_2,DIO_LOW);
    SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_3,DIO_LOW);
    SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_4,DIO_LOW);
}
void stepper_Rotate_CW(u8 Copy_StepMode, f32 degree )
{
    u8 Step_Index = 0;
    if(Copy_StepMode>4)
    {
        Step_Index = 1;
    }
    f32 degree_counter = 0.0;

    while( degree_counter < degree )
    {
        for(u8 i=0;i<Copy_StepMode;i++)
        {
            SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_4,GETBIT( Stepper_movment_Mode[Step_Index][i], 0 ));
            SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_3,GETBIT( Stepper_movment_Mode[Step_Index][i], 1 ));
            SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_2,GETBIT( Stepper_movment_Mode[Step_Index][i], 2 ));
            SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_1,GETBIT( Stepper_movment_Mode[Step_Index][i], 3 ));
            Timer1_voidDelay_Micro_Seconds(MAX_DELAY*1000);
            degree_counter+=DEGREE_PER_STEP;
        }
    }
}
void stepper_Rotate_CCW(u8 Copy_StepMode, f32 degree )
{
    u8 Step_Index = 0;
    if(Copy_StepMode>4)
    {
        Step_Index = 1;
    }

    f32 degree_counter = 0;

    while( degree_counter < degree )
    {
        for(u8 i=0;i<Copy_StepMode;i++)
        {
            SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_1,GETBIT( Stepper_movment_Mode[Step_Index][i], 0 ));
            SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_2,GETBIT( Stepper_movment_Mode[Step_Index][i], 1 ));
            SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_4,GETBIT( Stepper_movment_Mode[Step_Index][i], 3 ));
            SetPin_enumValue(STEPPER_MOTOR_PORT,COIL_PIN_3,GETBIT( Stepper_movment_Mode[Step_Index][i], 2 ));
            Timer1_voidDelay_Micro_Seconds(MAX_DELAY*1000);
            degree_counter+=DEGREE_PER_STEP;
        }
    }
}