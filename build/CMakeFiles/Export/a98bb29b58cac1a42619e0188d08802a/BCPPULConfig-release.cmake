#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "BCPPUL::bcppul_static" for configuration "Release"
set_property(TARGET BCPPUL::bcppul_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(BCPPUL::bcppul_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/bcppul_static.lib"
  )

list(APPEND _cmake_import_check_targets BCPPUL::bcppul_static )
list(APPEND _cmake_import_check_files_for_BCPPUL::bcppul_static "${_IMPORT_PREFIX}/lib/bcppul_static.lib" )

# Import target "BCPPUL::bcppul_shared" for configuration "Release"
set_property(TARGET BCPPUL::bcppul_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(BCPPUL::bcppul_shared PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/bcppul_shared.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/bcppul_shared.dll"
  )

list(APPEND _cmake_import_check_targets BCPPUL::bcppul_shared )
list(APPEND _cmake_import_check_files_for_BCPPUL::bcppul_shared "${_IMPORT_PREFIX}/lib/bcppul_shared.lib" "${_IMPORT_PREFIX}/bin/bcppul_shared.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
