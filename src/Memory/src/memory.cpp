#include "../memory.h"

Memory::Memory(size_t heapSize, size_t stackSize) {
    _heap = new unsigned char[heapSize];
    _reservedStackMemory = new unsigned char[stackSize];
    // Intitialize the head pointer
    _startPtr = _heap;
}


void* Memory::malloc(size_t size) {
    // Get the requested size
    // Caculate the request size + the size of the header
    size_t totalRequestSize = size + sizeof(header);
    
    // Get the current offset
    size_t currOffset = (size_t) _startPtr + _offset;

    size_t reqestedHeaderPos = currOffset + sizeof(header);

    // Convert the first n bytes into a header malloc
    header* headerBlock = (header*) reqestedHeaderPos
    header header{size};
    headerBlock = &header;

    // Finally get the requested size
    (void *) request = currOffset + reqestedHeaderPos;
    // Add to offset
    _offset += (size_t) request;
    return request;
}


void Memory::free(void* loc) {
    // Header = loc - sizeof(header) because pointers point to the begining
    header* header = (header*) (size_t)loc-size;
    // Attain pointed to header value
    header pointee = *header;

    // Attain allocated size
    size_t allocatedSize = pointee.size;


     // Move the offset back by that 
     _offset -= allocatedSize + sizeof(header);
}