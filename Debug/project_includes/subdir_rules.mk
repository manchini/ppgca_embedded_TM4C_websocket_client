################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
project_includes/EK_TM4C1294XL.obj: ../project_includes/EK_TM4C1294XL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --opt_for_speed=0 --include_path="C:/ti/CMSIS-SP-00300-r4p5-00rel0/CMSIS/Include" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages/ti/ndk/inc/bsd" --include_path="D:/manchini/projetos/ppgca_embedded_TM4C_websocket_client" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --define=ccs="ccs" --define=ccs --define=PART_TM4C1294NCPDT --define=TIVAWARE --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="project_includes/EK_TM4C1294XL.d" --obj_directory="project_includes" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

project_includes/adc_sample.obj: ../project_includes/adc_sample.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --opt_for_speed=0 --include_path="C:/ti/CMSIS-SP-00300-r4p5-00rel0/CMSIS/Include" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages/ti/ndk/inc/bsd" --include_path="D:/manchini/projetos/ppgca_embedded_TM4C_websocket_client" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --define=ccs="ccs" --define=ccs --define=PART_TM4C1294NCPDT --define=TIVAWARE --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="project_includes/adc_sample.d" --obj_directory="project_includes" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

project_includes/eth_network.obj: ../project_includes/eth_network.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --opt_for_speed=0 --include_path="C:/ti/CMSIS-SP-00300-r4p5-00rel0/CMSIS/Include" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages/ti/ndk/inc/bsd" --include_path="D:/manchini/projetos/ppgca_embedded_TM4C_websocket_client" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --define=ccs="ccs" --define=ccs --define=PART_TM4C1294NCPDT --define=TIVAWARE --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="project_includes/eth_network.d" --obj_directory="project_includes" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


