#include "generator.h"

std::vector<int> generator::create_random_seq(size_t size, int min, int max) {

    if (size == 0)
        return std::vector<int>{};

    std::vector<int> a;
    a.reserve(size);

    std::mt19937 engine{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(min, max);

    std::generate_n(std::back_inserter(a), size, [&] {return dist(engine);});

    return a;
}

std::vector<int> generator::create_convex_seq(size_t size, int min, int max) {

    if (size == 0)
        return std::vector<int>{};
    
    std::vector<int> b;
    b.reserve(size);

    std::mt19937 engine{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(min, max);

    b.push_back(dist(engine));
    for (size_t i = 1; i < size; ++i) {
        b.push_back(b[i - 1] + i);
    }

    return b;
}

bool generator::is_convex(const std::vector<int>& vec) {
    if (vec.empty())
        return false;
    for (size_t i = 1; i < vec.size() - 1; ++i)
        if (!(vec[i + 1] - vec[i] >= vec[i] - vec[i - 1])) // 2*vec[i] <= v[i-1] + vec[i+1] -> vec[i+1] = 2*vec[i] - vec[i-1]
            return false;
    return true;
}