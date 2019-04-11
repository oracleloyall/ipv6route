################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../list/list.c \
../list/list_iterator.c \
../list/list_node.c \
../list/test_list.c 

OBJS += \
./list/list.o \
./list/list_iterator.o \
./list/list_node.o \
./list/test_list.o 

C_DEPS += \
./list/list.d \
./list/list_iterator.d \
./list/list_node.d \
./list/test_list.d 


# Each subdirectory must supply rules for building sources it contributes
list/%.o: ../list/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


