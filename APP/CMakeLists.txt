CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(LOG_IN_SYSTEM)

set(CMAKE_GENERATOR CACHE STRING "Unix Makefiles")
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++ CACHE STRING "C++ compiler" FORCE)
set(CMAKE_C_COMPILER avr-gcc CACHE STRING "C compiler" FORCE)
set(CMAKE_OBJCOPY      avr-objcopy CACHE STRING "avr-objcopy" FORCE)

set(CMAKE_C_FLAGS "-mmcu=atmega32 -O1 -DF_CPU=8000000UL ")


add_executable( ${PROJECT_NAME}.elf 

                            ${CMAKE_CURRENT_SOURCE_DIR}/main.c

                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/01-LED/LED_program.c
                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/02-CLCD/CLCD_program.c
                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/03-KeyPad/KeyPad_program.c
                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/04-BUZZER/BUZZER_program.c
                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/05-stepper_motor/stepper_program.c
                            
                            ${CMAKE_CURRENT_SOURCE_DIR}/../MCAL/01-DIO/DIO_program.c
                            ${CMAKE_CURRENT_SOURCE_DIR}/../MCAL/02-Timer1/TIMER1_program.c
                            ${CMAKE_CURRENT_SOURCE_DIR}/../MCAL/07-EXINT/EXINT_program.c
)  

target_include_directories( ${PROJECT_NAME}.elf PUBLIC

                            ${CMAKE_CURRENT_SOURCE_DIR}/../MCAL/01-DIO
                            ${CMAKE_CURRENT_SOURCE_DIR}/../MCAL/02-Timer1

                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/01-LED
                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/02-CLCD
                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/03-KeyPad
                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/04-BUZZER
                            ${CMAKE_CURRENT_SOURCE_DIR}/../HAL/05-stepper_motor
                            ${CMAKE_CURRENT_SOURCE_DIR}/../MCAL/07-EXINT/

                            ${CMAKE_CURRENT_SOURCE_DIR}/../LIB                 
)     

add_custom_target(build ALL
                DEPENDS ${PROJECT_NAME}.elf
                COMMAND avr-objcopy -j .text -j .data -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
                ) 
                
add_custom_target(flash 
                DEPENDS build 
                COMMAND  avrdude -c usbasp -p m32 -B 0.5 -U flash:w:"${PROJECT_NAME}.hex":a 
)

add_custom_target(remove
                    COMMAND  rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/build/*
)

