################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sourcefiles/arrayFunctions.c \
../sourcefiles/filters.c \
../sourcefiles/main.c \
../sourcefiles/qsr.c \
../sourcefiles/sensor.c 

OBJS += \
./sourcefiles/arrayFunctions.o \
./sourcefiles/filters.o \
./sourcefiles/main.o \
./sourcefiles/qsr.o \
./sourcefiles/sensor.o 

C_DEPS += \
./sourcefiles/arrayFunctions.d \
./sourcefiles/filters.d \
./sourcefiles/main.d \
./sourcefiles/qsr.d \
./sourcefiles/sensor.d 


# Each subdirectory must supply rules for building sources it contributes
sourcefiles/%.o: ../sourcefiles/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


