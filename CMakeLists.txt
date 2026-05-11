cmake_minimum_required(VERSION 3.15)
project(FasterFeatureFrames LANGUAGES CXX)

# Use C++17 for pybind11 compatibility
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to find pybind11 if it's already installed
find_package(pybind11 CONFIG QUIET)

# If pybind11 isn't found locally, fetch it automatically from GitHub
if(NOT pybind11_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      pybind11
      GIT_REPOSITORY https://github.com/pybind/pybind11.git
      GIT_TAG        v2.11.1
    )
    FetchContent_MakeAvailable(pybind11)
endif()

# Create the python extension module named `_fasterfeatureframes_core`
pybind11_add_module(_fasterfeatureframes_core 
    bindings/bindings.cpp 
    cpp/src/FasterFeatureFrames.cpp
)

# Tell the compiler where to find our header files
target_include_directories(_fasterfeatureframes_core PRIVATE cpp/include)
