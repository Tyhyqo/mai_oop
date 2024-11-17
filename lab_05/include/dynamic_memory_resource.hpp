#ifndef DYNAMIC_MEMORY_RESOURCE_HPP
#define DYNAMIC_MEMORY_RESOURCE_HPP

#include <memory_resource>
#include <vector>
#include <cstdlib>

class DynamicMemoryResource : public std::pmr::memory_resource {
private:
    std::vector<void*> allocated_blocks_;
    std::vector<void*> free_blocks_;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    ~DynamicMemoryResource();
};

#include "dynamic_memory_resource.cpp"

#endif // DYNAMIC_MEMORY_RESOURCE_HPP