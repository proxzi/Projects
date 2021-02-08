################################################################################
#                                                                              #
#  Copyright (c) 2018, C3D Labs LLC                                            #
#  All rights reserved.                                                        #
#                                                                              #
#  This file is part of C3DVision Library                                      #
#  http://c3dlabs.com                                                          #
#                                                                              #
#  Exclusive rights to C3D Vision, any copies or components (parts) thereof    #
#  and other intellectual property belong to C3D Labs, LLC (the Rightholder).  # 
#  The license rights and restrictions are regulated by the Agreement between  #
#  the User and the Rightholder.                                               #
#                                                                              #
################################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(QtVision)

# CMP0038 Targets may not link directly to themselves.
# CMP0020 Automatically link Qt executables to qtmain target on Windows.
# CMP0043 Ignore COMPILE_DEFINITIONS_<Config> properties
#IF(POLICY CMP0020)
#	CMAKE_POLICY(SET CMP0020 NEW)
#	CMAKE_POLICY(SET CMP0038 OLD)
#	CMAKE_POLICY(SET CMP0043 NEW)
#ENDIF()
 
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(DESIRED_QT_VERSION "5" CACHE STRING "")
find_package( Qt5 COMPONENTS Core Gui OpenGL )

SET(QtCore_SRC
	./src/qt_openglwidget.cpp
	./src/qt_openglcontext.cpp
) 
SOURCE_GROUP(\\Core FILES ${QtCore_SRC})

#SET(MOC_Files 
#	./Include/qt_openglwidget.h
#  )
#QT5_WRAP_CPP(MOC_Gui ${MOC_Files})

SET(QtVision_INC
	./Include/qt_openglcontext.h
	./Include/qt_openglwidget.h
	./Include/qt_visiondef.h
	./Include/qt_resstream.h
	./Include/lisencekey.h
)
SOURCE_GROUP(Include FILES ${QtVision_INC})


IF(MathTest_NAMES)
  STRING(REPLACE "Source" "Revisions" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
ELSE()
  STRING(REPLACE "Source" "Install" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
ENDIF()

INCLUDE_DIRECTORIES(
    ${VLD_INCLUDE_DIRS}
    ${QtVision_SOURCE_DIR}/Include
    ${Vision_SOURCE_DIR}/Include
    ${Vision_SOURCE_DIR}/private
)

IF(C3DVision_POCKET_INSTALLER)
  INCLUDE_DIRECTORIES( ${Math_SOURCE_DIR}/Include)
ELSE()
  INCLUDE_DIRECTORIES(
    ${Math_SOURCE_DIR}/Include
    ${Vision_SOURCE_DIR}/src/Thread
    ) 
ENDIF()

IF(MSVC)
ADD_DEFINITIONS(
  #-D_WIN32_WINNT=0X0502
  )
ENDIF()

ADD_DEFINITIONS(
	-D_BUILDQTVISIONDLL
	-D__TEST_ONLY__
	-DOGLFT_NO_QT
	-DOGLFT_NO_SOLID
	-DVSN_COMPILER_EXPLICIT_OVERRIDES
	-DNOMINMAX
  )

IF (UNIX)
  ADD_DEFINITIONS(
    -DVSN_OS_UNIX
    )
  ADD_DEFINITIONS(-D_GLIBCXX_USE_CXX11_ABI=0)
ELSE()
  ADD_DEFINITIONS(
    -DVSN_OS_WIN32
    -DVSN_OS_WIN
    )
ENDIF()

IF(MSVC)
  #IF(C3DVision_USING_UNICODE)
    ADD_DEFINITIONS( 
      -DUNICODE
      -D_UNICODE
      -DVSN_DEBUG
      )
  #ENDIF(C3DVision_USING_UNICODE)
ENDIF()

IF(C3DVision_WITH_VLD)
  ADD_DEFINITIONS(
    -DENABLE_VLD
  )
ENDIF(C3DVision_WITH_VLD)

ADD_DEFINITIONS( 
  -D__USE_QT__
)

IF (C3DVision_FOR_VIEWER)
  ADD_DEFINITIONS(
    -DQT_VISION_STATIC
  )
ENDIF()
  
# platform  
vsn_platform()  
  
IF(MSVC)
  SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DEBUG -D_DRAWGI /Zi /W4 /MP /bigobj")
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} ")
ELSE()
  SET(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DEBUG -D_DRAWGI -Wno-deprecated-declarations -fno-operator-names -fopenmp")
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -Wno-deprecated-declarations -fno-operator-names -fopenmp")
ENDIF()

# метод сборки библиотеки
SET(QtVisionBuildMethod SHARED)
IF (C3DVision_FOR_VIEWER)
  SET(QtVisionBuildMethod STATIC)
ENDIF()
  
ADD_LIBRARY(${QtVision_OUTPUT} ${QtVisionBuildMethod} 
  ${QtCore_SRC} 
  ${QtVision_INC} 
  ${MOC_Gui}
)

message(STATUS "qtvision cxx: ${CMAKE_CXX_FLAGS}")

QT5_USE_MODULES(${QtVision_OUTPUT} Core Gui OpenGL Widgets)

IF (UNIX)
  SET(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")
ENDIF()

IF(MSVC) 
 TARGET_LINK_LIBRARIES(
	${QtVision_OUTPUT}
	${Vision_OUTPUT}
	${Math_OUTPUT}
    opengl32
    glu32
    )
ELSE()
    find_package(OpenGL REQUIRED)
    TARGET_LINK_LIBRARIES(
      ${QtVision_OUTPUT}
      ${Vision_OUTPUT}
      ${Math_OUTPUT}
      ${OPENGL_LIBRARIES}
      ${GLU_LIBRARY}
    )
ENDIF()

IF (C3DVision_FOR_VIEWER)
    TARGET_LINK_LIBRARIES(
	  ${QtVision_OUTPUT}	
      ${Vision_OUTPUT}
      ${Math_OUTPUT}
      ${Qt5Core_LIBRARIES}
      ${Qt5OpenGL_LIBRARIES}
      ${OPENGL_LIBRARIES}
      ${GLU_LIBRARY}
    )
ENDIF()

IF (C3DVision_FOR_VIEWER AND C3DVision_POCKET_DIRECTORY)
  include(vision_support)
  pocket_copy_include("${QtVision_INC}" "${C3DVision_POCKET_DIRECTORY}/../Include")
  pocket_output(${QtVision_OUTPUT})
  pocket_install_command(${QtVision_OUTPUT})
ENDIF()
