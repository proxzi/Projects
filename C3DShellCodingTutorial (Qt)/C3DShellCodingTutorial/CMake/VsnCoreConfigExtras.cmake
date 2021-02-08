include(VsnCoreConfig)

if (NOT TARGET Vsn::vsn_rcc)
    add_executable(Vsn::vsn_rcc IMPORTED)

    if (UNIX)
      SET(VCCRCC "vsn_rcc")
    else()
      SET(VCCRCC "vsn_rcc.exe")
    endif()

    set(imported_location "${_vsnCore_install_prefix}/Tools/visionrcc/release/${VCCRCC}")
    _vsn_Core_check_file_exists(${imported_location})

    set_target_properties(Vsn::vsn_rcc PROPERTIES
        IMPORTED_LOCATION ${imported_location}
    )
endif()

set(VSNCore_RCC_EXECUTABLE Vsn::vsn_rcc)
