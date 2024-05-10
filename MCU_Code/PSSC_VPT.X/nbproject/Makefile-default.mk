#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Application/ADCRead/ADCRead.c Application/Alarm/Alarm.c Application/Error/Error.c Application/Events/Events.c Application/PistonEncoder/PistonEncoder.c Application/PistonMotor/PistonMotor.c Application/Scheduler/Scheduler.c Application/Serial/Serial.c Application/SerialDebug/SerialDebug.c Application/ShakerMotor/ShakerMotor.c Application/TECControl.c Application/TemperatureControl/TemperatureControl.c Application/Timers/Timers.c Application/ValveMotor/ValveMotor.c mcc_generated_files/reset.c mcc_generated_files/system.c mcc_generated_files/pwm.c mcc_generated_files/clock.c mcc_generated_files/adc1.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/traps.c mcc_generated_files/uart1.c mcc_generated_files/spi1.c mcc_generated_files/sccp4_capture.c mcc_generated_files/sccp3_capture.c mcc_generated_files/tmr1.c mcc_generated_files/uart2.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Application/ADCRead/ADCRead.o ${OBJECTDIR}/Application/Alarm/Alarm.o ${OBJECTDIR}/Application/Error/Error.o ${OBJECTDIR}/Application/Events/Events.o ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o ${OBJECTDIR}/Application/Scheduler/Scheduler.o ${OBJECTDIR}/Application/Serial/Serial.o ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o ${OBJECTDIR}/Application/TECControl.o ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o ${OBJECTDIR}/Application/Timers/Timers.o ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o ${OBJECTDIR}/mcc_generated_files/reset.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/pwm.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/spi1.o ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Application/ADCRead/ADCRead.o.d ${OBJECTDIR}/Application/Alarm/Alarm.o.d ${OBJECTDIR}/Application/Error/Error.o.d ${OBJECTDIR}/Application/Events/Events.o.d ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o.d ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o.d ${OBJECTDIR}/Application/Scheduler/Scheduler.o.d ${OBJECTDIR}/Application/Serial/Serial.o.d ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o.d ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o.d ${OBJECTDIR}/Application/TECControl.o.d ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o.d ${OBJECTDIR}/Application/Timers/Timers.o.d ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o.d ${OBJECTDIR}/mcc_generated_files/reset.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/pwm.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/adc1.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/traps.o.d ${OBJECTDIR}/mcc_generated_files/uart1.o.d ${OBJECTDIR}/mcc_generated_files/spi1.o.d ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o.d ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/mcc_generated_files/uart2.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Application/ADCRead/ADCRead.o ${OBJECTDIR}/Application/Alarm/Alarm.o ${OBJECTDIR}/Application/Error/Error.o ${OBJECTDIR}/Application/Events/Events.o ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o ${OBJECTDIR}/Application/Scheduler/Scheduler.o ${OBJECTDIR}/Application/Serial/Serial.o ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o ${OBJECTDIR}/Application/TECControl.o ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o ${OBJECTDIR}/Application/Timers/Timers.o ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o ${OBJECTDIR}/mcc_generated_files/reset.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/pwm.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/spi1.o ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=Application/ADCRead/ADCRead.c Application/Alarm/Alarm.c Application/Error/Error.c Application/Events/Events.c Application/PistonEncoder/PistonEncoder.c Application/PistonMotor/PistonMotor.c Application/Scheduler/Scheduler.c Application/Serial/Serial.c Application/SerialDebug/SerialDebug.c Application/ShakerMotor/ShakerMotor.c Application/TECControl.c Application/TemperatureControl/TemperatureControl.c Application/Timers/Timers.c Application/ValveMotor/ValveMotor.c mcc_generated_files/reset.c mcc_generated_files/system.c mcc_generated_files/pwm.c mcc_generated_files/clock.c mcc_generated_files/adc1.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/traps.c mcc_generated_files/uart1.c mcc_generated_files/spi1.c mcc_generated_files/sccp4_capture.c mcc_generated_files/sccp3_capture.c mcc_generated_files/tmr1.c mcc_generated_files/uart2.c main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33CK128MP206
MP_LINKER_FILE_OPTION=,--script=p33CK128MP206.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Application/ADCRead/ADCRead.o: Application/ADCRead/ADCRead.c  .generated_files/flags/default/b9e7dd80839e051ee6fc874224289a9e091e7015 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ADCRead" 
	@${RM} ${OBJECTDIR}/Application/ADCRead/ADCRead.o.d 
	@${RM} ${OBJECTDIR}/Application/ADCRead/ADCRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ADCRead/ADCRead.c  -o ${OBJECTDIR}/Application/ADCRead/ADCRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ADCRead/ADCRead.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Alarm/Alarm.o: Application/Alarm/Alarm.c  .generated_files/flags/default/8a9fe8a183fcc0ea57751865128433d550fd6e3f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Alarm" 
	@${RM} ${OBJECTDIR}/Application/Alarm/Alarm.o.d 
	@${RM} ${OBJECTDIR}/Application/Alarm/Alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Alarm/Alarm.c  -o ${OBJECTDIR}/Application/Alarm/Alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Alarm/Alarm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Error/Error.o: Application/Error/Error.c  .generated_files/flags/default/8c5431de18cf9054eabc139b07479402eb04a362 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Error" 
	@${RM} ${OBJECTDIR}/Application/Error/Error.o.d 
	@${RM} ${OBJECTDIR}/Application/Error/Error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Error/Error.c  -o ${OBJECTDIR}/Application/Error/Error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Error/Error.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Events/Events.o: Application/Events/Events.c  .generated_files/flags/default/ae39003e03e40d3c67eaa78fbf00709f85250fa8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Events" 
	@${RM} ${OBJECTDIR}/Application/Events/Events.o.d 
	@${RM} ${OBJECTDIR}/Application/Events/Events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Events/Events.c  -o ${OBJECTDIR}/Application/Events/Events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Events/Events.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o: Application/PistonEncoder/PistonEncoder.c  .generated_files/flags/default/c2051591a70ff8fc5506109f785ecc338a6029c9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/PistonEncoder" 
	@${RM} ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o.d 
	@${RM} ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/PistonEncoder/PistonEncoder.c  -o ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/PistonMotor/PistonMotor.o: Application/PistonMotor/PistonMotor.c  .generated_files/flags/default/c2d34dc0b48bcb562afae5ac517600ffa7a630f5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/PistonMotor" 
	@${RM} ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/PistonMotor/PistonMotor.c  -o ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/PistonMotor/PistonMotor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Scheduler/Scheduler.o: Application/Scheduler/Scheduler.c  .generated_files/flags/default/b4df96e5e497e189e9c38f0216acaecd2ae75fc6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Scheduler" 
	@${RM} ${OBJECTDIR}/Application/Scheduler/Scheduler.o.d 
	@${RM} ${OBJECTDIR}/Application/Scheduler/Scheduler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Scheduler/Scheduler.c  -o ${OBJECTDIR}/Application/Scheduler/Scheduler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Scheduler/Scheduler.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Serial/Serial.o: Application/Serial/Serial.c  .generated_files/flags/default/53e4b5dd12e33f16a21147ac74cf168a785b5ef7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Serial" 
	@${RM} ${OBJECTDIR}/Application/Serial/Serial.o.d 
	@${RM} ${OBJECTDIR}/Application/Serial/Serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Serial/Serial.c  -o ${OBJECTDIR}/Application/Serial/Serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Serial/Serial.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/SerialDebug/SerialDebug.o: Application/SerialDebug/SerialDebug.c  .generated_files/flags/default/5ce5327f6f067fa94e62721465cf457f03b13bf6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/SerialDebug" 
	@${RM} ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o.d 
	@${RM} ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/SerialDebug/SerialDebug.c  -o ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/SerialDebug/SerialDebug.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o: Application/ShakerMotor/ShakerMotor.c  .generated_files/flags/default/9f71fed709a867285adae573dc51de2c386ac56f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ShakerMotor" 
	@${RM} ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ShakerMotor/ShakerMotor.c  -o ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/TECControl.o: Application/TECControl.c  .generated_files/flags/default/bbeda1c646172e716dfbae6b0a6eab1802064fe0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application" 
	@${RM} ${OBJECTDIR}/Application/TECControl.o.d 
	@${RM} ${OBJECTDIR}/Application/TECControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/TECControl.c  -o ${OBJECTDIR}/Application/TECControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/TECControl.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o: Application/TemperatureControl/TemperatureControl.c  .generated_files/flags/default/72dcf8321b2d879f29e0be7ec39fc4adf4d2197a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/TemperatureControl" 
	@${RM} ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o.d 
	@${RM} ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/TemperatureControl/TemperatureControl.c  -o ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Timers/Timers.o: Application/Timers/Timers.c  .generated_files/flags/default/f6432ef032fb61b496c32709ee9ce8a66bf317f7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Timers" 
	@${RM} ${OBJECTDIR}/Application/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Application/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Timers/Timers.c  -o ${OBJECTDIR}/Application/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Timers/Timers.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ValveMotor/ValveMotor.o: Application/ValveMotor/ValveMotor.c  .generated_files/flags/default/20dcf66fbf58ced16224801cf09d5a106037dc5f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ValveMotor" 
	@${RM} ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ValveMotor/ValveMotor.c  -o ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ValveMotor/ValveMotor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/reset.o: mcc_generated_files/reset.c  .generated_files/flags/default/a2b0cfef75a10e0aab53140256fe434cad5d4cf7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/reset.c  -o ${OBJECTDIR}/mcc_generated_files/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/reset.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/7ce2ac1480f5dec282caf4c2eaed4bfe37987f27 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pwm.o: mcc_generated_files/pwm.c  .generated_files/flags/default/48a08e96ace79fb1502180ed7b14d8b15eaa4c90 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pwm.c  -o ${OBJECTDIR}/mcc_generated_files/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pwm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/e7f3458d4b4aff180e641e6d20c615747f8f3293 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/flags/default/b90f8376283a3d09f9ec0daa8a9d7835d3095e96 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/2824209a762d37c4cfeaf39bee785e6caee6ef56 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/ff77e505f43830620df9cc3bfcb507c477b09d43 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/37b5367c3cdd89e49878af0df41694f66ec143bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/ab9a40904a30d972b9f7bf5b3c439784d97d4e60 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/flags/default/6bcb46af7971f99ddbcd75d7c463b748080633e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi1.o: mcc_generated_files/spi1.c  .generated_files/flags/default/8906ca1d71b2981237d2d199343b8e969373f8e0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi1.c  -o ${OBJECTDIR}/mcc_generated_files/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp4_capture.o: mcc_generated_files/sccp4_capture.c  .generated_files/flags/default/87202aea4b8c3db87d8721f8749d371feeb720c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp4_capture.c  -o ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp4_capture.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp3_capture.o: mcc_generated_files/sccp3_capture.c  .generated_files/flags/default/ee6306893cdecc32d1a968f4262dfe62969d729b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp3_capture.c  -o ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp3_capture.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/flags/default/5464dffeecbcc6aaf47e87242290ce1b671057f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/flags/default/324ee91e548bcabcd959b182024c3afdc062f26e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart2.c  -o ${OBJECTDIR}/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/f38027f7c98eba20ae427fa5a4172b3b7b3ac351 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/Application/ADCRead/ADCRead.o: Application/ADCRead/ADCRead.c  .generated_files/flags/default/9953da99d74d7c64d138716a9ccb7c716b0d16e6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ADCRead" 
	@${RM} ${OBJECTDIR}/Application/ADCRead/ADCRead.o.d 
	@${RM} ${OBJECTDIR}/Application/ADCRead/ADCRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ADCRead/ADCRead.c  -o ${OBJECTDIR}/Application/ADCRead/ADCRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ADCRead/ADCRead.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Alarm/Alarm.o: Application/Alarm/Alarm.c  .generated_files/flags/default/fa4388451cd7bf9f71459a73ebd6fa3fa5e3fa14 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Alarm" 
	@${RM} ${OBJECTDIR}/Application/Alarm/Alarm.o.d 
	@${RM} ${OBJECTDIR}/Application/Alarm/Alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Alarm/Alarm.c  -o ${OBJECTDIR}/Application/Alarm/Alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Alarm/Alarm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Error/Error.o: Application/Error/Error.c  .generated_files/flags/default/e5954fd01665a6a58e0e0812263ffa87a9c154e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Error" 
	@${RM} ${OBJECTDIR}/Application/Error/Error.o.d 
	@${RM} ${OBJECTDIR}/Application/Error/Error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Error/Error.c  -o ${OBJECTDIR}/Application/Error/Error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Error/Error.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Events/Events.o: Application/Events/Events.c  .generated_files/flags/default/c02b74c81d8a7976815417a3fd17a17e9cc1e36c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Events" 
	@${RM} ${OBJECTDIR}/Application/Events/Events.o.d 
	@${RM} ${OBJECTDIR}/Application/Events/Events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Events/Events.c  -o ${OBJECTDIR}/Application/Events/Events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Events/Events.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o: Application/PistonEncoder/PistonEncoder.c  .generated_files/flags/default/1eb619c62b969b69a66921d1032012e5528b034d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/PistonEncoder" 
	@${RM} ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o.d 
	@${RM} ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/PistonEncoder/PistonEncoder.c  -o ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/PistonMotor/PistonMotor.o: Application/PistonMotor/PistonMotor.c  .generated_files/flags/default/b2cd11c214c661845f77cecd7e2f4917e8105061 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/PistonMotor" 
	@${RM} ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/PistonMotor/PistonMotor.c  -o ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/PistonMotor/PistonMotor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Scheduler/Scheduler.o: Application/Scheduler/Scheduler.c  .generated_files/flags/default/9333f234f9815a661fd8739669b2fc525d0a7eb1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Scheduler" 
	@${RM} ${OBJECTDIR}/Application/Scheduler/Scheduler.o.d 
	@${RM} ${OBJECTDIR}/Application/Scheduler/Scheduler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Scheduler/Scheduler.c  -o ${OBJECTDIR}/Application/Scheduler/Scheduler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Scheduler/Scheduler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Serial/Serial.o: Application/Serial/Serial.c  .generated_files/flags/default/f047fd6583a1de91f54eb08827c4b64c48491f51 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Serial" 
	@${RM} ${OBJECTDIR}/Application/Serial/Serial.o.d 
	@${RM} ${OBJECTDIR}/Application/Serial/Serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Serial/Serial.c  -o ${OBJECTDIR}/Application/Serial/Serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Serial/Serial.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/SerialDebug/SerialDebug.o: Application/SerialDebug/SerialDebug.c  .generated_files/flags/default/867659e0fcf46cdb3e6dc049c407fc84aebf766d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/SerialDebug" 
	@${RM} ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o.d 
	@${RM} ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/SerialDebug/SerialDebug.c  -o ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/SerialDebug/SerialDebug.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o: Application/ShakerMotor/ShakerMotor.c  .generated_files/flags/default/ee1382a491c60a59719dfdbba429dd027fb047da .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ShakerMotor" 
	@${RM} ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ShakerMotor/ShakerMotor.c  -o ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/TECControl.o: Application/TECControl.c  .generated_files/flags/default/8c340297c103fb1cd707bb0aa9cab74ded94bc6f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application" 
	@${RM} ${OBJECTDIR}/Application/TECControl.o.d 
	@${RM} ${OBJECTDIR}/Application/TECControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/TECControl.c  -o ${OBJECTDIR}/Application/TECControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/TECControl.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o: Application/TemperatureControl/TemperatureControl.c  .generated_files/flags/default/a809c70ec6b49189da89dbd82d594f80aa4e83a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/TemperatureControl" 
	@${RM} ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o.d 
	@${RM} ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/TemperatureControl/TemperatureControl.c  -o ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Timers/Timers.o: Application/Timers/Timers.c  .generated_files/flags/default/d9e143ea702679fa0e760f5102f70ef66b525c15 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Timers" 
	@${RM} ${OBJECTDIR}/Application/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Application/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Timers/Timers.c  -o ${OBJECTDIR}/Application/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Timers/Timers.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ValveMotor/ValveMotor.o: Application/ValveMotor/ValveMotor.c  .generated_files/flags/default/2e9c4e62b950a99d29dde7e0cf08d68946e52498 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ValveMotor" 
	@${RM} ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ValveMotor/ValveMotor.c  -o ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ValveMotor/ValveMotor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/reset.o: mcc_generated_files/reset.c  .generated_files/flags/default/214c241d3edf81bfdd0d126f06fdff12f8ccf640 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/reset.c  -o ${OBJECTDIR}/mcc_generated_files/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/reset.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/cdd6da8b11ea788f4ffbe70487a25498d8f3c8a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pwm.o: mcc_generated_files/pwm.c  .generated_files/flags/default/4edd1ff4b67cb4e75aaae24e0f2eb1c7b714eb89 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pwm.c  -o ${OBJECTDIR}/mcc_generated_files/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pwm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/625f0a593b7592adc5c4122446a3799054710eb3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/flags/default/120cb3f511e28404825d3d5cf9ffb4d8b1b71a46 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/6179f33dd89c8649166fc2beeaced932243fd0ad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/18dc9683e1e6848f59ebc0d0a44f2b007d5b9948 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/b65cb6a8f797b60d90af495f7990dd4a20174c45 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/4a87eb163392fe0aedb0050a6343a957a20be605 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/flags/default/d3b06ac47e8db0232a6dbb6b143ae97ea6803580 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi1.o: mcc_generated_files/spi1.c  .generated_files/flags/default/3bf5ccfc0ba6be1292ae9775ee40dd5db1623c5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi1.c  -o ${OBJECTDIR}/mcc_generated_files/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp4_capture.o: mcc_generated_files/sccp4_capture.c  .generated_files/flags/default/cccd805820bf0067bb42378db311fe1163c26ff9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp4_capture.c  -o ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp4_capture.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp3_capture.o: mcc_generated_files/sccp3_capture.c  .generated_files/flags/default/7426314413bfa162d383244096c668144a154ad2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp3_capture.c  -o ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp3_capture.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/flags/default/73cc68e20839919738a7f46a784f8f71a8209708 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/flags/default/508b8c5e7e13c58f490e35bef450d07b360961f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart2.c  -o ${OBJECTDIR}/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/e3d1391d686133e0c495b45fd40dea743e396fc7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin"  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
