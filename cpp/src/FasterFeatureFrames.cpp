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

double FasterFeatureFrames::column_sum(const std::string& name) const {
    /*
     TODO:
     1. Retrieve the column using get_column(name).
     2. Cast the py::array to py::array_t<double> for typed access.
     3. Use .data() or .unchecked<1>() to get a pointer to the raw memory.
     4. Iterate through num_rows and accumulate the sum.
     5. Return the result.
    */
    auto col_data = get_column(name).cast<py::array_t<double, py::array::c_style | py::array::forcecast>>();
    const double* ptr = col_data.data();
    double sum = 0.0;
    for (size_t i = 0; i < num_rows; ++i) {
        sum += ptr[i];
    }
    return sum;
}

double FasterFeatureFrames::column_mean(const std::string& name) const {
    /*
     TODO:
     1. Check if num_rows is greater than 0 to avoid division by zero.
     2. Calculate the sum using column_sum(name).
     3. Return sum / num_rows.
    */
    double sum = column_sum(name);
    if(num_rows > 0){
        return sum / num_rows;
    }
    return 0.0;
}

double FasterFeatureFrames::column_min(const std::string& name) const {
    /*
     TODO:
     1. Retrieve the column and cast to py::array_t<double>.
     2. Initialize a 'min' variable with the first element or infinity.
     3. Loop through the data and update 'min' if a smaller value is found.
     4. Return 'min'.
    */
    auto col_data = get_column(name).cast<py::array_t<double, py::array::c_style | py::array::forcecast>>();
    if (num_rows == 0) {
        throw std::runtime_error("Cannot calculate min of empty column");
    }
    const double* ptr = col_data.data();
    double min = ptr[0];
    for (size_t i = 1; i < num_rows; ++i) {
        if (ptr[i] < min) {
            min = ptr[i];
        }
    }
    return min;
}

double FasterFeatureFrames::column_max(const std::string& name) const {
    /*
     TODO:
     1. Retrieve the column and cast to py::array_t<double>.
     2. Initialize a 'max' variable with the first element or -infinity.
     3. Loop through the data and update 'max' if a larger value is found.
     4. Return 'max'.
    */
    auto col_data = get_column(name).cast<py::array_t<double, py::array::c_style | py::array::forcecast>>();
    if (num_rows == 0) {
        throw std::runtime_error("Cannot calculate max of empty column");
    }
    const double* ptr = col_data.data();
    double max = ptr[0];
    for (size_t i = 1; i < num_rows; ++i) {
        if (ptr[i] > max) {
            max = ptr[i];
        }
    }
    return max;
}

py::array FasterFeatureFrames::column_mul_scalar(const std::string& name, double scalar) const {
    /*
     TODO:
     1. Retrieve the original column.
     2. Create a new py::array_t<double> of size 'num_rows' for the result.
     3. Get pointers to both input and output memory.
     4. Loop through the data: output[i] = input[i] * scalar.
     5. Return the new array.
    */
    auto col_data = get_column(name).cast<py::array_t<double, py::array::c_style | py::array::forcecast>>();
    py::array_t<double> res(std::vector<ptrdiff_t>{(ptrdiff_t)num_rows});
    
    const double* in_ptr = col_data.data();
    double* out_data = res.mutable_data();

    for (size_t i = 0; i < num_rows; ++i) {
        out_data[i] = in_ptr[i] * scalar;
    }
    return res;
}

py::array_t<bool> FasterFeatureFrames::column_gt(const std::string& name, double value) const {
    /*
     TODO:
     1. Retrieve the column and cast to py::array_t<double>.
     2. Allocate a new py::array_t<bool> of size 'num_rows'.
     3. Get the raw input pointer (const double*) and raw output pointer (bool*).
     4. Iterate through num_rows: out_ptr[i] = in_ptr[i] > value.
     5. Return the boolean mask.
    */
    auto col_data = get_column(name).cast<py::array_t<double, py::array::c_style | py::array::forcecast>>();
    py::array_t<bool> res(std::vector<ptrdiff_t>{(ptrdiff_t)num_rows});
    const double* in_ptr = col_data.data();
    bool* out_data = res.mutable_data();
    for (size_t i = 0; i < num_rows; ++i) {
        out_data[i] = in_ptr[i] > value;
    }
    return res;
}

void FasterFeatureFrames::drop_column(const std::string& name) {
    /*
     TODO:
     1. Check if the column exists in the 'data' map.
     2. If it exists, erase the entry from the 'data' unordered_map.
     3. Find and remove the column name from the 'columns' vector to keep the schema in sync.
     4. If the DataFrame becomes empty (no columns left), consider resetting 'num_rows' to 0.
    */
    auto it = data.find(name);
    if (it != data.end()) {
        data.erase(it);


        for (auto v_it = columns.begin(); v_it != columns.end(); ++v_it) {
            if (*v_it == name) {
                columns.erase(v_it);
                break;
            }
        }

        if (columns.empty()) {
            num_rows = 0;
        }
    }
}

std::pair<size_t, size_t> FasterFeatureFrames::shape() const {
    /*
     TODO:
     1. Return a std::pair containing 'num_rows' and the number of columns (size of 'columns' vector).
    */
    return {num_rows, columns.size()};
}
