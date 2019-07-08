################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_glyph/src/glyph/glyph.c 

COMPILER_OBJS += \
r_glyph/src/glyph/glyph.obj 

# Each subdirectory must supply rules for building sources it contributes
r_glyph/src/glyph/%.obj: ../r_glyph/src/glyph/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx -MM -MP -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" -cpu=rx600 -fpu -include="C:\Users\Alex\Desktop\DEMO\r_bsp","C:\Users\Alex\Desktop\DEMO\r_riic_rx600","C:\Users\Alex\Desktop\DEMO\r_riic_rx600\src","C:\Users\Alex\Desktop\DEMO\r_glyph","C:\Users\Alex\Desktop\DEMO\r_glyph\src","C:\Users\Alex\Desktop\DEMO\r_glyph\src\glyph","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600\src","C:\Users\Alex\Desktop\DEMO\src","C:\Program Files (x86)\Renesas\RX\2_7_0\include" -define=__RX -lang=c99 -nomessage -debug -nologo -nologo  "$<"
	ccrx -cpu=rx600 -fpu -include="C:\Users\Alex\Desktop\DEMO\r_bsp","C:\Users\Alex\Desktop\DEMO\r_riic_rx600","C:\Users\Alex\Desktop\DEMO\r_riic_rx600\src","C:\Users\Alex\Desktop\DEMO\r_glyph","C:\Users\Alex\Desktop\DEMO\r_glyph\src","C:\Users\Alex\Desktop\DEMO\r_glyph\src\glyph","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600\src","C:\Users\Alex\Desktop\DEMO\src","C:\Program Files (x86)\Renesas\RX\2_7_0\include" -define=__RX -lang=c99 -nomessage -output=obj -obj_path="r_glyph/src/glyph" -debug -nologo -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

