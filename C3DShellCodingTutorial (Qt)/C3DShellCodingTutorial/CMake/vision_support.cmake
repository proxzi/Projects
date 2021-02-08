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

# set output lib arhive directory
MACRO(pocket_output _target)
  #message("ARGC='${ARGC}' ARGV='${ARGV}' ARGN='${ARGN}'")
  #message("ARG0=${ARGV0}")
  
  SET(OUTER_PREFIX "${C3DVision_POCKET_DIRECTORY}/")
  
  SET(VISION_OUT_PATH "${OUTER_PREFIX}/Debug")
  INSTALL(TARGETS ${_target}
    RUNTIME DESTINATION ${VISION_OUT_PATH} CONFIGURATIONS Debug
    ARCHIVE DESTINATION ${VISION_OUT_PATH} CONFIGURATIONS Debug
    LIBRARY DESTINATION ${VISION_OUT_PATH} CONFIGURATIONS Debug
  )
  SET(VISION_OUT_PATH "${OUTER_PREFIX}/Release")
  INSTALL(TARGETS ${_target}
    RUNTIME DESTINATION ${VISION_OUT_PATH} CONFIGURATIONS Release
    ARCHIVE DESTINATION ${VISION_OUT_PATH} CONFIGURATIONS Release
    LIBRARY DESTINATION ${VISION_OUT_PATH} CONFIGURATIONS Release
  )
endMACRO()

# install include
MACRO(pocket_copy_include _src _dst)
  INSTALL(FILES ${_src} DESTINATION ${_dst})
endMACRO()

# add install command
MACRO(pocket_install_command _target)
  ADD_CUSTOM_COMMAND(TARGET ${_target}
    POST_BUILD
    COMMAND cmake -DBUILD_TYPE=$<CONFIGURATION> -P cmake_install.cmake)
endMACRO()

# vsn_platform
MACRO(vsn_platform)
  # Platform detect, used to configure c3d_platform.h.in
  IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	ADD_DEFINITIONS(-DVSN_PLATFORM_MACOSX)
  ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    #OPTION(VSN_UNIX_INSTALL_MODE "Set to ON to install C3D into default UNIX path structure." OFF)
	ADD_DEFINITIONS(-DVSN_PLATFORM_LINUX)
  ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	ADD_DEFINITIONS(-DVSN_PLATFORM_WINDOWS)
  ELSE()
    message(FATAL_ERROR "Unable to detect platform!")
  ENDIF()
  #message(STATUS "System detected: \"${CMAKE_SYSTEM_NAME}\"")
  
  # OpenGL, OpenGL ES 1 or OpenGL ES 2 mode
  SET(C3DVision_OPENGL_MODE "OPENGL" CACHE STRING "Set it to OPENGL, OPENGL_ES1 or OPENGL_ES2 to build C3D for OpenGL, OpenGL ES 1.x or OpenGL ES 2.x")
  # Setup variables used to configure c3d_platform.h.in
  IF( C3DVision_OPENGL_MODE STREQUAL  "OPENGL")
    #message(STATUS "Configuring for OpenGL 1.x/2.x/3.x/4.x")
	ADD_DEFINITIONS(-DVSN_OPENGL)
  ELSEIF( C3DVision_OPENGL_MODE STREQUAL  "OPENGL_ES1")
    #message(STATUS "Configuring for OpenGL ES 1.x")
	ADD_DEFINITIONS(-DVSN_OPENGL_ES1)
  ELSEIF( C3DVision_OPENGL_MODE STREQUAL  "OPENGL_ES2")
    #message(STATUS "Configuring for OpenGL ES 2.x")
	ADD_DEFINITIONS(VSN_OPENGL_ES2)
  ELSE()
    message(FATAL_ERROR "Invalid C3DVision_OPENGL_MODE! Valid modes are: OPENGL, OPENGL_ES1, OPENGL_ES2.")
  ENDIF()
endMACRO()