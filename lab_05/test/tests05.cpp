#include <gtest/gtest.h>
#include "dynamic_memory_resource.hpp"
#include "dynamic_array.hpp"

// Тесты для DynamicMemoryResource
TEST(DynamicMemoryResourceTest, AllocateDeallocate) {
    DynamicMemoryResource memory_resource;
    void* ptr1 = memory_resource.allocate(1024, alignof(std::max_align_t));
    ASSERT_NE(ptr1, nullptr);
    memory_resource.deallocate(ptr1, 1024, alignof(std::max_align_t));

    void* ptr2 = memory_resource.allocate(1024, alignof(std::max_align_t));
    ASSERT_EQ(ptr1, ptr2);  // Проверяем, что повторно используется тот же блок памяти
    memory_resource.deallocate(ptr2, 1024, alignof(std::max_align_t));
}

TEST(DynamicMemoryResourceTest, IsEqual) {
    DynamicMemoryResource memory_resource1;
    DynamicMemoryResource memory_resource2;
    ASSERT_TRUE(memory_resource1.is_equal(memory_resource1));
    ASSERT_FALSE(memory_resource1.is_equal(memory_resource2));
}

// Тесты для DynamicArray
TEST(DynamicArrayTest, PushBackAndSize) {
    DynamicMemoryResource memory_resource;
    DynamicArray<int> array(&memory_resource);
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    ASSERT_EQ(array.size(), 3);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
}

TEST(DynamicArrayTest, Clear) {
    DynamicMemoryResource memory_resource;
    DynamicArray<int> array(&memory_resource);
    array.push_back(1);
    array.push_back(2);
    array.clear();
    ASSERT_EQ(array.size(), 0);
}

TEST(DynamicArrayTest, Iterator) {
    DynamicMemoryResource memory_resource;
    DynamicArray<int> array(&memory_resource);
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    int sum = 0;
    for (auto it = array.begin(); it != array.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}