# FasterFeatureFrames

A high-performance DataFrame library that combines the expressiveness of Python with the speed of C++.

---

## Overview

FasterFeatureFrames is an experimental hybrid C++/Python DataFrame library built for high-performance data processing workloads. The project aims to provide a familiar, pandas-inspired API while accelerating compute-intensive operations using a native C++ backend.

The library is designed for developers and data engineers who want the productivity of Python without sacrificing performance on large datasets.

---

## Motivation

Python libraries like pandas are incredibly productive and easy to use, but performance can become a bottleneck when working with large datasets or repeated transformations.

This project was created to explore:

- How much performance can be gained by moving critical operations into C++
- How to bridge Python and C++ cleanly using pybind11
- Efficient memory handling strategies for tabular data
- Designing APIs that feel familiar while remaining performant

The goal is not only to improve execution speed, but also to deepen understanding of systems programming, language interoperability, and performance optimization.

---

## Features

- ⚡ C++-accelerated core for critical data operations
- 🐍 Python interface for ease of use and rapid development
- 📊 Pandas-like API for minimal learning curve
- 🔁 Efficient memory handling to reduce overhead
- 🧩 Modular architecture separating Python bindings from native code
- 🧪 Benchmark suite for comparing performance against pandas
- 🛠️ Cross-language build system using CMake and pybind11

---

## Project Structure

```text
FasterFeatureFrames/
├── .gitignore              # List of files to ignore in git
├── README.md               # Project documentation
├── CMakeLists.txt          # C++ build configuration
├── bindings/
│   └── bindings.cpp        # Python bindings using pybind11
├── cpp/
│   ├── include/
│   │   └── FasterFeatureFrames.h   # Header files
│   └── src/
│       └── FasterFeatureFrames.cpp # Core implementation
├── python/
│   └── fasterfeatureframes/
│       └── __init__.py
└── tests/
    ├── benchmarks/
    │   └── test_performance.py
    └── unit/
```

---

### Prerequisites

Before building the project, make sure the following tools are installed:

- Python 3.9+
- C++17 compatible compiler
- CMake 3.15+
- pybind11
- pip / virtualenv (recommended)

### Build Instructions

Clone the repository:

```bash
git clone https://github.com/POLDanf/FasterFeatureFrames.git
cd FasterFeatureFrames
```

Create and activate a virtual environment:

```bash
python -m venv venv
source venv/bin/activate
```

Install dependencies:

```bash
pip install pybind11 pytest
```

Build the C++ extension:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

(Optional) Install the Python package locally:

```bash
pip install -e .
```

---

## Usage

Example usage:

```python
import fasterfeatureframes as fff

df = fff.DataFrame({
    "feature_a": [1, 2, 3, 4],
    "feature_b": [10, 20, 30, 40]
})

result = df.sum("feature_b")

print(result)
```

Potential supported operations:

- Column selection
- Aggregations
- Filtering
- Vectorized arithmetic
- Memory-efficient transformations

---

### Setup

Benchmarks compare FasterFeatureFrames against pandas using:

- Large synthetic datasets
- Aggregation operations
- Filtering workloads
- Column-wise computations

Benchmark scripts are located in:

```text
tests/benchmarks/
```

Run benchmarks:

```bash
pytest tests/benchmarks/
```

### Results

> Preliminary benchmarks show noticeable improvements in compute-heavy operations where native C++ execution reduces Python overhead.

RESULTS (1000000 rows, 50 cols)
<br>
Pandas time:                0.1675s
<br>
FasterFeatureFrames time:    0.0015s
<br>
Speedup:                    111.59x
<br>

Benchmarking operations on 'column_0'...
<br>
Sum             | Pandas: 0.001990s | FFF: 0.000680s | Speedup: 2.93x<br>
Mean            | Pandas: 0.001024s | FFF: 0.000654s | Speedup: 1.57x<br>
Min             | Pandas: 0.001316s | FFF: 0.000801s | Speedup: 1.64x<br>
Max             | Pandas: 0.001211s | FFF: 0.000816s | Speedup: 1.48x<br>
Mul Scalar      | Pandas: 0.003556s | FFF: 0.002607s | Speedup: 1.36x<br>
Greater Than    | Pandas: 0.000926s | FFF: 0.000853s | Speedup: 1.09x
<br>

Testing Drop Column on 'column_1'...
<br>
Drop Column     | Pandas: 0.001266s | FFF: 0.000006s | Speedup: 197.30x


## Design

### Architecture

The project follows a layered architecture:

```text
Python API
    ↓
pybind11 Bindings
    ↓
C++ Core Engine
```

### Key Decisions

#### C++ Backend

Performance-critical operations are implemented in C++ to reduce interpreter overhead and improve execution speed.

#### pybind11 Integration

pybind11 provides lightweight interoperability between Python and C++ without requiring a separate wrapper language.

#### Pandas-Inspired API

Keeping a familiar API lowers the learning curve and improves developer adoption.

#### Modular Separation

Separating bindings, native code, and Python packaging improves maintainability and scalability.

---

## Future Work

Planned improvements include:

- Parallel execution support
- SIMD optimizations
- GroupBy operations
- Lazy evaluation
- Additional benchmark coverage
- Better error handling and validation
- Full pandas interoperability

---

## What I Learned

This project helped strengthen understanding of:

- C++ performance optimization
- Python/C++ interoperability
- API design
- Build systems with CMake
- Native extension development
- Benchmarking and profiling techniques

It also provided hands-on experience designing software that balances usability with low-level performance.

---

## License

MIT License

---

## Author

**Aidan Young**

- GitHub: https://github.com/POLDanf