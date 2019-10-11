################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ClientP2P.cpp \
../Commands.cpp \
../NetSocketWorker.cpp \
../StandartBuilder.cpp \
../StandartCommandInterpreter.cpp \
../StandartDataWorker.cpp \
../ThreadRequestsHandler.cpp \
../Translator.cpp \
../main.cpp 

OBJS += \
./ClientP2P.o \
./Commands.o \
./NetSocketWorker.o \
./StandartBuilder.o \
./StandartCommandInterpreter.o \
./StandartDataWorker.o \
./ThreadRequestsHandler.o \
./Translator.o \
./main.o 

CPP_DEPS += \
./ClientP2P.d \
./Commands.d \
./NetSocketWorker.d \
./StandartBuilder.d \
./StandartCommandInterpreter.d \
./StandartDataWorker.d \
./ThreadRequestsHandler.d \
./Translator.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


