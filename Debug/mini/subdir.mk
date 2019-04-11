################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mini/example3.c \
../mini/mini-file.c \
../mini/mini-parser.c \
../mini/mini-readline.c \
../mini/mini-strip.c 

OBJS += \
./mini/example3.o \
./mini/mini-file.o \
./mini/mini-parser.o \
./mini/mini-readline.o \
./mini/mini-strip.o 

C_DEPS += \
./mini/example3.d \
./mini/mini-file.d \
./mini/mini-parser.d \
./mini/mini-readline.d \
./mini/mini-strip.d 


# Each subdirectory must supply rules for building sources it contributes
mini/%.o: ../mini/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


