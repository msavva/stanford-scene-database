################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../common/Assets.cpp \
../common/Camera.cpp \
../common/Matrix4.cpp \
../common/Mesh.cpp \
../common/Model.cpp \
../common/ModelDatabase.cpp \
../common/ModelInstance.cpp \
../common/Parameters.cpp \
../common/Scene.cpp \
../common/Utility.cpp 

OBJS += \
./common/Assets.o \
./common/Camera.o \
./common/Matrix4.o \
./common/Mesh.o \
./common/Model.o \
./common/ModelDatabase.o \
./common/ModelInstance.o \
./common/Parameters.o \
./common/Scene.o \
./common/Utility.o 

CPP_DEPS += \
./common/Assets.d \
./common/Camera.d \
./common/Matrix4.d \
./common/Mesh.d \
./common/Model.d \
./common/ModelDatabase.d \
./common/ModelInstance.d \
./common/Parameters.d \
./common/Scene.d \
./common/Utility.d 


# Each subdirectory must supply rules for building sources it contributes
common/%.o: ../common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


