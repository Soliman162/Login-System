#ifndef EXINT_PRIVATE_H
#define EXINT_PRIVATE_H

#define ENABLE         1
#define DISABLE        0

#define LOW_LEVEL               0b00
#define ANY_LOGICAL_CHANGE      0b01
#define FALLING_EDGE            0b10
#define RISING_EDGE             0b11

#define MCUCR_REG    *((volatile u8 *)0x55)
#define MCUCSR_REG   *((volatile u8 *)0x54)
#define GICR_REG     *((volatile u8 *)0x5B)
#define GIFR_REG     *((volatile u8 *)0x5A)


void __vector_1 (void) __attribute__((signal));
void __vector_2 (void) __attribute__((signal));
void __vector_3 (void) __attribute__((signal));


#endif