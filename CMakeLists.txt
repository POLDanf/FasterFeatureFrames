cmake_minimum_required(VERSION 3.12)
project(FasterFeatureFrames LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find pybind11
find_package(pybind11 REQUIRED)

# Find OpenMP
find_package(OpenMP REQUIRED)

# Define the source files
set(SOURCE_FILES
    cpp/src/FasterFeatureFrames.cpp
    bindings/bindings.cpp
)

# Create the pybind11 module
pybind11_add_module(_fasterfeatureframes_core ${SOURCE_FILES})

# Optimization flags
target_compile_options(_fasterfeatureframes_core PRIVATE
    -O3
    -march=native
)

# Link OpenMP
target_link_libraries(_fasterfeatureframes_core PRIVATE
    OpenMP::OpenMP_CXX
)

# Output directory
set_target_properties(_fasterfeatureframes_core PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/python"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/python"
)