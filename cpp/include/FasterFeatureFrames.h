#ifndef FASTERFEATUREFRAMES_H
#define FASTERFEATUREFRAMES_H

#include <vector>
#include <string>
#include <unordered_map>

// PYBIND11
#include <pybind11/pybind11.h>
// NUMPY
#include <pybind11/numpy.h>

namespace py = pybind11;

class FasterFeatureFrames
{
public:
    FasterFeatureFrames();
    ~FasterFeatureFrames();

    // Core functionality
    void add_column(const std::string& name, py::array col_data);
    py::array get_column(const std::string& name) const;
    
    std::vector<std::string> get_columns() const;

    // Aggregations
    double column_sum(const std::string& name) const;
    double column_mean(const std::string& name) const;
    double column_min(const std::string& name) const;
    double column_max(const std::string& name) const;

    // Arithmetic and Filtering
    py::array column_mul_scalar(const std::string& name, double scalar) const;
    py::array_t<bool> column_gt(const std::string& name, double value) const;

    // Schema and Inspection
    void drop_column(const std::string& name);

    std::pair<size_t, size_t> shape() const;

private:
    std::vector<std::string> columns;
    std::unordered_map<std::string, py::array> data;
    size_t num_rows;
};

#endif // FASTERFEATUREFRAMES_H