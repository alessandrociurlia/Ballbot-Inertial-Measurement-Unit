################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_rspi_rx600/src/r_rspi_rx600.c 

COMPILER_OBJS += \
r_rspi_rx600/src/r_rspi_rx600.obj 

# Each subdirectory must supply rules for building sources it contributes
r_rspi_rx600/src/%.obj: ../r_rspi_rx600/src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx -MM -MP -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" -cpu=rx600 -fpu -include="C:\Users\Alex\Desktop\DEMO\r_bsp","C:\Users\Alex\Desktop\DEMO\r_riic_rx600","C:\Users\Alex\Desktop\DEMO\r_riic_rx600\src","C:\Users\Alex\Desktop\DEMO\r_glyph","C:\Users\Alex\Desktop\DEMO\r_glyph\src","C:\Users\Alex\Desktop\DEMO\r_glyph\src\glyph","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600\src","C:\Users\Alex\Desktop\DEMO\src","C:\Program Files (x86)\Renesas\RX\2_7_0\include" -define=__RX -lang=c99 -nomessage -debug -nologo -nologo  "$<"
	ccrx -cpu=rx600 -fpu -include="C:\Users\Alex\Desktop\DEMO\r_bsp","C:\Users\Alex\Desktop\DEMO\r_riic_rx600","C:\Users\Alex\Desktop\DEMO\r_riic_rx600\src","C:\Users\Alex\Desktop\DEMO\r_glyph","C:\Users\Alex\Desktop\DEMO\r_glyph\src","C:\Users\Alex\Desktop\DEMO\r_glyph\src\glyph","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600\src","C:\Users\Alex\Desktop\DEMO\src","C:\Program Files (x86)\Renesas\RX\2_7_0\include" -define=__RX -lang=c99 -nomessage -output=obj -obj_path="r_rspi_rx600/src" -debug -nologo -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

