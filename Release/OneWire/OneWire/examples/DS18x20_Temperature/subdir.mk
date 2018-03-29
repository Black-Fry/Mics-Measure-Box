################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
PDE_SRCS += \
..\OneWire\OneWire\examples\DS18x20_Temperature\DS18x20_Temperature.pde 

PDE_DEPS += \
.\OneWire\OneWire\examples\DS18x20_Temperature\DS18x20_Temperature.pde.d 


# Each subdirectory must supply rules for building sources it contributes
OneWire\OneWire\examples\DS18x20_Temperature\DS18x20_Temperature.o: ..\OneWire\OneWire\examples\DS18x20_Temperature\DS18x20_Temperature.pde
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\Micha\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"C:\Users\Micha\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\cores\arduino" -I"C:\Users\Micha\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


