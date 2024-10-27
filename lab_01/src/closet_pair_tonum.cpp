#include "closed_pair_tonum.h"

std::vector<int> closestPairTonum(const int upperLimit) {
    std::vector<int> res;
    for (int a = upperLimit - 1; a > 0; a--) {
        for (int b = a - 1; b > 0; b--) {
            if (std::sqrt(a + b) == static_cast<int>(std::sqrt(a + b)) and
                std::sqrt(a - b) == static_cast<int>(std::sqrt(a - b))) {
                res.push_back(a);
                res.push_back(b);
                return res;
            }
        }
    }
    return res;
}
