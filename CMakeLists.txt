cmake_minimum_required(VERSION 3.10)
project(BCPPUL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BCPPUL_VERSION_MAJOR 0)
set(BCPPUL_VERSION_MINOR 1)
set(BCPPUL_VERSION_PATCH 0)

include(GNUInstallDirs)


add_library(bcppul_static STATIC
    src/bcppul.cpp
)
add_library(bcppul_shared SHARED
    src/bcppul.cpp
)

target_compile_definitions(bcppul_shared PRIVATE BCPPUL_EXPORTS)

target_include_directories(bcppul_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_include_directories(bcppul_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(bcppul_static PROPERTIES
    VERSION ${BCPPUL_VERSION_MAJOR}.${BCPPUL_VERSION_MINOR}.${BCPPUL_VERSION_PATCH}
    SOVERSION ${BCPPUL_VERSION_MAJOR}
    PUBLIC_HEADER "include/bcppul.h"
)

set_target_properties(bcppul_shared PROPERTIES
    VERSION ${BCPPUL_VERSION_MAJOR}.${BCPPUL_VERSION_MINOR}.${BCPPUL_VERSION_PATCH}
    SOVERSION ${BCPPUL_VERSION_MAJOR}
    PUBLIC_HEADER "include/bcppul.h"
)

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

add_executable(bcppul_example examples/main.cpp)

target_link_libraries(bcppul_example PRIVATE bcppul_shared)

add_dependencies(bcppul_example bcppul_shared)

target_link_directories(bcppul_example PRIVATE $<TARGET_FILE_DIR:bcppul_shared>)


target_include_directories(bcppul_example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()
add_test(NAME BCPPUL_Example_Run COMMAND bcppul_example)