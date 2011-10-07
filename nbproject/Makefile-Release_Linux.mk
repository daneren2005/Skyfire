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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release_Linux
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include skyfire-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ParticleSystem.o \
	${OBJECTDIR}/Matrix.o \
	${OBJECTDIR}/BaseObject.o \
	${OBJECTDIR}/FirstPersonCamera.o \
	${OBJECTDIR}/Thread.o \
	${OBJECTDIR}/Triangle.o \
	${OBJECTDIR}/Camera.o \
	${OBJECTDIR}/CameraRenderer.o \
	${OBJECTDIR}/Renderer.o \
	${OBJECTDIR}/File.o \
	${OBJECTDIR}/Console.o \
	${OBJECTDIR}/Input.o \
	${OBJECTDIR}/Universe.o \
	${OBJECTDIR}/Region.o \
	${OBJECTDIR}/Window.o \
	${OBJECTDIR}/ObjectOrientedBox.o \
	${OBJECTDIR}/Matrix4.o \
	${OBJECTDIR}/Folder.o \
	${OBJECTDIR}/ParticleEmitter.o \
	${OBJECTDIR}/GenericType.o \
	${OBJECTDIR}/MeshPart.o \
	${OBJECTDIR}/Model.o \
	${OBJECTDIR}/Particle.o \
	${OBJECTDIR}/ResourceManager.o \
	${OBJECTDIR}/Vector.o \
	${OBJECTDIR}/GenericPointer.o \
	${OBJECTDIR}/CString.o \
	${OBJECTDIR}/Time.o \
	${OBJECTDIR}/Bitmap.o \
	${OBJECTDIR}/Sphere.o \
	${OBJECTDIR}/Mesh.o \
	${OBJECTDIR}/AxisAlignedBox.o \
	${OBJECTDIR}/Rectangle.o \
	${OBJECTDIR}/Date.o \
	${OBJECTDIR}/AxisObject.o \
	${OBJECTDIR}/Timer.o \
	${OBJECTDIR}/Key.o \
	${OBJECTDIR}/ThirdPersonCamera.o \
	${OBJECTDIR}/Quaternion.o \
	${OBJECTDIR}/Material.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskyfire.a

${OBJECTDIR}/ParticleSystem.o: ParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/ParticleSystem.o ParticleSystem.cpp

${OBJECTDIR}/Matrix.o: Matrix.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Matrix.o Matrix.cpp

${OBJECTDIR}/BaseObject.o: BaseObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/BaseObject.o BaseObject.cpp

${OBJECTDIR}/FirstPersonCamera.o: FirstPersonCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/FirstPersonCamera.o FirstPersonCamera.cpp

${OBJECTDIR}/Thread.o: Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Thread.o Thread.cpp

${OBJECTDIR}/Triangle.o: Triangle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Triangle.o Triangle.cpp

${OBJECTDIR}/Camera.o: Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Camera.o Camera.cpp

${OBJECTDIR}/CameraRenderer.o: CameraRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/CameraRenderer.o CameraRenderer.cpp

${OBJECTDIR}/Renderer.o: Renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Renderer.o Renderer.cpp

${OBJECTDIR}/File.o: File.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/File.o File.cpp

${OBJECTDIR}/Console.o: Console.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Console.o Console.cpp

${OBJECTDIR}/Input.o: Input.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input.o Input.cpp

${OBJECTDIR}/Universe.o: Universe.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Universe.o Universe.cpp

${OBJECTDIR}/Region.o: Region.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Region.o Region.cpp

${OBJECTDIR}/Window.o: Window.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Window.o Window.cpp

${OBJECTDIR}/ObjectOrientedBox.o: ObjectOrientedBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/ObjectOrientedBox.o ObjectOrientedBox.cpp

${OBJECTDIR}/Matrix4.o: Matrix4.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Matrix4.o Matrix4.cpp

${OBJECTDIR}/Folder.o: Folder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Folder.o Folder.cpp

${OBJECTDIR}/ParticleEmitter.o: ParticleEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/ParticleEmitter.o ParticleEmitter.cpp

${OBJECTDIR}/GenericType.o: GenericType.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/GenericType.o GenericType.cpp

${OBJECTDIR}/MeshPart.o: MeshPart.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/MeshPart.o MeshPart.cpp

${OBJECTDIR}/Model.o: Model.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Model.o Model.cpp

${OBJECTDIR}/Particle.o: Particle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Particle.o Particle.cpp

${OBJECTDIR}/ResourceManager.o: ResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/ResourceManager.o ResourceManager.cpp

${OBJECTDIR}/Vector.o: Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Vector.o Vector.cpp

${OBJECTDIR}/GenericPointer.o: GenericPointer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/GenericPointer.o GenericPointer.cpp

${OBJECTDIR}/CString.o: CString.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/CString.o CString.cpp

${OBJECTDIR}/Time.o: Time.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Time.o Time.cpp

${OBJECTDIR}/Bitmap.o: Bitmap.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Bitmap.o Bitmap.cpp

${OBJECTDIR}/Sphere.o: Sphere.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sphere.o Sphere.cpp

${OBJECTDIR}/Mesh.o: Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Mesh.o Mesh.cpp

${OBJECTDIR}/AxisAlignedBox.o: AxisAlignedBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/AxisAlignedBox.o AxisAlignedBox.cpp

${OBJECTDIR}/Rectangle.o: Rectangle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Rectangle.o Rectangle.cpp

${OBJECTDIR}/Date.o: Date.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Date.o Date.cpp

${OBJECTDIR}/AxisObject.o: AxisObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/AxisObject.o AxisObject.cpp

${OBJECTDIR}/Timer.o: Timer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Timer.o Timer.cpp

${OBJECTDIR}/Key.o: Key.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Key.o Key.cpp

${OBJECTDIR}/ThirdPersonCamera.o: ThirdPersonCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/ThirdPersonCamera.o ThirdPersonCamera.cpp

${OBJECTDIR}/Quaternion.o: Quaternion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Quaternion.o Quaternion.cpp

${OBJECTDIR}/Material.o: Material.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -MMD -MP -MF $@.d -o ${OBJECTDIR}/Material.o Material.cpp

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
