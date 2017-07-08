################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Apps.cpp \
../src/FAT.cpp \
../src/FBL.cpp \
../src/FIT.cpp \
../src/File.cpp \
../src/Functions.cpp \
../src/Inode.cpp \
../src/SuperBlock.cpp \
../src/VFS_3.cpp 

OBJS += \
./src/Apps.o \
./src/FAT.o \
./src/FBL.o \
./src/FIT.o \
./src/File.o \
./src/Functions.o \
./src/Inode.o \
./src/SuperBlock.o \
./src/VFS_3.o 

CPP_DEPS += \
./src/Apps.d \
./src/FAT.d \
./src/FBL.d \
./src/FIT.d \
./src/File.d \
./src/Functions.d \
./src/Inode.d \
./src/SuperBlock.d \
./src/VFS_3.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


