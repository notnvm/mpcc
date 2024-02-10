#include "solver.hpp"

void operations_research::RunKnapsackExample() {
  // Instantiate the solver.
    KnapsackSolver solver(
        KnapsackSolver::KNAPSACK_MULTIDIMENSION_BRANCH_AND_BOUND_SOLVER,
        "KnapsackExample");

    std::vector<int64_t> values = {
        360, 83, 59,  130, 431, 67, 230, 52,  93,  125, 670, 892, 600,
        38,  48, 147, 78,  256, 63, 17,  120, 164, 432, 35,  92,  110,
        22,  42, 50,  323, 514, 28, 87,  73,  78,  15,  26,  78,  210,
        36,  85, 189, 274, 43,  33, 10,  19,  389, 276, 312 };

    std::vector<std::vector<int64_t>> weights = {
        {7,  0,  30, 22, 80, 94, 11, 81, 70, 64, 59, 18, 0,  36, 3,  8,  15,
         42, 9,  0,  42, 47, 52, 32, 26, 48, 55, 6,  29, 84, 2,  4,  18, 56,
         7,  29, 93, 44, 71, 3,  86, 66, 31, 65, 0,  79, 20, 65, 52, 13} };

    std::vector<int64_t> capacities = { 850 };

    solver.Init(values, weights, capacities);
    int64_t computed_value = solver.Solve();

    // Print solution
    std::vector<int> packed_items;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (solver.BestSolutionContains(i)) packed_items.push_back(i);
    }
    std::ostringstream packed_items_ss;
    std::copy(packed_items.begin(), packed_items.end() - 1,
        std::ostream_iterator<int>(packed_items_ss, ", "));
    packed_items_ss << packed_items.back();

    std::vector<int64_t> packed_weights;
    packed_weights.reserve(packed_items.size());
    for (const auto& it : packed_items) {
        packed_weights.push_back(weights[0][it]);
    }
    std::ostringstream packed_weights_ss;
    std::copy(packed_weights.begin(), packed_weights.end() - 1,
        std::ostream_iterator<int>(packed_weights_ss, ", "));
    packed_weights_ss << packed_weights.back();

    int64_t total_weights =
        std::accumulate(packed_weights.begin(), packed_weights.end(), int64_t{ 0 });

    LOG(INFO) << "Total value: " << computed_value;
    LOG(INFO) << "Packed items: {" << packed_items_ss.str() << "}";
    LOG(INFO) << "Total weight: " << total_weights;
    LOG(INFO) << "Packed weights: {" << packed_weights_ss.str() << "}";
}

void operations_research::RunSmawkExample() {
    // std::vector<int> a{ generator::create_seq(10,1,100,0) };
    // std::vector<int> b{ generator::create_seq(10,1,100,1) };
    std::vector<int> a{ 3,2,5,2 };
    std::vector<int> b{ 1,2,4,7 };
    std::vector<int> res(a.size() + b.size() - 1);

    // for (auto elem : a)
    //     std::cout << elem << " ";
    // std::cout << "\n";
    // for (auto elem : b)
    //     std::cout << elem << " ";
    // std::cout << "\n";

    // std::vector<int> a1{ -2, 0, 3, 7, 12 };
    // std::vector<int> b1{ -1, -10, 14, 13, 22 };

    std::vector<int> c = smawk::mpcc(a, b);
    for (auto elem : c)
        std::cout << elem << " ";

    std::cout << "\n";
}