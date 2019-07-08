################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_bsp/board/rdkrx63n/dbsct.c \
../r_bsp/board/rdkrx63n/flash_options.c \
../r_bsp/board/rdkrx63n/hwsetup.c \
../r_bsp/board/rdkrx63n/lcd.c \
../r_bsp/board/rdkrx63n/lowsrc.c \
../r_bsp/board/rdkrx63n/resetprg.c \
../r_bsp/board/rdkrx63n/sbrk.c \
../r_bsp/board/rdkrx63n/vecttbl.c 

SRC_SRCS += \
../r_bsp/board/rdkrx63n/lowlvl.src 

ASSEMBLER_OBJS += \
r_bsp/board/rdkrx63n/lowlvl.obj 

COMPILER_OBJS += \
r_bsp/board/rdkrx63n/dbsct.obj \
r_bsp/board/rdkrx63n/flash_options.obj \
r_bsp/board/rdkrx63n/hwsetup.obj \
r_bsp/board/rdkrx63n/lcd.obj \
r_bsp/board/rdkrx63n/lowsrc.obj \
r_bsp/board/rdkrx63n/resetprg.obj \
r_bsp/board/rdkrx63n/sbrk.obj \
r_bsp/board/rdkrx63n/vecttbl.obj 

# Each subdirectory must supply rules for building sources it contributes
r_bsp/board/rdkrx63n/%.obj: ../r_bsp/board/rdkrx63n/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx -MM -MP -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" -cpu=rx600 -fpu -include="C:\Users\Alex\Desktop\DEMO\r_bsp","C:\Users\Alex\Desktop\DEMO\r_riic_rx600","C:\Users\Alex\Desktop\DEMO\r_riic_rx600\src","C:\Users\Alex\Desktop\DEMO\r_glyph","C:\Users\Alex\Desktop\DEMO\r_glyph\src","C:\Users\Alex\Desktop\DEMO\r_glyph\src\glyph","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600\src","C:\Users\Alex\Desktop\DEMO\src","C:\Program Files (x86)\Renesas\RX\2_7_0\include" -define=__RX -lang=c99 -nomessage -debug -nologo -nologo  "$<"
	ccrx -cpu=rx600 -fpu -include="C:\Users\Alex\Desktop\DEMO\r_bsp","C:\Users\Alex\Desktop\DEMO\r_riic_rx600","C:\Users\Alex\Desktop\DEMO\r_riic_rx600\src","C:\Users\Alex\Desktop\DEMO\r_glyph","C:\Users\Alex\Desktop\DEMO\r_glyph\src","C:\Users\Alex\Desktop\DEMO\r_glyph\src\glyph","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600","C:\Users\Alex\Desktop\DEMO\r_rspi_rx600\src","C:\Users\Alex\Desktop\DEMO\src","C:\Program Files (x86)\Renesas\RX\2_7_0\include" -define=__RX -lang=c99 -nomessage -output=obj -obj_path="r_bsp/board/rdkrx63n" -debug -nologo -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

r_bsp/board/rdkrx63n/%.obj: ../r_bsp/board/rdkrx63n/%.src 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	asrx -MM -MP -MF"$(@:%.obj=%.d)" -MT"$(@:%.d=%.obj)" -MT"$(@:%.obj=%.d)" -cpu=rx600 -fpu -debug -nologo -nologo  "$<"
	asrx -cpu=rx600 -fpu -output="$(@:%.d=%.obj)" -debug -nologo -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

