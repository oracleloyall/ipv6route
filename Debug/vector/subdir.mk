################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vector/example.c \
../vector/vector.c 

OBJS += \
./vector/example.o \
./vector/vector.o 

C_DEPS += \
./vector/example.d \
./vector/vector.d 


# Each subdirectory must supply rules for building sources it contributes
vector/%.o: ../vector/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


