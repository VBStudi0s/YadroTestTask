# Main CMake for the project

enable_testing()

cmake_minimum_required(VERSION 3.22)

project(TapeSorter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(SOURCE_DIR ./sources)
set(TESTS_DIR ./Tests)
set(INCLUDE_DIRECTORIES ./include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

include_directories(${INCLUDE_DIRECTORIES})

add_subdirectory(${SOURCE_DIR})

add_executable(main ${SOURCE_DIR}/main.cpp)

target_include_directories(main PRIVATE ${INCLUDE_DIRECTORIES})

target_link_libraries(main PRIVATE TapeLib SorterLib)

add_subdirectory(${TESTS_DIR})
