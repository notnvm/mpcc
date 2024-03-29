# convex convolution && knapsack
### 
***

_Two vectors **a**, **b** of size **N**, **M** are given. One of these vectors is convex._
_Convex (min,plus) convolution calculates vector **c** in  O(N+M)  time complexity._ 

***
### Building

- Install google or-tools 
  
install ortools in **root** of your **working** directory. https://developers.google.com/optimization/install/cpp

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
- main file ```./mpcc_bin```
- tests ```./mpcc_tests```
- benchmarks ```./mpcc_bench``` or ```./mpcc_bench --benchmark_format=json > your_filename.json``` to write result to **your_filename.json** file
- plot results ```python3 scripts/plot_data.py your_filename.json bench_type``` 
- bench types: ```all-zero```; ```ab-convex```; ```equal-size```; ```small-size```; ```different-size```
***
### Results
- Sequences a and b are **equal-sized**:
  
![plot](./scripts/pics/equal-size.jpg)

- **Small size**:
  
![plot](./scripts/pics/small-size.jpg)

- **Different sizes**:
  
![plot](./scripts/pics/different-size.jpg)
