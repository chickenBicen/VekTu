cmake_minimum_required(VERSION 3.30)
project(VekTu VERSION 0.1.0 LANGUAGES CXX)

add_library(VekTu src/utils.cpp)

target_compile_features(VekTu PUBLIC cxx_std_20)

enable_testing()

# cache variables for installation destinations
include(GNUInstallDirs)
include(CTest)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()

target_include_directories(
    VekTu
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_sources(VekTu
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
            include/VekTu/Geometry/AABB.h
            include/VekTu/Geometry/Shapes.h
            include/VekTu/Linear/Mat2.h
            include/VekTu/Linear/Mat3.h
            include/VekTu/Linear/Mat4.h
            include/VekTu/Linear/Vec2.h
            include/VekTu/Linear/Vec3.h
            include/VekTu/Linear/Vec4.h
            include/VekTu/Math/Matrix.h
            include/VekTu/Math/Vector.h
            include/VekTu/Common.h
            include/VekTu/Linear.h
            include/VekTu/utils.h
)

install(TARGETS VekTu
    EXPORT VekTuTargets
    FILE_SET HEADERS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


install(EXPORT VekTuTargets
    FILE VekTuTargets.cmake
    NAMESPACE VekTu::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VekTu
    )

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/VekTuConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VekTu
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/VekTuConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VekTu
)
