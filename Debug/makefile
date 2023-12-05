################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
GLCD_Project_Train.lss \

FLASH_IMAGE += \
GLCD_Project_Train.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: GLCD_Project_Train.elf secondary-outputs

# Tool invocations
GLCD_Project_Train.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,GLCD_Project_Train.map -mmcu=atmega32 -o "GLCD_Project_Train.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

GLCD_Project_Train.lss: GLCD_Project_Train.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S GLCD_Project_Train.elf  >"GLCD_Project_Train.lss"
	@echo 'Finished building: $@'
	@echo ' '

GLCD_Project_Train.hex: GLCD_Project_Train.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex GLCD_Project_Train.elf  "GLCD_Project_Train.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: GLCD_Project_Train.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 GLCD_Project_Train.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) GLCD_Project_Train.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
