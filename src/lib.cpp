#include "lib.h"

#include <numeric>
// #include <cassert>
#include <exception>

namespace smawk {

    // source: https://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf
    template<typename Selector>
    std::vector<unsigned> smawk_(unsigned row_size, unsigned col_size, const Selector& select) {
        auto solve = [&](auto& solve, const std::vector<unsigned>& row, const std::vector<unsigned>& col) -> std::vector<unsigned> {
            // =========== BASE ===========
            const unsigned n = row.size();
            if (n == 0)
                return {};

            // =========== REDUCE ===========
            std::vector<unsigned> sc; // stack of surv colmns
            for (auto el : col) {
                while (!sc.empty()) {
                    if (select(row[sc.size() - 1], sc.back(), el) == sc.back()) break;
                    sc.pop_back();
                }
                if (sc.size() < n)
                    sc.push_back(el);
            }
            // =========== RECURSIVE ON ODD ROWS ===========
            
            std::vector<unsigned> odd;
            for (unsigned i = 1; i < n; i += 2)
                odd.push_back(row[i]);
            std::vector<unsigned> a2 = solve(solve, odd, sc);
            std::vector<unsigned> ans(n); 
            for (unsigned i = 0; i < a2.size(); ++i)
                ans[2 * i + 1] = a2[i];

            // =========== INTERPOLATE ===========
            unsigned j = 0;
            for (unsigned i = 0; i < n; i += 2) {
                const unsigned end = i + 1 == n ? col.back() : ans[i + 1];
                int best = col[j];
                while (col[j] < end) {
                    ++j;
                    best = select(row[i], best, col[j]);
                }
                ans[i] = best;
            }
            return ans;
            };

        std::vector<unsigned> row(row_size), col(col_size);
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

        int as = (int)a.size(); int bs = (int)b.size();
        int rs = as + bs - 1;

        const auto get = [&](const unsigned i, const unsigned j) { // get matrix elements
            return a[j] + b[i - j];
            };

        const auto select = [&](const unsigned i, const unsigned j, const unsigned k) {
            if (i < k)
                return j;
            if (i - j >= bs)
                return k;
            return get(i, j) > get(i, k) ? k : j;
            };

        std::vector<unsigned> argmin = smawk_(rs, as, select);
        // for (auto elem : argmin)
        //     std::cout << elem << " ";
        // std::cout << "\n";
        std::vector<int> c(rs);
        for (size_t i = 0; i < rs; ++i)
            c[i] = get(i, argmin[i]);
        return c;
    };
}