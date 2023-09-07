# convex convolution
### 
***
_Two vectors **a**, **b** of size **N**, **M** are given. One of these vectors is convex i.e._ $$ f(i+1) - f(i) \geq f(i) - f(i-1)\; \forall i $$ 
_Convex (min,plus) convolution calculates vector **c** in $ O(N+M) $ time complexity using the following rule:_
$$ c_k = \min_{i+j=k} \{a_i + b_j\} $$

***
### Building

- Release build
```
cmake -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release .
cmake --build build
```
- Debug build
```
cmake -B debug -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug .
cmake --build debug
```
***
### Usage  
After building there are would be 3 files you need in **build/debug** directory:
- main file ```./out```
- tests ```./test_out```
- benchmarks ```./g_bench``` or ```./g_bench --benchmark_format=json > <your_filename>.json``` to write result to <your_filename>.json file
