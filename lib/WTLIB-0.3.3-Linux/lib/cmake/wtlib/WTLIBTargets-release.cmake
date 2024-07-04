#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "wtlib::core" for configuration "Release"
set_property(TARGET wtlib::core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(wtlib::core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libcore.a"
  )

list(APPEND _cmake_import_check_targets wtlib::core )
list(APPEND _cmake_import_check_files_for_wtlib::core "${_IMPORT_PREFIX}/lib/libcore.a" )

# Import target "wtlib::internal" for configuration "Release"
set_property(TARGET wtlib::internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(wtlib::internal PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libinternal.a"
  )

list(APPEND _cmake_import_check_targets wtlib::internal )
list(APPEND _cmake_import_check_files_for_wtlib::internal "${_IMPORT_PREFIX}/lib/libinternal.a" )

# Import target "wtlib::sources" for configuration "Release"
set_property(TARGET wtlib::sources APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(wtlib::sources PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsources.so"
  IMPORTED_SONAME_RELEASE "libsources.so"
  )

list(APPEND _cmake_import_check_targets wtlib::sources )
list(APPEND _cmake_import_check_files_for_wtlib::sources "${_IMPORT_PREFIX}/lib/libsources.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
