#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <stdio.h>
#include <cstdlib> 
#include <cstring>

// TODO: implement function that automatically scales up the reservedStack adn heap based on the usage


/*
 ________________________________________
/ You have Egyptian flu: you're going to \
\ be a mummy.                            /
 ----------------------------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\               
                ||----w |
                ||     ||


    ( ͡°( ͡° ͜ʖ( ͡° ͜ʖ ͡°)ʖ ͡°) ͡°)
*/


typedef unsigned int size;

namespace Runtime {

    namespace Util {
        
        // Header class for different allocations and for dealing with memory
        struct Header {
            // Size of the allocated block
            uint32_t size;
            // Position in RAM
            bool flagDeletion;
            // IF this header refrences the begining blokc which dictates he start of the heap
            // This is mainly used in the defragmentation of teh heap
            bool isStart = false;
        };



        // This function can be public coz tbh it is very basic
        // Function that calculates the allignment of a certain data block
        unsigned long calcAllignment(uintptr_t size);

    };

    class Memory {
        public:
            Memory(size stackSize, size heapSize);
            ~Memory();
            void* alloc(size size);
            void  free(void* memoryLoc);
            void* realloc(void* memoryLoc, size size);
            // TODO: implement stack functions for allocation of memory on the stack
            // TODO: implement defragmentation functions
            void  defragment();


    private:
        // Reserved stack memory only for usage with stack frames
        char* _stack;
        // Only for the heap vars
        char* _heap;

        // Utility vars
        // Size of the heap
        size _heapSize;
        // Offset variable for new allocations
        unsigned int _offset = 0;

        // Pointer to the fist header so that we can easilly traverse the heap
        Runtime::Util::Header* _header;


        // Function that extends the didcated memory to the heap
        void extendHeap(size size);

    };
}

#endif // !MEMORY_H
