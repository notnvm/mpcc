#include "generator.hpp"

std::vector<int> generator::create_seq(size_t size, int min, int max, bool convex) {

    if (size == 0)
        return std::vector<int>{};

    std::vector<int> vec;
    vec.reserve(size);

    std::mt19937 engine{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(min, max);

    if(!convex)
        std::generate_n(std::back_inserter(vec), size, [&] {return dist(engine);});
    else {
        vec.push_back(dist(engine));
        for (size_t i = 1; i < size; ++i) {
            vec.push_back(vec[i - 1] + i);
        }
    }

    return vec;
}

bool generator::is_convex(const std::vector<int>& vec) {
    if (vec.empty())
        return false;
    for (size_t i = 1; i < vec.size() - 1; ++i)
        if (!(vec[i + 1] - vec[i] >= vec[i] - vec[i - 1])) // 2*vec[i] <= v[i-1] + vec[i+1] -> vec[i+1] = 2*vec[i] - vec[i-1]
            return false;
    return true;
}