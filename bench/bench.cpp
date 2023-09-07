#include <benchmark/benchmark.h>
#include "lib.h"

std::vector<int> mpcc_bench(size_t size, int min, int max) {
    std::vector<int> a{ generator::create_random_seq(size, min, max) };
    std::vector<int> b{ generator::create_convex_seq(size, min, max) };

    std::vector<int> c = smawk::mpcc(a, b);

    return c;
}

std::vector<int> mpcc_allzero_bench(size_t size) {
    std::vector<int> a{ generator::create_random_seq(size, 0, 0) };
    std::vector<int> b{ generator::create_random_seq(size, 0, 0) };

    std::vector<int> c = smawk::mpcc(a, b);

    return c;
}

void mpcc_eqs(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            mpcc_bench(state.range(0), 1, 100)
        );
    }
}
BENCHMARK(mpcc_eqs)->Name("< min,+ > - convex convolution: equal-size")->RangeMultiplier(10)->Range(10, 1'000'000)->Unit(benchmark::kMillisecond);

void mpcc_all_zero(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            mpcc_allzero_bench(state.range(0))
        );

    }
}
BENCHMARK(mpcc_eqs)->Name("< min,+ > - convex convolution: all-zero")->RangeMultiplier(10)->Range(10, 1'000'000)->Unit(benchmark::kMillisecond);

void mpcc_small_size(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            mpcc_allzero_bench(state.range(0))
        );
    }
}
BENCHMARK(mpcc_eqs)->Name("< min,+ > - convex convolution: small-size")->RangeMultiplier(2)->Range(1, 10)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();