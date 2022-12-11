#include "../globals.hpp"
#include <iostream>

void* gamelogic_thread(void* DATA) {
  OUTPUT_MUTEX.lock();
  std::cout << "I'm the game logic thread!" << std::endl;
  OUTPUT_MUTEX.unlock();
  
  int i = 0;
  while (GAME_RUN) {
    i += 1;
    GAME_RUN = i < 1001;
  }

  return 0;
}
