#include <gtest/gtest.h>
#include "../include/closed_pair_tonum.h"

TEST(test_01, basic_test_set)
{
    const std::vector<int> res{5, 4};
    ASSERT_TRUE(closestPairTonum(10)==res);
}

TEST(test_02, basic_test_set)
{
    const std::vector<int> res{29, 20};
    ASSERT_TRUE(closestPairTonum(30)==res);
}

TEST(test_03, basic_test_set)
{
    const std::vector<int> res{45, 36};
    ASSERT_TRUE(closestPairTonum(50)==res);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
