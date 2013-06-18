################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/player/Player.cpp 

OBJS += \
./src/player/Player.o 

CPP_DEPS += \
./src/player/Player.d 


# Each subdirectory must supply rules for building sources it contributes
src/player/%.o: ../src/player/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/home/david/code/cpp/libs/SFML-2.0/include -I"/home/david/repos/rac0r/eclipse_linux" -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


