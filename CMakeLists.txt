cmake_minimum_required(VERSION 3.2)
project(GMR)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_subdirectory(extern)

include_directories(extern
                    source)

set(    SOURCE_FILES

        # UTIL
        source/util/buffers.cpp

        # MAIN
        source/main.cpp

        # OPUS
        source/opus/rangedec.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)