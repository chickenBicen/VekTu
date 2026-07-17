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

add_library(
    VekTu
)

target_sources(VekTu
    PUBLIC
        FILE_SET CXX_MODULES
        TYPE CXX_MODULES
        BASE_DIRS
            include
        FILES
            include/VekTu/Common.cppm
            include/VekTu/linear.cppm
            include/VekTu/Linear/Vec2.cppm
            include/VekTu/Linear/Vec3.cppm
            include/VekTu/Linear/Vec4.cppm
            include/VekTu/Linear/Mat2.cppm
            include/VekTu/Linear/Mat3.cppm
            include/VekTu/Geometry/Shapes.cppm
)

target_include_directories(
    VekTu
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(
    TARGETS VekTu
    EXPORT VekTuTargets
    FILE_SET CXX_MODULES
    DESTINATION include
)
install(
    EXPORT VekTuTargets
    FILE VekTuTargets.cmake
    NAMESPACE VekTu::
    DESTINATION lib/cmake/VekTu
)
