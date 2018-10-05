#include "myAllocator.h"

int main() {
    myAllocator* alloc = myAllocator::getAllocator();
    void* p = alloc->allocate(10);
    void* q = alloc->allocate(10);
    alloc->deallocate(p, 10);
}