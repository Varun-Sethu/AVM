#include "../Memory.h"
#include <iostream>

using namespace Runtime;


int main() {
    Memory instance = Memory(1024, 100000);
    int* data  = (int*) instance.alloc(32);
    instance.alloc(20);

    *data = 7;

    //instance.free(data);
    instance.free(data);
    instance.defragment();

    return 0;
}