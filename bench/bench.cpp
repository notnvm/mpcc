#include <benchmark/benchmark.h>
#include "lib.h"

std::vector<int> mpcc_bench(size_t size_a, size_t size_b, int min, int max) {
    std::vector<int> a{ generator::create_seq(size_a, min, max, 0) };
    std::vector<int> b{ generator::create_seq(size_b, min, max, 1) };

    std::vector<int> c = smawk::mpcc(a, b);

    return c;
}

std::vector<int> mpcc_allzero_bench(size_t size) {
    std::vector<int> a{ generator::create_seq(size, 0, 0, 0) };
    std::vector<int> b{ generator::create_seq(size, 0, 0, 1) };

    std::vector<int> c = smawk::mpcc(a, b);

    return c;
}

void mpcc_eqs(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            mpcc_bench(state.range(0), state.range(0), 1, 100)
        );
    }
}
BENCHMARK(mpcc_eqs)->Name("< min,+ > - convex convolution: equal-size")->RangeMultiplier(10)->Range(10, 1'000'000)->Unit(benchmark::kMillisecond);

void mpcc_uneqs(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            mpcc_bench(state.range(0), 10, 1, 100)
        );
    }
}
BENCHMARK(mpcc_uneqs)->Name("< min,+ > - convex convolution: unequal-size(M - const)")->RangeMultiplier(10)->Range(10, 1'000'000)->Unit(benchmark::kMillisecond);

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