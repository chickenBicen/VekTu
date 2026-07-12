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
message(STATUS "Vek-Tu Build Type: ${CMAKE_BUILD_TYPE}")

# Set the version for Vek-Tu
set(VekTu_Version_Major 0)
set(VekTu_Version_Minor 1)
set(VekTu_Version_Patch 0)
set(VekTu_Version_Status "-dev")
set(PROJECT_VERSION
    "${Vek-Tu_Version_Major}.${Vek-Tu_Version_Minor}.${Vek-Tu_Version_Patch}${Vek-Tu_Version_Status}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

add_library(VekTu)
add_subdirectory(./test/)
target_sources(VekTu
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        modules/Common.cppm
            modules/Vec2.cppm
            modules/Vec3.cppm
            modules/Vec4.cppm   
            modules/linear.cppm
            modules/Mat2.cppm
            modules/Mat3.cppm
            
)

target_include_directories(
    VekTu
    PRIVATE ${PROJECT_SOURCE_DIR}/includes
)
