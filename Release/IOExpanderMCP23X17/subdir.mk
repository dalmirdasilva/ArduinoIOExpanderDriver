################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../IOExpanderMCP23X17/IOExpanderMCP23X17.cpp 

OBJS += \
./IOExpanderMCP23X17/IOExpanderMCP23X17.o 

CPP_DEPS += \
./IOExpanderMCP23X17/IOExpanderMCP23X17.d 


# Each subdirectory must supply rules for building sources it contributes
IOExpanderMCP23X17/%.o: ../IOExpanderMCP23X17/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/storage/microcontroller/arduino/driver/io_expander/IOExpander" -I"/storage/microcontroller/arduino/driver/io_expander/IOExpanderMCP23X17" -I/usr/share/arduino/hardware/arduino/variants/standard -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/libraries/Wire -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


