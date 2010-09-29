#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include skyfire-Makefile.mk

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AxisObject.o \
	${OBJECTDIR}/FrameRate.o \
	${OBJECTDIR}/Thread.o \
	${OBJECTDIR}/StopWatch.o \
	${OBJECTDIR}/Camera.o \
	${OBJECTDIR}/Triangle.o \
	${OBJECTDIR}/Polygon.o \
	${OBJECTDIR}/Input.o \
	${OBJECTDIR}/Key.o \
	${OBJECTDIR}/Vector.o \
	${OBJECTDIR}/Scene.o \
	${OBJECTDIR}/Universe.o \
	${OBJECTDIR}/BaseObject.o \
	${OBJECTDIR}/Window.o \
	${OBJECTDIR}/Region.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/libskyfire.a

dist/Release/GNU-Linux-x86/libskyfire.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${RM} dist/Release/GNU-Linux-x86/libskyfire.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/GNU-Linux-x86/libskyfire.a

${OBJECTDIR}/AxisObject.o: nbproject/Makefile-${CND_CONF}.mk AxisObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AxisObject.o AxisObject.cpp

${OBJECTDIR}/FrameRate.o: nbproject/Makefile-${CND_CONF}.mk FrameRate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FrameRate.o FrameRate.cpp

${OBJECTDIR}/Thread.o: nbproject/Makefile-${CND_CONF}.mk Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Thread.o Thread.cpp

${OBJECTDIR}/StopWatch.o: nbproject/Makefile-${CND_CONF}.mk StopWatch.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/StopWatch.o StopWatch.cpp

${OBJECTDIR}/Camera.o: nbproject/Makefile-${CND_CONF}.mk Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Camera.o Camera.cpp

${OBJECTDIR}/Triangle.o: nbproject/Makefile-${CND_CONF}.mk Triangle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Triangle.o Triangle.cpp

${OBJECTDIR}/Polygon.o: nbproject/Makefile-${CND_CONF}.mk Polygon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Polygon.o Polygon.cpp

${OBJECTDIR}/Input.o: nbproject/Makefile-${CND_CONF}.mk Input.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input.o Input.cpp

${OBJECTDIR}/Key.o: nbproject/Makefile-${CND_CONF}.mk Key.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Key.o Key.cpp

${OBJECTDIR}/Vector.o: nbproject/Makefile-${CND_CONF}.mk Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Vector.o Vector.cpp

${OBJECTDIR}/Scene.o: nbproject/Makefile-${CND_CONF}.mk Scene.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Scene.o Scene.cpp

${OBJECTDIR}/Universe.o: nbproject/Makefile-${CND_CONF}.mk Universe.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Universe.o Universe.cpp

${OBJECTDIR}/BaseObject.o: nbproject/Makefile-${CND_CONF}.mk BaseObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BaseObject.o BaseObject.cpp

${OBJECTDIR}/Window.o: nbproject/Makefile-${CND_CONF}.mk Window.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Window.o Window.cpp

${OBJECTDIR}/Region.o: nbproject/Makefile-${CND_CONF}.mk Region.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Region.o Region.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/libskyfire.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
