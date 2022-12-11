#include <iostream>
#include "../globals.hpp"

void* networking_thread(void* DATA) {
  OUTPUT_MUTEX.lock();
  std::cout << "I'm the network thread!" << std::endl;
  OUTPUT_MUTEX.unlock();

  return NULL;
}
