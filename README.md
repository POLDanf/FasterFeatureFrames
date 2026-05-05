# FasterFeatureFrames

A high-performance DataFrame library that combines the expressiveness of Python with the speed of C++.

## Overview

This project is designed as a drop-in or near drop-in alternative to pandas, focusing on faster execution for compute-heavy workloads while preserving a familiar API.

## Motivation

The motivation behind this project is to create a DataFrame library that is both fast and easy to use. Pandas is a great library, but it can be slow for large datasets. This project aims to provide a solution that is both fast and easy to use.

## Features

⚡ C++-accelerated core for critical data operations
🐍 Python interface for ease of use and rapid development
📊 Pandas-like API for minimal learning curve
🔁 Efficient memory handling to reduce overhead

## Project Structure

```
FasterFeatureFrames/
├── CMakeLists.txt       # C++ project configuration
├── bindings/
│   └── bindings.cpp     # Python bindings using pybind11
├── cpp/
│   ├── include/        # C++ header files
│   ├── src/            # C++ source files
│   ├── FasterFeatureFrames.cpp    
├── python/
│   ├── fasterfeatureframes/  # Python package 
└── tests/
```

## Installation



### Prerequisites


### Build Instructions


## Usage


## Benchmarks

### Setup


### Results


## Design

### Architecture


### Key Decisions


## Future Work


## What I Learned


## License

MIT License

## Author

Aidan Young
GitHub: https://github.com/POLDanf
