################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ..\makefile.init

RM := del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include core\core\subdir.mk
-include OneWire\OneWire\examples\DS250x_PROM\subdir.mk
-include OneWire\OneWire\examples\DS2408_Switch\subdir.mk
-include OneWire\OneWire\examples\DS18x20_Temperature\subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ..\makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
D:\prog\Arduino\pro mini\Mics-Measure-Box\Release\arduino.ar \

ELF += \
Mics_Measure_Box.elf \

HEX += \
Mics_Measure_Box.hex \


# All Target
all: Mics_Measure_Box

# Tool invocations
Mics_Measure_Box: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:\Users\Micha\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-size" -A "D:/prog/Arduino/pro mini/Mics-Measure-Box/Release/Mics_Measure_Box.elf"
	@echo 'Finished building target: $@'
	@echo ' '

D:\prog\Arduino\pro\ mini\Mics-Measure-Box\Release\arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:\Users\Micha\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs    D:/prog/Arduino/pro mini/Mics-Measure-Box/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Mics_Measure_Box.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:\Users\Micha\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -o "D:\prog\Arduino\pro mini\Mics-Measure-Box/Release/Mics_Measure_Box.elf"   $(LINK_OBJ)   D:/prog/Arduino/pro mini/Mics-Measure-Box/Release/arduino.ar  "-LD:\prog\Arduino\pro mini\Mics-Measure-Box/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

Mics_Measure_Box.hex: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ..\makefile.targets
