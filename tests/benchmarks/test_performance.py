import time
import sys
import os
import pandas as pd
import numpy as np

# Add the 'python' directory to the search path so we can find FasterFeatureFrames
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../python")))

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

    # Benchmark Aggregations and Arithmetic
    target_col = "column_0"
    print(f"\nBenchmarking operations on '{target_col}'...")

    def benchmark_op(name, pd_func, fff_func):
        t0 = time.perf_counter()
        pd_res = pd_func()
        t_pd = time.perf_counter() - t0

        t0 = time.perf_counter()
        fff_res = fff_func()
        t_fff = time.perf_counter() - t0
        
        speedup = t_pd / t_fff if t_fff > 0 else 0
        print(f"{name:<15} | Pandas: {t_pd:.6f}s | FFF: {t_fff:.6f}s | Speedup: {speedup:.2f}x")
        return pd_res, fff_res

    print("-" * 65)
    # Sum
    p_sum, f_sum = benchmark_op("Sum", lambda: df[target_col].sum(), lambda: frame.sum(target_col))
    # Mean
    p_mean, f_mean = benchmark_op("Mean", lambda: df[target_col].mean(), lambda: frame.mean(target_col))
    # Min/Max
    benchmark_op("Min", lambda: df[target_col].min(), lambda: frame.min(target_col))
    benchmark_op("Max", lambda: df[target_col].max(), lambda: frame.max(target_col))
    # Multiply Scalar
    p_mul, f_mul = benchmark_op("Mul Scalar", lambda: df[target_col] * 2.5, lambda: frame.mul_scalar(target_col, 2.5))
    # Greater Than
    p_gt, f_gt = benchmark_op("Greater Than", lambda: df[target_col] > 0.5, lambda: frame.gt(target_col, 0.5))
    print("-" * 65)

    # Verification of results
    np.testing.assert_allclose(f_sum, p_sum, rtol=1e-5)
    np.testing.assert_allclose(f_mean, p_mean, rtol=1e-5)
    np.testing.assert_allclose(f_mul, p_mul, rtol=1e-5)
    np.testing.assert_array_equal(f_gt, p_gt)
    
    assert frame.shape == (num_rows, num_cols), "Shape mismatch in FFF!"

    # Benchmark Drop Column
    print(f"\nTesting Drop Column on 'column_1'...")
    t0 = time.perf_counter()
    df.drop(columns=['column_1'], inplace=True)
    t_pd = time.perf_counter() - t0

    t0 = time.perf_counter()
    frame.drop('column_1')
    t_fff = time.perf_counter() - t0
    
    speedup_drop = t_pd / t_fff if t_fff > 0 else 0
    print(f"{'Drop Column':<15} | Pandas: {t_pd:.6f}s | FFF: {t_fff:.6f}s | Speedup: {speedup_drop:.2f}x")

    assert 'column_1' not in frame.columns, "Column 'column_1' still in FFF after drop!"
    assert frame.shape == (num_rows, num_cols - 1), "Shape mismatch after drop in FFF!"

if __name__ == "__main__":
    run_benchmark()
