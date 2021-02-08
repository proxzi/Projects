if (CMAKE_VERSION VERSION_LESS 2.8.3)
    message(FATAL_ERROR "Vision 1.0.0 requires at least CMake version 2.8.3")
endif()

get_filename_component(_vsnCore_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

# For backwards compatibility only. Use VsnCore_VERSION instead.
set(VssnCore_VERSION_STRING 1.0.0)

set(VsnCore_LIBRARIES Vsn::Core)

macro(_vsn_Core_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The imported target \"Vsn::Core\" references the file
   \"${file}\"
	but this file does not exist.  Possible reasons include:
	* The file was deleted, renamed, or moved to another location.
	* An install or uninstall procedure did not complete successfully.
	* The installation package was faulty and contained
	   \"${CMAKE_CURRENT_LIST_FILE}\"
	but not all the files it references.
	")
    endif()
endmacro()
