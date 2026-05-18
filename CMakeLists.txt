cmake_minimum_required(VERSION 3.12)
project(FasterFeatureFrames)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find pybind11
find_package(pybind11 REQUIRED)

# Define the source files
set(SOURCE_FILES
    cpp/src/FasterFeatureFrames.cpp
    bindings/bindings.cpp
)

# Create the pybind11 module
pybind11_add_module(_fasterfeatureframes_core ${SOURCE_FILES})

# Ensure the module is placed in the python folder for the wrapper to find
set_target_properties(_fasterfeatureframes_core PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/python"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/python"
)