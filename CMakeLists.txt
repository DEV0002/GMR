cmake_minimum_required(VERSION 3.2)
project(GMR)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set(    SOURCE_FILES

        # MAIN
        source/main.cpp

)

add_executable(SnapPP ${SOURCE_FILES})

target_compile_features(SnapPP PUBLIC cxx_std_17)

target_include_directories(SnapPP PUBLIC "source")