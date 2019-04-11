################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ini/example1.c \
../ini/ini.c 

OBJS += \
./ini/example1.o \
./ini/ini.o 

C_DEPS += \
./ini/example1.d \
./ini/ini.d 


# Each subdirectory must supply rules for building sources it contributes
ini/%.o: ../ini/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


