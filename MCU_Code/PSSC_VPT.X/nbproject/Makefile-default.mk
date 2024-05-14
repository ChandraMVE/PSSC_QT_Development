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
${OBJECTDIR}/Application/ADCRead/ADCRead.o: Application/ADCRead/ADCRead.c  .generated_files/flags/default/68ea8ccef04a02f30fff472cfa0f11dea95616d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ADCRead" 
	@${RM} ${OBJECTDIR}/Application/ADCRead/ADCRead.o.d 
	@${RM} ${OBJECTDIR}/Application/ADCRead/ADCRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ADCRead/ADCRead.c  -o ${OBJECTDIR}/Application/ADCRead/ADCRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ADCRead/ADCRead.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Alarm/Alarm.o: Application/Alarm/Alarm.c  .generated_files/flags/default/952fdf98beedd5e37b175753be34e2a07e41df08 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Alarm" 
	@${RM} ${OBJECTDIR}/Application/Alarm/Alarm.o.d 
	@${RM} ${OBJECTDIR}/Application/Alarm/Alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Alarm/Alarm.c  -o ${OBJECTDIR}/Application/Alarm/Alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Alarm/Alarm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Error/Error.o: Application/Error/Error.c  .generated_files/flags/default/8c5b0121a84451931efc708123ba43b63369df43 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Error" 
	@${RM} ${OBJECTDIR}/Application/Error/Error.o.d 
	@${RM} ${OBJECTDIR}/Application/Error/Error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Error/Error.c  -o ${OBJECTDIR}/Application/Error/Error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Error/Error.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Events/Events.o: Application/Events/Events.c  .generated_files/flags/default/db20bf13795f5ed4cbaf19a6b33df8a4bda21697 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Events" 
	@${RM} ${OBJECTDIR}/Application/Events/Events.o.d 
	@${RM} ${OBJECTDIR}/Application/Events/Events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Events/Events.c  -o ${OBJECTDIR}/Application/Events/Events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Events/Events.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o: Application/PistonEncoder/PistonEncoder.c  .generated_files/flags/default/adf0f4c93aed13d3de6d9601e3bcb395b5d1da84 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/PistonEncoder" 
	@${RM} ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o.d 
	@${RM} ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/PistonEncoder/PistonEncoder.c  -o ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/PistonMotor/PistonMotor.o: Application/PistonMotor/PistonMotor.c  .generated_files/flags/default/37a5b1b2f0ef8ff1d4f88a0cf3450f6a5ee914af .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/PistonMotor" 
	@${RM} ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/PistonMotor/PistonMotor.c  -o ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/PistonMotor/PistonMotor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Scheduler/Scheduler.o: Application/Scheduler/Scheduler.c  .generated_files/flags/default/3df434a872d6a9381abe3d394fa00bd11511576d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Scheduler" 
	@${RM} ${OBJECTDIR}/Application/Scheduler/Scheduler.o.d 
	@${RM} ${OBJECTDIR}/Application/Scheduler/Scheduler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Scheduler/Scheduler.c  -o ${OBJECTDIR}/Application/Scheduler/Scheduler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Scheduler/Scheduler.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Serial/Serial.o: Application/Serial/Serial.c  .generated_files/flags/default/adf6f52ba3c78ce8ea26a4ff2518488fd0acb42d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Serial" 
	@${RM} ${OBJECTDIR}/Application/Serial/Serial.o.d 
	@${RM} ${OBJECTDIR}/Application/Serial/Serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Serial/Serial.c  -o ${OBJECTDIR}/Application/Serial/Serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Serial/Serial.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/SerialDebug/SerialDebug.o: Application/SerialDebug/SerialDebug.c  .generated_files/flags/default/614d7043b9d0a8b1807081b62ae0362b64815e43 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/SerialDebug" 
	@${RM} ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o.d 
	@${RM} ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/SerialDebug/SerialDebug.c  -o ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/SerialDebug/SerialDebug.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o: Application/ShakerMotor/ShakerMotor.c  .generated_files/flags/default/6da5253d012e87afcfc8101059c4b193e9d7edec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ShakerMotor" 
	@${RM} ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ShakerMotor/ShakerMotor.c  -o ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/TECControl.o: Application/TECControl.c  .generated_files/flags/default/ce7ae75103329711d9a53c62852d1490a01a3e4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application" 
	@${RM} ${OBJECTDIR}/Application/TECControl.o.d 
	@${RM} ${OBJECTDIR}/Application/TECControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/TECControl.c  -o ${OBJECTDIR}/Application/TECControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/TECControl.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o: Application/TemperatureControl/TemperatureControl.c  .generated_files/flags/default/ab4ed83a4cb09ec5f8558bca0bf78979a733d4b5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/TemperatureControl" 
	@${RM} ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o.d 
	@${RM} ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/TemperatureControl/TemperatureControl.c  -o ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Timers/Timers.o: Application/Timers/Timers.c  .generated_files/flags/default/720d180e6439955d3afee42484a5d9b0c6b6e054 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Timers" 
	@${RM} ${OBJECTDIR}/Application/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Application/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Timers/Timers.c  -o ${OBJECTDIR}/Application/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Timers/Timers.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ValveMotor/ValveMotor.o: Application/ValveMotor/ValveMotor.c  .generated_files/flags/default/2b4cdf5fe53618a65d61b11406817304e6f1b6ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ValveMotor" 
	@${RM} ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ValveMotor/ValveMotor.c  -o ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ValveMotor/ValveMotor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/reset.o: mcc_generated_files/reset.c  .generated_files/flags/default/628f99f1fbdb8ac77a3cd63b945ea1c5e9440a17 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/reset.c  -o ${OBJECTDIR}/mcc_generated_files/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/reset.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/93a7686e9589932c85f253c4e51a9e984afe0457 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pwm.o: mcc_generated_files/pwm.c  .generated_files/flags/default/a2afc1e3025b93ade19c3ec28314d6e0580f512e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pwm.c  -o ${OBJECTDIR}/mcc_generated_files/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pwm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/3cfd8d4766734c29b1c4f4dfc72769a2e747ff56 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/flags/default/4c3ad4e5775d3d690458d2be6b0e200f17ad6adf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/fa2d1ca75af7a0eec4af97b93d2059d23be79445 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/86f976d1d5ff91abc0134b2e2df93e6faa33988e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/b12839879921024d7ccd85eb9a094400c3410873 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/93013796a5b3868324779eb995eed4a2b89e213e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/flags/default/f3e1ccddbdcd6805985819b43d207e94e1a59916 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi1.o: mcc_generated_files/spi1.c  .generated_files/flags/default/fa8bbbb1b5408a9316f0a12e1c8d15c0ae13d1e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi1.c  -o ${OBJECTDIR}/mcc_generated_files/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp4_capture.o: mcc_generated_files/sccp4_capture.c  .generated_files/flags/default/a22dc1abc5ce618b9b614fcd4b673187febbbdbf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp4_capture.c  -o ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp4_capture.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp3_capture.o: mcc_generated_files/sccp3_capture.c  .generated_files/flags/default/1dad59b267a2683c8c5e7719cf619f1b0631a2a1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp3_capture.c  -o ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp3_capture.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/flags/default/678a24645412eea479150fc06acfc336f647101c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/flags/default/84167836bc3ca1091a6e9e837786ed917e9b6565 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart2.c  -o ${OBJECTDIR}/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/10e8cdf5633d6953de7f77d712f5dc2aff25f35b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/Application/ADCRead/ADCRead.o: Application/ADCRead/ADCRead.c  .generated_files/flags/default/605b4cb35a40590a81bb0400cd2698df396e8b06 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ADCRead" 
	@${RM} ${OBJECTDIR}/Application/ADCRead/ADCRead.o.d 
	@${RM} ${OBJECTDIR}/Application/ADCRead/ADCRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ADCRead/ADCRead.c  -o ${OBJECTDIR}/Application/ADCRead/ADCRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ADCRead/ADCRead.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Alarm/Alarm.o: Application/Alarm/Alarm.c  .generated_files/flags/default/81778d8d7c0020942e422d69ee89a76779fb7421 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Alarm" 
	@${RM} ${OBJECTDIR}/Application/Alarm/Alarm.o.d 
	@${RM} ${OBJECTDIR}/Application/Alarm/Alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Alarm/Alarm.c  -o ${OBJECTDIR}/Application/Alarm/Alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Alarm/Alarm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Error/Error.o: Application/Error/Error.c  .generated_files/flags/default/9408efa29ebb3f5e077f1b1c7b91f2b670871c12 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Error" 
	@${RM} ${OBJECTDIR}/Application/Error/Error.o.d 
	@${RM} ${OBJECTDIR}/Application/Error/Error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Error/Error.c  -o ${OBJECTDIR}/Application/Error/Error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Error/Error.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Events/Events.o: Application/Events/Events.c  .generated_files/flags/default/d2bc3d6bee632cc82e4967c26a5422cfab3e84f2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Events" 
	@${RM} ${OBJECTDIR}/Application/Events/Events.o.d 
	@${RM} ${OBJECTDIR}/Application/Events/Events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Events/Events.c  -o ${OBJECTDIR}/Application/Events/Events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Events/Events.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o: Application/PistonEncoder/PistonEncoder.c  .generated_files/flags/default/442abe588c3f2b227a128eb4172e662159580ac3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/PistonEncoder" 
	@${RM} ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o.d 
	@${RM} ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/PistonEncoder/PistonEncoder.c  -o ${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/PistonEncoder/PistonEncoder.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/PistonMotor/PistonMotor.o: Application/PistonMotor/PistonMotor.c  .generated_files/flags/default/786301bf0bf234589d86fe0bed8d82942b8897e1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/PistonMotor" 
	@${RM} ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/PistonMotor/PistonMotor.c  -o ${OBJECTDIR}/Application/PistonMotor/PistonMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/PistonMotor/PistonMotor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Scheduler/Scheduler.o: Application/Scheduler/Scheduler.c  .generated_files/flags/default/c0c8de92688198552088421dbc5ab46bba9d97fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Scheduler" 
	@${RM} ${OBJECTDIR}/Application/Scheduler/Scheduler.o.d 
	@${RM} ${OBJECTDIR}/Application/Scheduler/Scheduler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Scheduler/Scheduler.c  -o ${OBJECTDIR}/Application/Scheduler/Scheduler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Scheduler/Scheduler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Serial/Serial.o: Application/Serial/Serial.c  .generated_files/flags/default/600db5e850b39615cf9e4c92ebbc042a9c9d151d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Serial" 
	@${RM} ${OBJECTDIR}/Application/Serial/Serial.o.d 
	@${RM} ${OBJECTDIR}/Application/Serial/Serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Serial/Serial.c  -o ${OBJECTDIR}/Application/Serial/Serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Serial/Serial.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/SerialDebug/SerialDebug.o: Application/SerialDebug/SerialDebug.c  .generated_files/flags/default/440be259f5ed8385ed06136601156638260f3f19 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/SerialDebug" 
	@${RM} ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o.d 
	@${RM} ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/SerialDebug/SerialDebug.c  -o ${OBJECTDIR}/Application/SerialDebug/SerialDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/SerialDebug/SerialDebug.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o: Application/ShakerMotor/ShakerMotor.c  .generated_files/flags/default/d6204019a63ddd23f96e188d9ef0220ffe684a34 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ShakerMotor" 
	@${RM} ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ShakerMotor/ShakerMotor.c  -o ${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ShakerMotor/ShakerMotor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/TECControl.o: Application/TECControl.c  .generated_files/flags/default/52a93a3b330d6336c1f2d93472ac736d3cba6873 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application" 
	@${RM} ${OBJECTDIR}/Application/TECControl.o.d 
	@${RM} ${OBJECTDIR}/Application/TECControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/TECControl.c  -o ${OBJECTDIR}/Application/TECControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/TECControl.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o: Application/TemperatureControl/TemperatureControl.c  .generated_files/flags/default/fc6876c306129b48e0ee8e2a3853d57b2eaf2b8a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/TemperatureControl" 
	@${RM} ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o.d 
	@${RM} ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/TemperatureControl/TemperatureControl.c  -o ${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/TemperatureControl/TemperatureControl.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/Timers/Timers.o: Application/Timers/Timers.c  .generated_files/flags/default/8e99b183999b3884a040cfcfdc81cc843ab21d25 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/Timers" 
	@${RM} ${OBJECTDIR}/Application/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Application/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/Timers/Timers.c  -o ${OBJECTDIR}/Application/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/Timers/Timers.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ValveMotor/ValveMotor.o: Application/ValveMotor/ValveMotor.c  .generated_files/flags/default/f7976e95624aa78bea4188ff5897233f7c86a427 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ValveMotor" 
	@${RM} ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o.d 
	@${RM} ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ValveMotor/ValveMotor.c  -o ${OBJECTDIR}/Application/ValveMotor/ValveMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ValveMotor/ValveMotor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/reset.o: mcc_generated_files/reset.c  .generated_files/flags/default/2f3014d16b72062abcd903662aae66838c9ed5d3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/reset.c  -o ${OBJECTDIR}/mcc_generated_files/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/reset.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/a836c2a64339303dd08ce43839709f5cd44be436 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pwm.o: mcc_generated_files/pwm.c  .generated_files/flags/default/a081ad5436a18159ba3f0554d3e9aa44309334d9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pwm.c  -o ${OBJECTDIR}/mcc_generated_files/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pwm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/68b2e11fcf738f5a94e8f88101031d71457575c9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/flags/default/23193b19b9118c9dddf1f74e82e68513898c99e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/a2a9656dc27bc951479706d1d1e8571b80231d75 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/f83172a30f054ed6d96d486133d260709da1ab76 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/3b66bd506fb3c2d6bdd77c94d66190b4ca4c415c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/db745e18341de26fbbab004e54a0abe60c165ee3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/flags/default/9d741b7ab767ea9c80cd89a60c14e32bf1c2a542 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi1.o: mcc_generated_files/spi1.c  .generated_files/flags/default/555b88b3941b13afcee5592c5add1a1594bde8f2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi1.c  -o ${OBJECTDIR}/mcc_generated_files/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp4_capture.o: mcc_generated_files/sccp4_capture.c  .generated_files/flags/default/7e258815f206603baad029bd51e12fe5fc1dc751 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp4_capture.c  -o ${OBJECTDIR}/mcc_generated_files/sccp4_capture.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp4_capture.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp3_capture.o: mcc_generated_files/sccp3_capture.c  .generated_files/flags/default/aae723d010ede8c20a35c1a62d8671b326dbc8c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp3_capture.c  -o ${OBJECTDIR}/mcc_generated_files/sccp3_capture.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp3_capture.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/flags/default/438448bc98cd167848a46a096495b1f30f4138b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/flags/default/874044b9824b5766592bef1115be7fa2f5d75dc6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart2.c  -o ${OBJECTDIR}/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/cd87c65d4ffce2438da989b5031b8453e4cf485c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -O0 -I"Application/Timers" -I"Application/Events" -I"Application/Scheduler" -I"Application/Serial" -I"../h" -I"." -I"mcc_generated_files" -I"Application/PistonMotor" -I"Application/ValveMotor" -I"Application/TECControl" -I"Application/ShakerMotor" -I"Application/TemperatureControl" -I"Application/PistonEncoder" -I"Application/Alarm" -I"Application/ADCRead" -I"Application/Error" -I"Application/SerialDebug" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin"  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/PSSC_VPT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../h" -I"." -I"../../../../Program Files/Microchip/xc16/v1.60/include" -I"../../../../Program Files/Microchip/xc16/v1.60/support/generic/h" -I"mcc_generated_files" -I"../../../../Program Files/Microchip/xc16/v1.60/support/dsPIC33C" -I"../../../../Program Files/Microchip/xc16/v1.60/bin" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
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

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
