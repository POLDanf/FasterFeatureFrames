#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../cpp/include/FasterFeatureFrames.h"

namespace py = pybind11;

PYBIND11_MODULE(_fasterfeatureframes_core, m) {
    m.doc() = "FasterFeatureFrames core C++ extension";

    /*
     TODO:
     1. Expose the FasterFeatureFrames class to Python using py::class_<FasterFeatureFrames>(m, "FasterFeatureFrames")
     2. Bind the constructor using .def(py::init<>())
     3. Bind the 'add_column' method using .def("add_column", ...)
     4. Bind the 'get_column' method using .def("get_column", ...)
     5. Bind 'get_columns' as a read-only property named 'columns' using .def_property_readonly(...)
     6. Bind 'shape' as a read-only property named 'shape' using .def_property_readonly(...)
    */
}
