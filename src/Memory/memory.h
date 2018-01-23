#ifndef RAM_H_
#define RAM_H_

#include "../Common/Stack/stack.h"
#include <cstdint>

typedef size_t unsigned int;

// Memory model:
// Heap for dynamic allocation

// Memory class is meant to act as a linear heap allocator
class Memory {
public:
    // Allocator acts as a stack allocator, you can find details on the stack allocator here:
    // https://github.com/mtrebi/memory-allocators#stack-allocator

    // Header struct as per the specifications headers sits on top of the allocated memory:
    // E.g.
    /*
    * [=====]  = memory, [##] = header
    * [##][=======][##][========]
    */
    static struct header {
        size_t size;
    }

    Memory(size_t heapSize, size_t stackSize);
    void* malloc(size_t size);
    void free(void* loc);
    void* realloc(void* loc);
    
private:
    unsigned char* _reservedStackMemory;
    unsigned char* _heap;

    // Offset that holds the total leased memory
    size_t _offset;
    // Start pointer
    void* _startPtr;
};

#endif