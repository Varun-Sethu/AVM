#define __DEBUG

#include "Memory.h"
#ifdef __DEBUG
#include <iostream>
#endif // __DEBUG

// TODO: Optamised and reduce the number of vars created
// TODO: Add allignment and fix the allignment issues we are having



/// TESTED =======
// Constructor 
Runtime::Memory::Memory(unsigned int stackSize, unsigned int heapSize) {
    this->_heap =  (char*) std::malloc(heapSize);
    this->_stack = (char*) std::malloc(stackSize); 
    _heapSize = heapSize;


    // Create an allocation to the first header
    void* block = this->alloc(10);
    this->_header = (Runtime::Util::Header*) ((char*) block - sizeof(Runtime::Util::Header));
}


/// TESTED =======
// Destructor
Runtime::Memory::~Memory() {
    std::free((void*)_stack);
    std::free((void*)_heap);
}



/// TESTED =======
// Allocation functiont that allocates a block of memory given a specific size
void* Runtime::Memory::alloc(unsigned int size) {
    const int HEADER_SIZE = sizeof(Runtime::Util::Header);

    // First determine if any memory can even be allocated
    if (_offset + size + HEADER_SIZE >= _heapSize) {
        // Extend the heap by 10x the rquested size
        this->realloc(_heap, size * 10);
    } 



    // Start a new allocation from the offset pointer
    char* newAddr = (char*) (_heap + _offset + size + HEADER_SIZE);
    uintptr_t headerLoc = (uintptr_t) (newAddr - HEADER_SIZE);

    // Create a header struct to hold our info
    Runtime::Util::Header header{size, false};


    // Setup the header part of the allocation
    Runtime::Util::Header *headerptr = (Runtime::Util::Header*) headerLoc;
    *headerptr = header;


    #ifdef __DEBUG
        std::cout << std::endl << "REQUEST: " << std::endl << "REQUEST SIZE: " << size + HEADER_SIZE << "\n\n"; 
        std::cout << "ALLOC HEADER: " << (int*) headerLoc << std::endl;
        std::cout << "ALLOC BLOCK: " << (int*) newAddr << std::endl;
    #endif // __DEBUG



    // Set our offset so it is just a bit easier to type up next time
    _offset += size + HEADER_SIZE;


    // Returnt he allocated block minus the actual header
    return (void*) (newAddr);
}




/// TESTED =======
// Free function that just frees a block of memory
void Runtime::Memory::free(void* memoryLoc) {
    const int HEADER_SIZE = sizeof(Runtime::Util::Header);
    
    // Determine the location fo the header so that we can eaislly delete what has bene requested
    const uintptr_t location = (uintptr_t) memoryLoc;
    Runtime::Util::Header *header{(Runtime::Util::Header*) (location - HEADER_SIZE)};
    // Get the sizde of the block requested for deleteion
    uint32_t size = header->size;


    // Override the block of memory
    *((char*) memoryLoc) = NULL;

    // Delete and free the block
    header->flagDeletion = true;
}




/// NOT TESTED =======
// Realloc function just resizes a block of memory
void* Runtime::Memory::realloc(void* memoryLoc, unsigned int size) {
    const uintptr_t HEADER_SIZE = sizeof(Runtime::Util::Header);

    // First we need to get the header to get the size of the actual block
    char* headerLocation = ((char*) memoryLoc) - HEADER_SIZE;

    // Convert to actual pointer
    Runtime::Util::Header *header{(Runtime::Util::Header*) headerLocation};
    const uint32_t memSize = header->size;

    // We do this because if we try and access this later the program will segfault
    unsigned int requuestedSize = memSize + size;
    // Create a temp buffer
    char* buffer = new char[memSize];
    // Copy our contents into a buffer
    std::memcpy(buffer, memoryLoc, memSize);

    // Free the current memoryLoc, this will defragment the current heap so it might take some time
    this->free(memoryLoc);
    
    // Create a new allocation
    void* location = this->alloc(requuestedSize);
    
    // Copy the contents from the buffer into the location
    std::memcpy(location, buffer, sizeof(buffer));
    // Delete the bffer so we dont have any memory leaks
    delete buffer;

    return location;
}




/// TESTED =======
// Function extens the current size of the heap, this is an internal function
void Runtime::Memory::extendHeap(unsigned int size) {
    realloc(_heap, size);
    _heapSize += size;
}



// Defragmenting is really easy because of the deletetion method we have set up and our header structure which enables marking of objects to be deleted
void Runtime::Memory::defragment() { 
    // Iterate over every single block
    // Attain the first header block, aka the current offset
    uintptr_t offset = 0;
    // The current amount we should move all the blocks back
    unsigned int moveBackPointer = 0;
    // Iterate until we are "done"
    for(int i = 0; i < 2; i++) {
        // Segfault protection
        // When the offset reaches the size of the heap no more data is avaliable to be defragmented
        if (_heapSize == offset) {
            break;
        }

        // Get the header for the block
        const uintptr_t headerLocation = (uintptr_t) _header + offset;
        Runtime::Util::Header *header{(Runtime::Util::Header*) headerLocation};        



        // Check if this block is allowed to be deleted, if it is then we set a move back pointer and eventually the block will be overriden
        // MAGIC ;) 
        if (header->flagDeletion) {
            moveBackPointer += header->size + sizeof(Runtime::Util::Header);
        // If the moveback pointer is non-zero and the block is not flagged for deletion we can delete it
        } else if (offset != 0) {
            // Create a new location with the given size of this block
            unsigned int dedicatedSize = header->size + sizeof(Runtime::Util::Header);
            // Set our offset to its current position
            offset += dedicatedSize;


            // Move back the current block to its current position - the move back pointer
            // Old position = header position + size of block
            uintptr_t oldPos = (uintptr_t) (header + header->size);
            void* newPos = (void*) (oldPos - moveBackPointer);

            // Copy the contents of the old location into the new one
            // We cal call sizeof old pos coz we are going to treat it like a char array
            std::memcpy(newPos, (void*) oldPos, sizeof((char*) oldPos));
        }
        // Set the offest again
        offset += header->size + sizeof(Runtime::Util::Header);
    }
}