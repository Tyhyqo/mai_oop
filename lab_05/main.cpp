#include "dynamic_memory_resource.hpp"
#include "dynamic_array.hpp"
#include <iostream>
#include <string>

struct ComplexType {
    int id;
    std::string name;

    ComplexType(int id, const std::string& name) : id(id), name(name) {}
};

int main() {
    DynamicMemoryResource memory_resource;
    std::pmr::polymorphic_allocator<int> int_allocator(&memory_resource);
    std::pmr::polymorphic_allocator<ComplexType> complex_allocator(&memory_resource);

    DynamicArray<int> int_array(int_allocator);
    int_array.push_back(1);
    int_array.push_back(2);
    int_array.push_back(3);

    std::cout << "Int array:" << std::endl;
    for (const auto& value : int_array) {
        std::cout << value << std::endl;
    }

    DynamicArray<ComplexType> complex_array(complex_allocator);
    complex_array.push_back(ComplexType(1, "Alice"));
    complex_array.push_back(ComplexType(2, "Bob"));
    complex_array.push_back(ComplexType(3, "Charlie"));

    std::cout << "Complex array:" << std::endl;
    for (const auto& value : complex_array) {
        std::cout << "ID: " << value.id << ", Name: " << value.name << std::endl;
    }

    return 0;
}