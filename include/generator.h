#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

namespace generator {
    std::vector<int> create_random_seq(size_t size, int min, int max); // N
    std::vector<int> create_convex_seq(size_t size, int min, int max); // M N>=M
    bool is_convex(const std::vector<int>& vec);
}