#include "lib.hpp"

#include <numeric>
// #include <cassert>
#include <exception>

namespace smawk {

    // source: https://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf
    template<typename Selector>
    std::vector<size_t> smawk_(size_t row_size, size_t col_size, const Selector& select) {
        auto solve = [&](auto& solve, const std::vector<size_t>& row, const std::vector<size_t>& col) -> std::vector<size_t> {
            const size_t n = row.size();
            if (n == 0)
                return {};

            std::vector<size_t> sc;
            for (auto el : col) {
                while (!sc.empty()) {
                    if (select(row[sc.size() - 1], sc.back(), el) == sc.back()) break;
                    sc.pop_back();
                }
                if (sc.size() < n)
                    sc.push_back(el);
            }
            
            std::vector<size_t> odd;
            for (size_t i = 1; i < n; i += 2)
                odd.push_back(row[i]);
            std::vector<size_t> a2 = solve(solve, odd, sc);
            std::vector<size_t> ans(n);
            for (size_t i = 0; i < a2.size(); ++i)
                ans[2 * i + 1] = a2[i];

            size_t j = 0;
            for (size_t i = 0; i < n; i += 2) {
                const size_t end = i + 1 == n ? col.back() : ans[i + 1];
                int best = col[j];
                while (col[j] < end) {
                    ++j;
                    best = select(row[i], best, col[j]);
                }
                ans[i] = best;
            }
            return ans;
            };

        std::vector<size_t> row(row_size), col(col_size);
        std::iota(row.begin(), row.end(), 0); std::iota(col.begin(), col.end(), 0);
        return solve(solve, row, col);
    };

    std::vector<int> mpcc(std::vector<int>& a, std::vector<int>& b) {
        if (a.size() == 0 || b.size() == 0)
            return std::vector<int>{};

        if (!generator::is_convex(a) && !generator::is_convex(b))
            throw std::logic_error("a and b is not convex");

        // assert(generator::is_convex(a) || generator::is_convex(b));
        if (!generator::is_convex(b))
            std::swap(a, b);

        size_t as = a.size(); size_t bs = b.size();

        if (!(as >= bs))
            throw std::logic_error("n < m");

        size_t rs = as + bs - 1;

        const auto get = [&](const size_t i, const size_t j) {
            return a[j] + b[i - j];
            };

        const auto select = [&](const size_t i, const size_t j, const size_t k) {
            if (i < k)
                return j;
            if (i - j >= bs)
                return k;
            return get(i, j) > get(i, k) ? k : j;
            };

        std::vector<size_t> argmin = smawk_(rs, as, select);
        std::vector<int> c(rs);
        for (size_t i = 0; i < rs; ++i)
            c[i] = get(i, argmin[i]);
        return c;
    };
}