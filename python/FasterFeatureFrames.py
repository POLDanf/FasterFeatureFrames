import numpy as np

# Import the compiled pybind11 module
try:
    import _fasterfeatureframes_core
except ImportError:
    raise ImportError("Could not import _fasterfeatureframes_core. Did you compile the C++ extension?")

class DataFrame:
    """
    A pandas-like DataFrame backed by a fast C++ feature frame.
    """
    def __init__(self, data=None):
        self._core = _fasterfeatureframes_core.FasterFeatureFrames()
        if data is not None:
            for col_name, col_data in data.items():
                self[col_name] = col_data

    @property
    def columns(self):
        return self._core.get_columns()

    @property
    def shape(self):
        return self._core.shape

    def __getitem__(self, key):
        if isinstance(key, str):
            return self._core.get_column(key)
        elif isinstance(key, list):
            # Selection of multiple columns
            new_data = {col: self._core.get_column(col) for col in key}
            return DataFrame(new_data)
        raise TypeError(f"Invalid key type: {type(key)}")

    def __setitem__(self, key, value):
        if not isinstance(key, str):
            raise TypeError("Column name must be a string")
        
        # Ensure data is a 1D numpy array
        arr = np.ascontiguousarray(value, dtype=np.float64)
        self._core.add_column(key, arr)

    def __repr__(self):
        cols = self.columns
        rows, num_cols = self.shape
        res = f"FasterFeatureFrame: {rows} rows x {num_cols} columns\n"
        res += "Columns: [" + ", ".join(cols[:10]) + ("..." if num_cols > 10 else "") + "]"
        return res
