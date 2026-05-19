#!/bin/bash
set -e

echo "====================================="
echo "Cleaning previous build..."
echo "====================================="

rm -rf build

echo "====================================="
echo "Creating fresh build directory..."
echo "====================================="

mkdir build
cd build

echo "====================================="
echo "Configuring CMake..."
echo "====================================="

cmake -DCMAKE_BUILD_TYPE=Release ..

echo "====================================="
echo "Building project..."
echo "====================================="

make -j$(nproc)

echo "====================================="
echo "Build complete."
echo "====================================="