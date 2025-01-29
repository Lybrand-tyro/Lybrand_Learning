cmake_minimum_required(VERSION 3.10)
project(VScodeLibrary)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

aux_source_directory(${PROJECT_SOURCE_DIR} SOURCES)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)
