#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "BCPPUL::bcppul_static" for configuration "MinSizeRel"
set_property(TARGET BCPPUL::bcppul_static APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(BCPPUL::bcppul_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/bcppul_static.lib"
  )

list(APPEND _cmake_import_check_targets BCPPUL::bcppul_static )
list(APPEND _cmake_import_check_files_for_BCPPUL::bcppul_static "${_IMPORT_PREFIX}/lib/bcppul_static.lib" )

# Import target "BCPPUL::bcppul_shared" for configuration "MinSizeRel"
set_property(TARGET BCPPUL::bcppul_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(BCPPUL::bcppul_shared PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/bcppul_shared.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/bcppul_shared.dll"
  )

list(APPEND _cmake_import_check_targets BCPPUL::bcppul_shared )
list(APPEND _cmake_import_check_files_for_BCPPUL::bcppul_shared "${_IMPORT_PREFIX}/lib/bcppul_shared.lib" "${_IMPORT_PREFIX}/bin/bcppul_shared.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
