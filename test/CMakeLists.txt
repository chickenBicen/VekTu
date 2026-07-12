
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(
    tests ./testMain.cpp
)

target_link_libraries(
    tests
    PRIVATE
    VekTu
)

add_test(
    NAME RunLibraryTests 
    COMMAND $<TARGET_FILE:tests>
)

