#include "lib.h"

int main() {
    std::vector<int> a{ generator::create_seq(10,1,100,0) };
    std::vector<int> b{ generator::create_seq(10,1,100,1) };
    std::vector<int> res(a.size() + b.size() - 1);

    for (auto elem : a)
        std::cout << elem << " ";
    std::cout << "\n";
    for (auto elem : b)
        std::cout << elem << " ";
    std::cout << "\n";

    std::vector<int> c = smawk::mpcc(a, b);
    for (auto elem : c)
        std::cout << elem << " ";

    return 0;
}