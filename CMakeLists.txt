cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(Neon)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

include_directories(src)

### Main binary target: Neon
find_package(SDL2 REQUIRED)
set(SDL2_ALL_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})
set(SDL2_ALL_LIBRARIES ${SDL2_LIBRARIES})
find_package(SDL2_image REQUIRED)
set(SDL2_ALL_INCLUDE_DIRS ${SDL2_ALL_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
find_package(SDL2_ttf REQUIRED)
set(SDL2_ALL_INCLUDE_DIRS ${SDL2_ALL_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} ${SDL2_TTF_LIBRARIES})

file(GLOB_RECURSE SRC_SOURCES LIST_DIRECTORIES true
    src/*.hpp
    src/*.cpp
)
include_directories(Neon ${SDL2_ALL_INCLUDE_DIRS})
add_executable(Neon ${SRC_SOURCES})
target_link_libraries(Neon ${SDL2_LIBRARIES} ${SDL2_ALL_LIBRARIES})

# Necessary so that code from /src/ can be used by files in /test/ directory:
add_library(Neon_lib STATIC ${SRC_SOURCES})


### Test binary target: test_Neon
add_subdirectory(lib/googletest)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true
    test/*.hpp
    test/*.cpp
)
add_test(
    NAME test_Neon
    COMMAND test_Neon
)
add_executable(test_Neon ${TEST_SOURCES})
target_link_libraries(test_Neon PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)
