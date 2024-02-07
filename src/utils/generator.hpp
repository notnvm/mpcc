#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

namespace generator {
    std::vector<int> create_seq(size_t size, int min, int max, bool convex);
    bool is_convex(const std::vector<int>& vec);
}