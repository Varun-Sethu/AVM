#include "../env.h"

Environment::Environment(std::size_t sharedSize) {      
  _sharedStorage = new unsigned char[sharedSize];
}

// TODO: Determine what to add to this later
bool Environment::createThread(Thread thread) {
  // Push the thread into our list
  try {
    _thread.push_back(thread)
  } catch(...) {
    // Oopsie Dasie
    return false;
  }

  return true;
}