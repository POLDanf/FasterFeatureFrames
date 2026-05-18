import time
import pandas as pd
import numpy as np
try:
    import FasterFeatureFrames as fff
except ImportError:
    print("Error: FasterFeatureFrames module not found. Please compile the C++ extension first.")
    exit(1)

def run_benchmark(num_rows=1_000_000, num_cols=50):
    print(f"Generating {num_rows} rows and {num_cols} columns of random data...")
    data = {f"column_{i}": np.random.randn(num_rows) for i in range(num_cols)}
    
    # Benchmark Pandas
    print("Benchmarking Pandas...")
    start_pd = time.perf_counter()
    df = pd.DataFrame()
    for name, col_data in data.items():
        df[name] = col_data
    end_pd = time.perf_counter()
    pd_duration = end_pd - start_pd
    
    # Benchmark FasterFeatureFrames
    print("Benchmarking FasterFeatureFrames...")
    start_fff = time.perf_counter()
    frame = fff.DataFrame()
    for name, col_data in data.items():
        frame[name] = col_data
    end_fff = time.perf_counter()
    fff_duration = end_fff - start_fff
    
    # Results
    print("\n" + "="*30)
    print(f"RESULTS ({num_rows} rows, {num_cols} cols)")
    print("="*30)
    print(f"Pandas time:                {pd_duration:.4f}s")
    print(f"FasterFeatureFrames time:    {fff_duration:.4f}s")
    
    if fff_duration > 0:
        speedup = pd_duration / fff_duration
        print(f"Speedup:                    {speedup:.2f}x")
    
    assert frame.shape == (num_rows, num_cols), "Shape mismatch in FFF!"

if __name__ == "__main__":
    run_benchmark()
