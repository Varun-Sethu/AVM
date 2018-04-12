#ifndef _ENV_H_
#define _ENV_H_

#include <cstdint>
#include <cstddef>
#include <vector>

// Environment class is the runtime class of the virtual machine, 
// it holds all our threads and the shared memory location
class Environment {
  public:
    // Construct
    Environment(std::size_t sharedSize);
    // Crerate thread function
    bool createThread(Thread tread);



  private:
    // Shared storage to be used among threads
    unsigned char* _sharedStorage;
    // List of threads currently provided to the VM
    std::vector<Thread> _threads;
}



#endif 