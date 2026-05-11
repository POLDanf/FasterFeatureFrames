import numpy as np

# Import the compiled pybind11 module
# try:
#     import _fasterfeatureframes_core
# except ImportError:
#     raise ImportError("Could not import _fasterfeatureframes_core. Did you compile the C++ extension?")

class DataFrame:
    """
    A pandas-like DataFrame backed by a fast C++ feature frame.
    """
    def __init__(self, data=None):
        """
        Initialize the DataFrame.
        
        TODO:
        1. Create an instance of the C++ FasterFeatureFrames object.
        2. If 'data' is provided (e.g., a dictionary where keys are column names 
           and values are lists/arrays), iterate through it.
        3. Convert each column's data to a 1D numpy array.
        4. Add each column to the C++ frame using its add_column method.
        """
        pass

    @property
    def columns(self):
        """
        Return the column names of the DataFrame.
        
        TODO:
        1. Call the corresponding property/method on the C++ frame to get column names.
        2. Return the result.
        """
        pass

    @property
    def shape(self):
        """
        Return the dimensionality of the DataFrame (rows, columns).
        
        TODO:
        1. Call the shape property/method on the C++ frame.
        2. Return the tuple (rows, cols).
        """
        pass

    def __getitem__(self, key):
        """
        Overloads df['col_name'] or df[['col1', 'col2']]
        
        TODO:
        1. Check if 'key' is a string. If so, return that single column from the C++ frame.
        2. Check if 'key' is a list of strings. If so, create a new dictionary containing 
           just those columns, and return a new DataFrame initialized with that dictionary.
        """
        pass

    def __setitem__(self, key, value):
        """
        Overloads df['col_name'] = value
        
        TODO:
        1. Check if 'key' is a string.
        2. Convert 'value' into a numpy array.
        3. Add this array as a new column to the C++ frame.
        """
        pass

    def __repr__(self):
        """
        Provide a pandas-like string representation.
        
        TODO:
        1. Get the shape and columns of the dataframe.
        2. Create a formatted string that shows the shape, the column headers,
           and the first few rows of data (similar to how pandas prints).
        3. Return the formatted string.
        """
        return "DataFrame skeleton"
