cmake_minimum_required(VERSION 3.10)
project(BCPPUL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BCPPUL_VERSION_MAJOR 0)
set(BCPPUL_VERSION_MINOR 1)
set(BCPPUL_VERSION_PATCH 10)

configure_file(
    include/bcppul/version_config.h.in
    "${CMAKE_CURRENT_BINARY_DIR}/bcppul/version_config.h"
    @ONLY
)

include(GNUInstallDirs)

add_library(bcppul_static STATIC)
add_library(bcppul_shared SHARED)

target_sources(bcppul_static PRIVATE
    src/bcppul.cpp
 "include/bcppul/timer.h" "src/timer.cpp" "include/bcppul/bcppul_expimp.h" "include/bcppul/file_utils.h" "src/file_utils.cpp" "include/bcppul/string_utils.h" "src/string_utils.cpp" "include/bcppul/bcppul_math.h" "src/bcppul_math.cpp" "include/bcppul/bcppul_math_precalc.h" "src/bcppul_math_precalc.cpp" "include/bcppul/properties.h" "src/properties.cpp" "src/logging.cpp" "include/bcppul/logging.h")

target_sources(bcppul_shared PRIVATE
    src/bcppul.cpp
 "include/bcppul/timer.h" "src/timer.cpp" "include/bcppul/bcppul_expimp.h" "include/bcppul/file_utils.h" "src/file_utils.cpp" "include/bcppul/string_utils.h" "src/string_utils.cpp" "include/bcppul/bcppul_math.h" "src/bcppul_math.cpp" "include/bcppul/bcppul_math_precalc.h" "src/bcppul_math_precalc.cpp" "include/bcppul/properties.h" "src/properties.cpp" "src/logging.cpp" "include/bcppul/logging.h")

target_compile_definitions(bcppul_shared PRIVATE BCPPUL_EXPORTS)

set_target_properties(bcppul_static PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

set_target_properties(bcppul_shared PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VERSION ${BCPPUL_VERSION_MAJOR}.${BCPPUL_VERSION_MINOR}.${BCPPUL_VERSION_PATCH}
    SOVERSION ${BCPPUL_VERSION_MAJOR}
)

target_include_directories(bcppul_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_include_directories(bcppul_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(bcppul_static PROPERTIES
    PUBLIC_HEADER "include/bcppul/bcppul.h"
)

set_target_properties(bcppul_shared PROPERTIES
    PUBLIC_HEADER "include/bcppul/bcppul.h"
)

#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h")

install(TARGETS bcppul_static bcppul_shared
    EXPORT BCPPULTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT BCPPULTargets
    FILE BCPPULConfig.cmake
    NAMESPACE BCPPUL::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BCPPUL
)

configure_file(
    cmake/BCPPULConfigVersion.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/BCPPULConfigVersion.cmake"
    @ONLY
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/BCPPULConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BCPPUL
)

add_executable(bcppul_example examples/main.cpp)

set_target_properties(bcppul_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_compile_definitions(bcppul_example PRIVATE BCPPUL_SHARED_USE)

target_link_libraries(bcppul_example PRIVATE bcppul_shared)

add_dependencies(bcppul_example bcppul_shared)

target_link_directories(bcppul_example PRIVATE "${CMAKE_BINARY_DIR}/lib")

target_include_directories(bcppul_example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    "${CMAKE_CURRENT_BINARY_DIR}"
)

enable_testing()
add_test(NAME BCPPUL_Example_Run COMMAND bcppul_example)