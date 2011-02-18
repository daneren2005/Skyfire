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
	${OBJECTDIR}/Thread.o \
	${OBJECTDIR}/Triangle.o \
	${OBJECTDIR}/StaticObject.o \
	${OBJECTDIR}/Input.o \
	${OBJECTDIR}/Matrix4.o \
	${OBJECTDIR}/Universe.o \
	${OBJECTDIR}/Rate.o \
	${OBJECTDIR}/BaseObject.o \
	${OBJECTDIR}/Window.o \
	${OBJECTDIR}/FileDirectory.o \
	${OBJECTDIR}/Rectangle3.o \
	${OBJECTDIR}/Rectangle2.o \
	${OBJECTDIR}/AxisObject.o \
	${OBJECTDIR}/Particle.o \
	${OBJECTDIR}/StopWatch.o \
	${OBJECTDIR}/Camera.o \
	${OBJECTDIR}/Model.o \
	${OBJECTDIR}/Mesh.o \
	${OBJECTDIR}/Key.o \
	${OBJECTDIR}/Scene.o \
	${OBJECTDIR}/Vector.o \
	${OBJECTDIR}/ParticleEmitter.o \
	${OBJECTDIR}/CString.o \
	${OBJECTDIR}/ParticleSystem.o \
	${OBJECTDIR}/AnimateObject.o \
	${OBJECTDIR}/File.o \
	${OBJECTDIR}/Matrix.o \
	${OBJECTDIR}/Quaternion.o \
	${OBJECTDIR}/Region.o \
	${OBJECTDIR}/ModelManager.o \
	${OBJECTDIR}/Console.o

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

${OBJECTDIR}/Thread.o: nbproject/Makefile-${CND_CONF}.mk Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Thread.o Thread.cpp

${OBJECTDIR}/Triangle.o: nbproject/Makefile-${CND_CONF}.mk Triangle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Triangle.o Triangle.cpp

${OBJECTDIR}/StaticObject.o: nbproject/Makefile-${CND_CONF}.mk StaticObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/StaticObject.o StaticObject.cpp

${OBJECTDIR}/Input.o: nbproject/Makefile-${CND_CONF}.mk Input.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input.o Input.cpp

${OBJECTDIR}/Matrix4.o: nbproject/Makefile-${CND_CONF}.mk Matrix4.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Matrix4.o Matrix4.cpp

${OBJECTDIR}/Universe.o: nbproject/Makefile-${CND_CONF}.mk Universe.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Universe.o Universe.cpp

${OBJECTDIR}/Rate.o: nbproject/Makefile-${CND_CONF}.mk Rate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Rate.o Rate.cpp

${OBJECTDIR}/BaseObject.o: nbproject/Makefile-${CND_CONF}.mk BaseObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BaseObject.o BaseObject.cpp

${OBJECTDIR}/Window.o: nbproject/Makefile-${CND_CONF}.mk Window.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Window.o Window.cpp

${OBJECTDIR}/FileDirectory.o: nbproject/Makefile-${CND_CONF}.mk FileDirectory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FileDirectory.o FileDirectory.cpp

${OBJECTDIR}/Rectangle3.o: nbproject/Makefile-${CND_CONF}.mk Rectangle3.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Rectangle3.o Rectangle3.cpp

${OBJECTDIR}/Rectangle2.o: nbproject/Makefile-${CND_CONF}.mk Rectangle2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Rectangle2.o Rectangle2.cpp

${OBJECTDIR}/AxisObject.o: nbproject/Makefile-${CND_CONF}.mk AxisObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AxisObject.o AxisObject.cpp

${OBJECTDIR}/Particle.o: nbproject/Makefile-${CND_CONF}.mk Particle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Particle.o Particle.cpp

${OBJECTDIR}/StopWatch.o: nbproject/Makefile-${CND_CONF}.mk StopWatch.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/StopWatch.o StopWatch.cpp

${OBJECTDIR}/Camera.o: nbproject/Makefile-${CND_CONF}.mk Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Camera.o Camera.cpp

${OBJECTDIR}/Model.o: nbproject/Makefile-${CND_CONF}.mk Model.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Model.o Model.cpp

${OBJECTDIR}/Mesh.o: nbproject/Makefile-${CND_CONF}.mk Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Mesh.o Mesh.cpp

${OBJECTDIR}/Key.o: nbproject/Makefile-${CND_CONF}.mk Key.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Key.o Key.cpp

${OBJECTDIR}/Scene.o: nbproject/Makefile-${CND_CONF}.mk Scene.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Scene.o Scene.cpp

${OBJECTDIR}/Vector.o: nbproject/Makefile-${CND_CONF}.mk Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Vector.o Vector.cpp

${OBJECTDIR}/ParticleEmitter.o: nbproject/Makefile-${CND_CONF}.mk ParticleEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ParticleEmitter.o ParticleEmitter.cpp

${OBJECTDIR}/CString.o: nbproject/Makefile-${CND_CONF}.mk CString.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CString.o CString.cpp

${OBJECTDIR}/ParticleSystem.o: nbproject/Makefile-${CND_CONF}.mk ParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ParticleSystem.o ParticleSystem.cpp

${OBJECTDIR}/AnimateObject.o: nbproject/Makefile-${CND_CONF}.mk AnimateObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AnimateObject.o AnimateObject.cpp

${OBJECTDIR}/File.o: nbproject/Makefile-${CND_CONF}.mk File.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/File.o File.cpp

${OBJECTDIR}/Matrix.o: nbproject/Makefile-${CND_CONF}.mk Matrix.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Matrix.o Matrix.cpp

${OBJECTDIR}/Quaternion.o: nbproject/Makefile-${CND_CONF}.mk Quaternion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Quaternion.o Quaternion.cpp

${OBJECTDIR}/Region.o: nbproject/Makefile-${CND_CONF}.mk Region.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Region.o Region.cpp

${OBJECTDIR}/ModelManager.o: nbproject/Makefile-${CND_CONF}.mk ModelManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ModelManager.o ModelManager.cpp

${OBJECTDIR}/Console.o: nbproject/Makefile-${CND_CONF}.mk Console.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Console.o Console.cpp

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
