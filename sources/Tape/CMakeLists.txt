set(TAPE_SOURCES TapeHandler.cpp)

set(TAPE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories(
    ${TAPE_INCLUDE_DIR}/Tape
)

set(TAPE_HEADERS
    ${TAPE_INCLUDE_DIR}/Tape/ITape.h
    ${TAPE_INCLUDE_DIR}/Tape/TapeHandler.h
    ${TAPE_INCLUDE_DIR}/Tape/TapeSettings.h
)

add_library(TapeLib OBJECT ${TAPE_SOURCES} ${TAPE_HEADERS})

target_include_directories(TapeLib PRIVATE TAPE_INCLUDE_DIR)