#include <iostream>
#include "include/closed_pair_tonum.h"

int main() {
    std::cout << "Input upper limit: ";
    int upperLimit = 0;
    std::cin >> upperLimit;
    if (const std::vector<int> res = closestPairTonum(upperLimit); res.empty()) {
        std::cout << "No closest pair tonum found" << std::endl;
    } else {
        const int a = res[0];
        const int b = res[1];
        std::cout << "Result: " << a << ", " << b << std::endl;
    }
    return 0;
}
