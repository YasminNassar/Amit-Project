################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_Program.c \
../GIE_Program.c \
../GLCD_Program.c \
../TIMER_Program.c \
../main.c 

OBJS += \
./DIO_Program.o \
./GIE_Program.o \
./GLCD_Program.o \
./TIMER_Program.o \
./main.o 

C_DEPS += \
./DIO_Program.d \
./GIE_Program.d \
./GLCD_Program.d \
./TIMER_Program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=2000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


