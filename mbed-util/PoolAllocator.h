// Copyright (C) 2015 ARM Limited. All rights reserved.

#ifndef __MBED_UTIL_POOL_ALLOCATOR_H__
#define __MBED_UTIL_POOL_ALLOCATOR_H__

#include <stddef.h>

// [TODO] this should probably be 8, but at the moment our allocators are 
// aligned at 4 bytes
// [TODO] where should the system allocator alignment be defined?
#define MBED_UTIL_POOL_ALLOC_DEFAULT_ALIGN       4

namespace mbed {
namespace util {

/** A simple pool allocator class. It can allocate one elements oe 'element_size' bytes at a time.
  * alloc() and free() operations are synchronized, they can be used safely from both user
  * and interrupt context.
  */
class PoolAllocator {
public:
    /** Create a new pool allocator
      * @param start pool start address
      * @param elements the size of pool in elements (each of element_size bytes)
      * @param element_size size of each pool element in bytes (this might be rounded up
               to satisfy the 'alignment' argument)
      * @param alignment allocation alignment in bytes
      */
    PoolAllocator(void *start, size_t elements, size_t element_size, unsigned alignment = MBED_UTIL_POOL_ALLOC_DEFAULT_ALIGN);

    /** Allocate a new element from the pool
     * @returns the address of the new element or NULL for error
      */
    void* alloc();

    /** Allocate a new element from the pool and initialize it with 0
      * @returns the address of the new element or NULL for error
      */
   void *calloc();

    /** Free a previously allocated element
      * @param p pointer to element
      */
    void free(void* p);

    /** Returns a pool size suitable to hold the required number of elements
      * @param elements the size of pool in elements (each of element_size bytes)
      * @param element_size size of each pool element in bytes (this might be rounded up
               to satisfy the 'alignment' argument)
      * @param alignment allocation alignment in bytes
      * @returns the size of the pool in bytes
      */
    static size_t get_pool_size(size_t elements, size_t element_size, unsigned alignment = MBED_UTIL_POOL_ALLOC_DEFAULT_ALIGN);

    /** Check if this pool owns a pointer
      * @param p the pointer to check
      * @returns true if the pointer is inside this pool, false otherwise
      */
    bool owns(void *p) const;

private:
    void _init();

    void *_start, *_free_block, *_end;
    size_t _element_size;
};

} // namespace util
} // namespace mbed

#endif // #ifndef __MBED_UTIL_POOL_ALLOCATOR_H__
