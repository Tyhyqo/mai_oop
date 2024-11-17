#include "dynamic_memory_resource.hpp"

void* DynamicMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    if (!free_blocks_.empty()) {
        void* ptr = free_blocks_.back();
        free_blocks_.pop_back();
        return ptr;
    } else {
        void* ptr = std::aligned_alloc(alignment, bytes);
        allocated_blocks_.push_back(ptr);
        return ptr;
    }
}

void DynamicMemoryResource::do_deallocate(void* p, std::size_t /*bytes*/, std::size_t /*alignment*/) {
    free_blocks_.push_back(p);
}

bool DynamicMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

DynamicMemoryResource::~DynamicMemoryResource() {
    for (void* ptr : allocated_blocks_) {
        std::free(ptr);
    }
    allocated_blocks_.clear();
    free_blocks_.clear();
}