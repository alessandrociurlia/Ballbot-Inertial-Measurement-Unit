################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.bls *.libelf *.rel *.lbk *.abs  *.obj *.p *.pp *.d *.asm 1st/*.obj 1st/*.d 1st/*.asm 1st/*.abs

# All of the sources participating in the build are defined here
-include sources.mk
-include r_glyph/src/glyph/drivers/subdir.mk
-include r_riic_rx600/src/subdir.mk
-include r_glyph/src/glyph/fonts/subdir.mk
-include r_bsp/board/rdkrx63n/subdir.mk
-include r_glyph/src/subdir.mk
-include r_rspi_rx600/src/subdir.mk
-include r_glyph/src/glyph/subdir.mk
-include src/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
ADC_OneShot.abs

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
ADC_OneShot.lib

CONVERTOR_OUTPUT_OUTPUTS += \
ADC_OneShot.mot \
ADC_OneShot.x

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

# All Target
all: $(CONVERTOR_OUTPUT_OUTPUTS) 
	@echo 'Build complete.'

ADC_OneShot.mot: $(LINKER_OUTPUT_OUTPUTS) 
	@echo 'Invoking: Converter'
	@echo 'Building target:'
	rlink "ADC_OneShot.abs" -form=stype -output="ADC_OneShot.mot" -nologo -nomessage -nomessage
	@echo 'Finished building target:'
	@echo.


ADC_OneShot.abs: $(OBJS)  $(ALL_ASMS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) 
	@echo 'Invoking: Linker'
	rlink -noprelink -subcommand="LinkerSubCommand.tmp"  -output="ADC_OneShot.abs" -form=absolute -nomessage -list=ADC_OneShot.map -nooptimize -nologo -nologo -nomessage -rom=D=R,D_1=R_1,D_2=R_2 -vect=_undefined_interrupt_source_isr
	@echo 'Finished building:'
	@echo.


ADC_OneShot.lib: 
	@echo 'Invoking: Library Generator'
	lbgrx -cpu=rx600 -fpu -lang=c99 -head=runtime,math,mathf,stdio,stdlib -output="ADC_OneShot.lib" -nologo
	@echo 'Finished building:'
	@echo.

ADC_OneShot.x: ADC_OneShot.abs
		-C:\Renesas\e2_studio\eclipse\/../\Utilities\\ccrx\renesas_cc_converter.exe ADC_OneShot.abs ADC_OneShot.x

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS)
	-rm -rf r_glyph/src/glyph/drivers/*.obj r_glyph/src/glyph/drivers/*.d r_glyph/src/glyph/drivers/*.asm r_glyph/src/glyph/drivers/*.p r_glyph/src/glyph/drivers/*.src r_glyph/src/glyph/drivers/*.jmp r_glyph/src/glyph/drivers/*.lst r_glyph/src/glyph/drivers/*.prn 
	-rm -rf r_riic_rx600/src/*.obj r_riic_rx600/src/*.d r_riic_rx600/src/*.asm r_riic_rx600/src/*.p r_riic_rx600/src/*.src r_riic_rx600/src/*.jmp r_riic_rx600/src/*.lst r_riic_rx600/src/*.prn 
	-rm -rf r_glyph/src/glyph/fonts/*.obj r_glyph/src/glyph/fonts/*.d r_glyph/src/glyph/fonts/*.asm r_glyph/src/glyph/fonts/*.p r_glyph/src/glyph/fonts/*.src r_glyph/src/glyph/fonts/*.jmp r_glyph/src/glyph/fonts/*.lst r_glyph/src/glyph/fonts/*.prn 
	-rm -rf r_bsp/board/rdkrx63n/*.obj r_bsp/board/rdkrx63n/*.d r_bsp/board/rdkrx63n/*.asm r_bsp/board/rdkrx63n/*.p r_bsp/board/rdkrx63n/*.src r_bsp/board/rdkrx63n/*.jmp r_bsp/board/rdkrx63n/*.lst r_bsp/board/rdkrx63n/*.prn 
	-rm -rf r_glyph/src/*.obj r_glyph/src/*.d r_glyph/src/*.asm r_glyph/src/*.p r_glyph/src/*.src r_glyph/src/*.jmp r_glyph/src/*.lst r_glyph/src/*.prn 
	-rm -rf r_rspi_rx600/src/*.obj r_rspi_rx600/src/*.d r_rspi_rx600/src/*.asm r_rspi_rx600/src/*.p r_rspi_rx600/src/*.src r_rspi_rx600/src/*.jmp r_rspi_rx600/src/*.lst r_rspi_rx600/src/*.prn 
	-rm -rf r_glyph/src/glyph/*.obj r_glyph/src/glyph/*.d r_glyph/src/glyph/*.asm r_glyph/src/glyph/*.p r_glyph/src/glyph/*.src r_glyph/src/glyph/*.jmp r_glyph/src/glyph/*.lst r_glyph/src/glyph/*.prn 
	-rm -rf src/*.obj src/*.d src/*.asm src/*.p src/*.src src/*.jmp src/*.lst src/*.prn 
	@echo
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets