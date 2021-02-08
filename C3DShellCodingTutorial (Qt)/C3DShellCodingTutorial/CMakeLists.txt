################################################################################
#                                                                              #
#  Copyright (c) 2016, C3D Labs LLC                                            #
#  All rights reserved.                                                        #
#                                                                              # 
################################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(C3DShellCodingTutorial  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
 
# CMP0020 Automatically link Qt executables to qtmain target on Windows.  
# CMP0043 Ignore COMPILE_DEFINITIONS_<Config> properties
#IF(POLICY CMP0020)
#    CMAKE_POLICY(SET CMP0020 NEW)
#    CMAKE_POLICY(SET CMP0043 NEW)
#ENDIF()

# Runtime output directory
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

# CMake modules search path
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
   
INCLUDE(vision_support)

IF(MSVC)  
    SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG_INIT} /W4 /D_DEBUG /D_DRAWGI /Zi  /MP /bigobj") 
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} /W4") 
ENDIF() 
 
# Unicode build
OPTION(C3DVision_USING_UNICODE "USING UNICODE" ON)
OPTION(C3DVision_POCKET_INSTALLER "Pocket Installer" ON)

################################################################################
# C3DShellCodingTutorial
################################################################################
OPTION(C3DVision_GUI_QT5 "Build Qt5 support" ON)

# Libraries C3D  
################################################################################
SET(Math_SOURCE_DIR   ${CMAKE_SOURCE_DIR}/../Kernel)

IF (MSVC)
  SET(C3DLIBNAME "c3d.lib")
  SET(C3DDLLNAME "c3d.dll")
ENDIF()

SET(Math_OUTPUT optimized ${Math_SOURCE_DIR}/Release/${C3DLIBNAME} debug ${Math_SOURCE_DIR}/Debug/${C3DLIBNAME})

SET(Vision_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../Vision)

IF (MSVC)
  SET(C3DVISIONLIBNAME "c3dvision.lib")
  SET(C3DVISIONDLLNAME "c3dvision.dll")
ENDIF()

SET(Vision_OUTPUT optimized ${Vision_SOURCE_DIR}/Release/${C3DVISIONLIBNAME} debug ${Vision_SOURCE_DIR}/Debug/${C3DVISIONLIBNAME})

#copy external dll, lib, pdb Math and Vision
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
  file(INSTALL ${Math_SOURCE_DIR}/Debug/${C3DDLLNAME}           DESTINATION ${CMAKE_BINARY_DIR}/Bin)
  file(INSTALL ${Vision_SOURCE_DIR}/Debug/${C3DVISIONDLLNAME}   DESTINATION ${CMAKE_BINARY_DIR}/Bin)
ELSE ()
  file(INSTALL ${Math_SOURCE_DIR}/Release/${C3DDLLNAME}         DESTINATION ${CMAKE_BINARY_DIR}/Bin)
  file(INSTALL ${Vision_SOURCE_DIR}/Release/${C3DVISIONDLLNAME} DESTINATION ${CMAKE_BINARY_DIR}/Bin)
ENDIF ()

#  Libraries QScintilla
################################################################################
SET(QScintilla_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../QScintilla)

IF (MSVC)
  SET(QSCINTILLALIBNAMEDEBUG "qscintilla2_qt5d.lib")
  SET(QSCINTILLALDLLNAMEDEBUG "qscintilla2_qt5d.dll")
  SET(QSCINTILLALIBNAMERELEASE "qscintilla2_qt5.lib")
  SET(QSCINTILLALDLLNAMERELEASE "qscintilla2_qt5.dll")
ENDIF()

SET(QScintilla_OUTPUT optimized ${QScintilla_SOURCE_DIR}/Release/${QSCINTILLALIBNAMERELEASE} debug ${QScintilla_SOURCE_DIR}/Debug/${QSCINTILLALIBNAMEDEBUG})

#copy external dll, lib, pdb QScintilla
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
  file(INSTALL ${QScintilla_SOURCE_DIR}/Debug/${QSCINTILLALDLLNAMEDEBUG}     DESTINATION ${CMAKE_BINARY_DIR}/Bin)
ELSE ()
  file(INSTALL ${QScintilla_SOURCE_DIR}/Release/${QSCINTILLALDLLNAMERELEASE} DESTINATION ${CMAKE_BINARY_DIR}/Bin)
ENDIF ()

#  Libraries AdvancedDockingSystem
################################################################################
SET(QtAdvancedDocking_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../AdvancedDockingSystem)

IF (MSVC)
  SET(QTADVANCEDDOCKINGLIBNAMEDEBUG "qtadvanceddockingd.lib")
  SET(QTADVANCEDDOCKINGDLLNAMEDEBUG "qtadvanceddockingd.dll")
  SET(QTADVANCEDDOCKINGLIBNAMERELEASE "qtadvanceddocking.lib")
  SET(QTADVANCEDDOCKINGDLLNAMERELEASE "qtadvanceddocking.dll")
ENDIF()
 
SET(QtAdvancedDocking_OUTPUT optimized ${QtAdvancedDocking_SOURCE_DIR}/Release/${QTADVANCEDDOCKINGLIBNAMERELEASE} debug ${QtAdvancedDocking_SOURCE_DIR}/Debug/${QTADVANCEDDOCKINGLIBNAMEDEBUG})

#copy external dll, lib, pdb  
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
  file(INSTALL ${QtAdvancedDocking_SOURCE_DIR}/Debug/${QTADVANCEDDOCKINGDLLNAMEDEBUG}     DESTINATION ${CMAKE_BINARY_DIR}/Bin)
ELSE ()
  file(INSTALL ${QtAdvancedDocking_SOURCE_DIR}/Release/${QTADVANCEDDOCKINGDLLNAMERELEASE} DESTINATION ${CMAKE_BINARY_DIR}/Bin)
ENDIF ()
  

# User Folders and copy 
################################################################################  
#c3dlib
#IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
#  file(INSTALL ${Math_SOURCE_DIR}/Debug/${C3DLIBNAME}     DESTINATION ${CMAKE_BINARY_DIR}/Bin/User)
#  SET(USER_DIR ${CMAKE_SOURCE_DIR}/User/Debug)
#ELSE ()
#  file(INSTALL ${Math_SOURCE_DIR}/Release/${C3DLIBNAME} DESTINATION ${CMAKE_BINARY_DIR}/Bin/User)
#  SET(USER_DIR ${CMAKE_SOURCE_DIR}/User/Release)
#ENDIF ()
#
#
# file(GLOB_RECURSE USERFILES ${USER_DIR}/*)
#  file(COPY ${USERFILES} DESTINATION ${CMAKE_BINARY_DIR}/Bin/User)
#
#
#install(DIRECTORY ${Math_SOURCE_DIR}/Include DESTINATION ${CMAKE_BINARY_DIR}/Bin/User/Kernel)

# Docs 
################################################################################
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Bin/Docs)
ADD_CUSTOM_TARGET( Unzipping_Docs_files
  COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/Docs/docs_test_version.zip
  DEPENDS ${CMAKE_SOURCE_DIR}/Docs/docs_test_version.zip
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/Docs"
  COMMENT "Unpacking docs.zip"
VERBATIM)

# Tutorials
################################################################################ 
set(TUTORIALS Tutorials)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/${TUTORIALS} DESTINATION ${CMAKE_BINARY_DIR}/Bin)

# Models
################################################################################ 
set(MODELS Models)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/${MODELS} DESTINATION ${CMAKE_BINARY_DIR}/Bin)

# Manuals
################################################################################ 
set(MANUALS Manuals)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/${MANUALS} DESTINATION ${CMAKE_BINARY_DIR}/Bin)

# PdfJs
################################################################################ 
set(PDFJS pdfjs)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/${PDFJS} DESTINATION ${CMAKE_BINARY_DIR}/Bin)

# WorkFolder
################################################################################
#set(WORKFOLDER WorkFolder)
#install(DIRECTORY ${CMAKE_SOURCE_DIR}/${WORKFOLDER} DESTINATION ${CMAKE_BINARY_DIR}/Bin)

IF(C3DVision_USING_UNICODE)
  ADD_DEFINITIONS( 
    -DUNICODE
    -D_UNICODE
    )
ENDIF()

INCLUDE_DIRECTORIES(
    #${CMAKE_CURRENT_SOURCE_DIR}
    #${CMAKE_CURRENT_SOURCE_DIR}/Shared
    )

IF (C3DVision_GUI_QT5)
  SET(DESIRED_QT_VERSION "5" CACHE STRING "")
  find_package( Qt5Core REQUIRED )
  find_package( Qt5Gui REQUIRED )
  find_package( Qt5OpenGL REQUIRED )
  find_package( Qt5WebEngineWidgets REQUIRED )
  find_package( Qt5Xml REQUIRED )
  find_package( Qt5LinguistTools REQUIRED )
  
  ADD_DEFINITIONS(-D__USE_QT__)
  
  SET(QtVision_OUTPUT "qtvision")
  ADD_SUBDIRECTORY(QtVision)
  
  SET(C3DShellCodingTutorial_OUTPUT "C3DShellCodingTutorial")
  ADD_SUBDIRECTORY(C3DShellCodingTutorial)
  
  ADD_DEFINITIONS( -DNOMINMAX )
ENDIF()

