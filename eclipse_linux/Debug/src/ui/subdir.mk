################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ui/GameScreen.cpp \
../src/ui/MenuScreen.cpp \
../src/ui/Screen.cpp 

OBJS += \
./src/ui/GameScreen.o \
./src/ui/MenuScreen.o \
./src/ui/Screen.o 

CPP_DEPS += \
./src/ui/GameScreen.d \
./src/ui/MenuScreen.d \
./src/ui/Screen.d 


# Each subdirectory must supply rules for building sources it contributes
src/ui/%.o: ../src/ui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/home/david/code/cpp/libs/SFML-2.0/include -I"/home/david/repos/rac0r/eclipse_linux" -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -std=c++0x -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


