#include "../include/FasterFeatureFrames.h"
#include <stdexcept>

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
}

py::array FasterFeatureFrames::get_column(const std::string& name) const {
    /*
     TODO:
     1. Look up 'name' in the 'data' unordered_map.
     2. If found, return the py::array.
     3. If not found, throw an std::invalid_argument.
    */
    return py::array(); // Placeholder return
}

std::vector<std::string> FasterFeatureFrames::get_columns() const {
    /*
     TODO:
     1. Return the 'columns' vector.
    */
    return std::vector<std::string>(); // Placeholder return
}

std::pair<size_t, size_t> FasterFeatureFrames::shape() const {
    /*
     TODO:
     1. Return a std::pair containing 'num_rows' and the number of columns (size of 'columns' vector).
    */
    return {0, 0}; // Placeholder return
}