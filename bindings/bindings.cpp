#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "../cpp/include/FasterFeatureFrames.h"

namespace py = pybind11;

PYBIND11_MODULE(_fasterfeatureframes_core, m) {
    m.doc() = "FasterFeatureFrames core C++ extension";

    py::class_<FasterFeatureFrames>(m, "FasterFeatureFrames")
        .def(py::init<>())
        .def("add_column", &FasterFeatureFrames::add_column)
        .def("get_column", &FasterFeatureFrames::get_column)
        .def("get_columns", &FasterFeatureFrames::get_columns)
        .def_property_readonly("columns", &FasterFeatureFrames::get_columns)
        .def("shape", &FasterFeatureFrames::shape)
        .def_property_readonly("shape", &FasterFeatureFrames::shape);
}
