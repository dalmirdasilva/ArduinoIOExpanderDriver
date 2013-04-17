################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../IOExpander/IOExpander.cpp 

OBJS += \
./IOExpander/IOExpander.o 

CPP_DEPS += \
./IOExpander/IOExpander.d 


# Each subdirectory must supply rules for building sources it contributes
IOExpander/%.o: ../IOExpander/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/storage/microcontroller/arduino/driver/io_expander/IOExpander" -I"/storage/microcontroller/arduino/driver/io_expander/IOExpanderMCP23X17" -I/usr/share/arduino/hardware/arduino/variants/standard -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/libraries/Wire -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


