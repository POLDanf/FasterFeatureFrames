#include "../include/FasterFeatureFrames.h"
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

FasterFeatureFrames::FasterFeatureFrames() : num_rows(0)
{
    // Constructor
}

FasterFeatureFrames::~FasterFeatureFrames()
{
    // Destructor
}

void FasterFeatureFrames::add_column(const std::string& name, py::array col_data) {
    /*
     TODO:
     1. Check if col_data is a 1D array. If not, throw an std::invalid_argument.
     2. Get the number of rows in this new column.
     3. If this is the first column being added, set 'num_rows' to this size.
     4. If it's not the first column, ensure its size matches 'num_rows'. If not, throw an error.
     5. If this column name doesn't exist yet, add the name to the 'columns' vector to maintain order.
     6. Store the 'col_data' array in the 'data' unordered_map using 'name' as the key.
    */
    if(col_data.ndim() != 1){
        throw std::invalid_argument("Column data must be a 1D array");
    }
    size_t current_col_rows = col_data.shape()[0];
    if(num_rows == 0){
        num_rows = current_col_rows;
    }
    else if(num_rows != current_col_rows){
        throw std::invalid_argument("Column data must match the number of rows");
    }
    if(this->data.find(name) == this->data.end()){
        this->columns.push_back(name);
    }
    this->data[name] = col_data;
}

py::array FasterFeatureFrames::get_column(const std::string& name) const {
    /*
     TODO:
     1. Look up 'name' in the 'data' unordered_map.
     2. If found, return the py::array.
     3. If not found, throw an std::invalid_argument.
    */
    auto it = data.find(name);
    if (it == data.end()) {
        throw std::invalid_argument("Column '" + name + "' not found");
    }
    return it->second;
}

std::vector<std::string> FasterFeatureFrames::get_columns() const {
    /*
     TODO:
     1. Return the 'columns' vector.
    */
    return columns;
}

std::pair<size_t, size_t> FasterFeatureFrames::shape() const {
    /*
     TODO:
     1. Return a std::pair containing 'num_rows' and the number of columns (size of 'columns' vector).
    */
    return {num_rows, columns.size()};
}
