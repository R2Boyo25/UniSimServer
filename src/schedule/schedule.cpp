#include "../globals.hpp"
#include <iostream>

void* scheduling_thread(void* DATA) {
  OUTPUT_MUTEX.lock();
  std::cout << "I'm the task scheduler thread!" << std::endl;
  OUTPUT_MUTEX.unlock();
  return NULL;
}
