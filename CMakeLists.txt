cmake_minimum_required(VERSION 3.30)
project(VekTu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

if(NOT CMAKE_BUILD_TYPE)
    set(default_build_type "Debug")
    message(STATUS "Set the build type to `${default_build_type}` as none was specified.")
    set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Chooce the build type." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "VekTu Build Type: ${CMAKE_BUILD_TYPE}")

# Set the version for Vek-Tu
set(VekTu_Version_Major 0)
set(VekTu_Version_Minor 1)
set(VekTu_Version_Patch 0)
set(VekTu_Version_Status "-dev")
set(PROJECT_VERSION
    "${VekTu_Version_Major}.${VekTu_Version_Minor}.${VekTu_Version_Patch}${VekTu_Version_Status}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

add_subdirectory(test)
add_library(
    VekTu INTERFACE
)

target_sources(VekTu INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        include/VekTu/Common.h
        include/VekTu/Linear/Vec2.h
)
target_include_directories(
    VekTu
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(
    TARGETS VekTu
    EXPORT VekTuTargets
    FILE_SET HEADERS
    DESTINATION include
)
install(
    EXPORT VekTuTargets
    FILE VekTuTargets.cmake
    NAMESPACE VekTu::
    DESTINATION lib/cmake/VekTu
)
