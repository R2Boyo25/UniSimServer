#include <iostream>
#include <omp.h>
#include <libguile.h>

#include "globals.hpp"
#include "network/network.hpp"
#include "schedule/schedule.hpp"
#include "logic/logic.hpp"

void* guile_main(void* DATA) {
  omp_set_num_threads(omp_get_num_procs() + 2);
  
#pragma omp parallel sections
  {
#pragma omp section
    { // Networking
      scm_with_guile(*networking_thread, NULL);
    }
#pragma omp section
    { // Task scheduler
      scm_with_guile(*scheduling_thread, NULL);
    }
#pragma omp section
    { // Main loop
      scm_with_guile(*gamelogic_thread, NULL);
    }
  }
  
  return NULL;
}

int main(int argc, char**argv) {
  scm_with_guile(*guile_main, NULL);
}
