#include "lib/lib.hpp"

int main() {
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

    return 0;
}