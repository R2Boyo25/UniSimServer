#include "../globals.hpp"
#include <iostream>
#include <libguile.h>

void* gamelogic_thread(void* DATA) {
  OUTPUT_MUTEX.lock();
  std::cout << "I'm the game logic thread!" << std::endl;
  OUTPUT_MUTEX.unlock();

  scm_c_eval_string("(display \"no\n\")");
  
  //scm_c_eval_string("(schedule-task 0 (lambda () (display \"Hello from the task scheduler\n\")))");
  //scm_c_eval_string("(schedule-task 2000 (lambda () (display \"Hello from 2 seconds later\n\")))");
  
  int i = 0;
  while (GAME_RUN) {
    i += 1;
    GAME_RUN = i < 1001;
  }

  return 0;
}
