################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/arrayFunctions.c \
../src/filters.c \
../src/main.c \
../src/qsr.c \
../src/sensor.c 

OBJS += \
./src/arrayFunctions.o \
./src/filters.o \
./src/main.o \
./src/qsr.o \
./src/sensor.o 

C_DEPS += \
./src/arrayFunctions.d \
./src/filters.d \
./src/main.d \
./src/qsr.d \
./src/sensor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


