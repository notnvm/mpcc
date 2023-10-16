#include <benchmark/benchmark.h>
#include "lib.h"

std::vector<int> bench(std::vector<int>& a, std::vector<int>& b) {
    std::vector<int> c = smawk::mpcc(a, b);
    return c;
}

void mpcc_eqs(benchmark::State& state) {
    std::vector<int> a{ generator::create_seq(state.range(0), 1, 100, 0) };
    std::vector<int> b{ generator::create_seq(state.range(0), 1, 100, 1) };

    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            bench(a, b)
        );
    }
}
BENCHMARK(mpcc_eqs)->Name("< min,+ > - convex convolution: equal-size")->RangeMultiplier(10)->Range(10, 10'000'000)->Unit(benchmark::kMillisecond);

void mpcc_uneqs(benchmark::State& state) {
    std::vector<int> a{ generator::create_seq(state.range(0), 1, 100, 0) };
    std::vector<int> b{ generator::create_seq(10, 1, 100, 1) };

    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            bench(a, b)
        );
    }
}
BENCHMARK(mpcc_uneqs)->Name("< min,+ > - convex convolution: different-size")->RangeMultiplier(10)->Range(10, 10'000'000)->Unit(benchmark::kMillisecond);

void mpcc_all_zero(benchmark::State& state) {
    std::vector<int> a{ generator::create_seq(state.range(0), 0, 0, 0) };
    std::vector<int> b{ generator::create_seq(state.range(0), 0, 0, 1) };

    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            bench(a, b)
        );
    }
}
BENCHMARK(mpcc_eqs)->Name("< min,+ > - convex convolution: all-zero")->RangeMultiplier(10)->Range(10, 10'000'000)->Unit(benchmark::kMillisecond);

void mpcc_ab_convex(benchmark::State& state) {
    std::vector<int> a{ generator::create_seq(state.range(0), 1, 100, 1) };
    std::vector<int> b{ generator::create_seq(state.range(0), 1, 100, 1) };

    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            bench(a, b)
        );
    }
}
BENCHMARK(mpcc_eqs)->Name("< min,+ > - convex convolution: ab-convex")->RangeMultiplier(10)->Range(10, 10'000'000)->Unit(benchmark::kMillisecond);

void mpcc_small_size(benchmark::State& state) {
    std::vector<int> a{ generator::create_seq(state.range(0), 1, 100, 1) };
    std::vector<int> b{ generator::create_seq(state.range(0), 1, 100, 1) };

    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            bench(a, b)
        );
    }
}
BENCHMARK(mpcc_eqs)->Name("< min,+ > - convex convolution: small-size")->RangeMultiplier(2)->Range(1, 10)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();