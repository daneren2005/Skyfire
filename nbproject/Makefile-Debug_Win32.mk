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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Debug_Win32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include skyfire-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Texture.o \
	${OBJECTDIR}/ParticleSystem.o \
	${OBJECTDIR}/EventManager.o \
	${OBJECTDIR}/Matrix.o \
	${OBJECTDIR}/BaseObject.o \
	${OBJECTDIR}/FirstPersonCamera.o \
	${OBJECTDIR}/Thread.o \
	${OBJECTDIR}/EventHandler.o \
	${OBJECTDIR}/Triangle.o \
	${OBJECTDIR}/FunctionCall.o \
	${OBJECTDIR}/Label.o \
	${OBJECTDIR}/Camera.o \
	${OBJECTDIR}/SearchState.o \
	${OBJECTDIR}/Renderer.o \
	${OBJECTDIR}/File.o \
	${OBJECTDIR}/Console.o \
	${OBJECTDIR}/Universe.o \
	${OBJECTDIR}/Font2D.o \
	${OBJECTDIR}/Input.o \
	${OBJECTDIR}/Condition.o \
	${OBJECTDIR}/Window.o \
	${OBJECTDIR}/Region.o \
	${OBJECTDIR}/ObjectOrientedBox.o \
	${OBJECTDIR}/TextBox.o \
	${OBJECTDIR}/Matrix4.o \
	${OBJECTDIR}/Ray.o \
	${OBJECTDIR}/Folder.o \
	${OBJECTDIR}/ParticleEmitter.o \
	${OBJECTDIR}/GenericType.o \
	${OBJECTDIR}/Model.o \
	${OBJECTDIR}/MeshPart.o \
	${OBJECTDIR}/Particle.o \
	${OBJECTDIR}/ResourceManager.o \
	${OBJECTDIR}/Vector.o \
	${OBJECTDIR}/Event.o \
	${OBJECTDIR}/GenericPointer.o \
	${OBJECTDIR}/CString.o \
	${OBJECTDIR}/Time.o \
	${OBJECTDIR}/DataFile.o \
	${OBJECTDIR}/Lock.o \
	${OBJECTDIR}/Sphere.o \
	${OBJECTDIR}/Mesh.o \
	${OBJECTDIR}/AxisAlignedBox.o \
	${OBJECTDIR}/SearchStatePath.o \
	${OBJECTDIR}/ThreadLoop.o \
	${OBJECTDIR}/SharedLock.o \
	${OBJECTDIR}/AxisObject.o \
	${OBJECTDIR}/Rectangle.o \
	${OBJECTDIR}/Date.o \
	${OBJECTDIR}/GUI.o \
	${OBJECTDIR}/Timer.o \
	${OBJECTDIR}/Key.o \
	${OBJECTDIR}/ThirdPersonCamera.o \
	${OBJECTDIR}/Quaternion.o \
	${OBJECTDIR}/Material.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=gnu++0x
CXXFLAGS=-std=gnu++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a

${OBJECTDIR}/Texture.o: nbproject/Makefile-${CND_CONF}.mk Texture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Texture.o Texture.cpp

${OBJECTDIR}/ParticleSystem.o: nbproject/Makefile-${CND_CONF}.mk ParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/ParticleSystem.o ParticleSystem.cpp

${OBJECTDIR}/EventManager.o: nbproject/Makefile-${CND_CONF}.mk EventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/EventManager.o EventManager.cpp

${OBJECTDIR}/Matrix.o: nbproject/Makefile-${CND_CONF}.mk Matrix.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Matrix.o Matrix.cpp

${OBJECTDIR}/BaseObject.o: nbproject/Makefile-${CND_CONF}.mk BaseObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/BaseObject.o BaseObject.cpp

${OBJECTDIR}/FirstPersonCamera.o: nbproject/Makefile-${CND_CONF}.mk FirstPersonCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/FirstPersonCamera.o FirstPersonCamera.cpp

${OBJECTDIR}/Thread.o: nbproject/Makefile-${CND_CONF}.mk Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Thread.o Thread.cpp

${OBJECTDIR}/EventHandler.o: nbproject/Makefile-${CND_CONF}.mk EventHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/EventHandler.o EventHandler.cpp

${OBJECTDIR}/Triangle.o: nbproject/Makefile-${CND_CONF}.mk Triangle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Triangle.o Triangle.cpp

${OBJECTDIR}/FunctionCall.o: nbproject/Makefile-${CND_CONF}.mk FunctionCall.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/FunctionCall.o FunctionCall.cpp

${OBJECTDIR}/Label.o: nbproject/Makefile-${CND_CONF}.mk Label.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Label.o Label.cpp

${OBJECTDIR}/Camera.o: nbproject/Makefile-${CND_CONF}.mk Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Camera.o Camera.cpp

${OBJECTDIR}/SearchState.o: nbproject/Makefile-${CND_CONF}.mk SearchState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/SearchState.o SearchState.cpp

${OBJECTDIR}/Renderer.o: nbproject/Makefile-${CND_CONF}.mk Renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Renderer.o Renderer.cpp

${OBJECTDIR}/File.o: nbproject/Makefile-${CND_CONF}.mk File.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/File.o File.cpp

${OBJECTDIR}/Console.o: nbproject/Makefile-${CND_CONF}.mk Console.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Console.o Console.cpp

${OBJECTDIR}/Universe.o: nbproject/Makefile-${CND_CONF}.mk Universe.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Universe.o Universe.cpp

${OBJECTDIR}/Font2D.o: nbproject/Makefile-${CND_CONF}.mk Font2D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Font2D.o Font2D.cpp

${OBJECTDIR}/Input.o: nbproject/Makefile-${CND_CONF}.mk Input.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input.o Input.cpp

${OBJECTDIR}/Condition.o: nbproject/Makefile-${CND_CONF}.mk Condition.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Condition.o Condition.cpp

${OBJECTDIR}/Window.o: nbproject/Makefile-${CND_CONF}.mk Window.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Window.o Window.cpp

${OBJECTDIR}/Region.o: nbproject/Makefile-${CND_CONF}.mk Region.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Region.o Region.cpp

${OBJECTDIR}/ObjectOrientedBox.o: nbproject/Makefile-${CND_CONF}.mk ObjectOrientedBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/ObjectOrientedBox.o ObjectOrientedBox.cpp

${OBJECTDIR}/TextBox.o: nbproject/Makefile-${CND_CONF}.mk TextBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/TextBox.o TextBox.cpp

${OBJECTDIR}/Matrix4.o: nbproject/Makefile-${CND_CONF}.mk Matrix4.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Matrix4.o Matrix4.cpp

${OBJECTDIR}/Ray.o: nbproject/Makefile-${CND_CONF}.mk Ray.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Ray.o Ray.cpp

${OBJECTDIR}/Folder.o: nbproject/Makefile-${CND_CONF}.mk Folder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Folder.o Folder.cpp

${OBJECTDIR}/ParticleEmitter.o: nbproject/Makefile-${CND_CONF}.mk ParticleEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/ParticleEmitter.o ParticleEmitter.cpp

${OBJECTDIR}/GenericType.o: nbproject/Makefile-${CND_CONF}.mk GenericType.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/GenericType.o GenericType.cpp

${OBJECTDIR}/Model.o: nbproject/Makefile-${CND_CONF}.mk Model.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Model.o Model.cpp

${OBJECTDIR}/MeshPart.o: nbproject/Makefile-${CND_CONF}.mk MeshPart.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/MeshPart.o MeshPart.cpp

${OBJECTDIR}/Particle.o: nbproject/Makefile-${CND_CONF}.mk Particle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Particle.o Particle.cpp

${OBJECTDIR}/ResourceManager.o: nbproject/Makefile-${CND_CONF}.mk ResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/ResourceManager.o ResourceManager.cpp

${OBJECTDIR}/Vector.o: nbproject/Makefile-${CND_CONF}.mk Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Vector.o Vector.cpp

${OBJECTDIR}/Event.o: nbproject/Makefile-${CND_CONF}.mk Event.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Event.o Event.cpp

${OBJECTDIR}/GenericPointer.o: nbproject/Makefile-${CND_CONF}.mk GenericPointer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/GenericPointer.o GenericPointer.cpp

${OBJECTDIR}/CString.o: nbproject/Makefile-${CND_CONF}.mk CString.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/CString.o CString.cpp

${OBJECTDIR}/Time.o: nbproject/Makefile-${CND_CONF}.mk Time.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Time.o Time.cpp

${OBJECTDIR}/DataFile.o: nbproject/Makefile-${CND_CONF}.mk DataFile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataFile.o DataFile.cpp

${OBJECTDIR}/Lock.o: nbproject/Makefile-${CND_CONF}.mk Lock.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Lock.o Lock.cpp

${OBJECTDIR}/Sphere.o: nbproject/Makefile-${CND_CONF}.mk Sphere.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sphere.o Sphere.cpp

${OBJECTDIR}/Mesh.o: nbproject/Makefile-${CND_CONF}.mk Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Mesh.o Mesh.cpp

${OBJECTDIR}/AxisAlignedBox.o: nbproject/Makefile-${CND_CONF}.mk AxisAlignedBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/AxisAlignedBox.o AxisAlignedBox.cpp

${OBJECTDIR}/SearchStatePath.o: nbproject/Makefile-${CND_CONF}.mk SearchStatePath.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/SearchStatePath.o SearchStatePath.cpp

${OBJECTDIR}/ThreadLoop.o: nbproject/Makefile-${CND_CONF}.mk ThreadLoop.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/ThreadLoop.o ThreadLoop.cpp

${OBJECTDIR}/SharedLock.o: nbproject/Makefile-${CND_CONF}.mk SharedLock.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/SharedLock.o SharedLock.cpp

${OBJECTDIR}/AxisObject.o: nbproject/Makefile-${CND_CONF}.mk AxisObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/AxisObject.o AxisObject.cpp

${OBJECTDIR}/Rectangle.o: nbproject/Makefile-${CND_CONF}.mk Rectangle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Rectangle.o Rectangle.cpp

${OBJECTDIR}/Date.o: nbproject/Makefile-${CND_CONF}.mk Date.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Date.o Date.cpp

${OBJECTDIR}/GUI.o: nbproject/Makefile-${CND_CONF}.mk GUI.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/GUI.o GUI.cpp

${OBJECTDIR}/Timer.o: nbproject/Makefile-${CND_CONF}.mk Timer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Timer.o Timer.cpp

${OBJECTDIR}/Key.o: nbproject/Makefile-${CND_CONF}.mk Key.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Key.o Key.cpp

${OBJECTDIR}/ThirdPersonCamera.o: nbproject/Makefile-${CND_CONF}.mk ThirdPersonCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/ThirdPersonCamera.o ThirdPersonCamera.cpp

${OBJECTDIR}/Quaternion.o: nbproject/Makefile-${CND_CONF}.mk Quaternion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Quaternion.o Quaternion.cpp

${OBJECTDIR}/Material.o: nbproject/Makefile-${CND_CONF}.mk Material.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -IInclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/Material.o Material.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
