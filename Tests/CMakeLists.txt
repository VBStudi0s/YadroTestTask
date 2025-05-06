enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests
    TapeTests.cpp)

target_link_libraries(tests
    TapeLib
    ${GTEST_LIBRARIES}
    pthread)

add_test(NAME Tests COMMAND tests)
