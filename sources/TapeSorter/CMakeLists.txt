set(SORTER_SOURCES TapeSorter.cpp)

set(SORTER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories(
    ${SORTER_INCLUDE_DIR}/Tape
    ${SORTER_INCLUDE_DIR}/TapeSorter
)

set(SORTER_HEADERS
    ${SORTER_INCLUDE_DIR}/Tape/ITape.h
    ${SORTER_INCLUDE_DIR}/Tape/TapeHandler.h
    ${SORTER_INCLUDE_DIR}/Tape/TapeSettings.h
    ${SORTER_INCLUDE_DIR}/TapeSorter/TapeSorter.h
)

add_library(SorterLib OBJECT ${SORTER_SOURCES} ${SORTER_HEADERS})

target_include_directories(SorterLib PRIVATE SORTER_INCLUDE_DIR)