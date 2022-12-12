#include <iostream>
#include <omp.h>
#include <libguile.h>

#include "globals.hpp"
#include "network/network.hpp"
#include "schedule/schedule.hpp"
#include "logic/logic.hpp"

void guile_threadsafe_display(SCM args) {
  OUTPUT_MUTEX.lock();
  scm_call_2(scm_c_eval_string("apply"), scm_c_eval_string("raw-display"), args);
  OUTPUT_MUTEX.unlock();
}

void* guile_setup(void* DATA) {
  scm_c_eval_string("(define raw-display display)");
  scm_c_define_gsubr("display", 0, 0, 1, scm_t_subr(guile_threadsafe_display));
  scm_c_define_gsubr("raw-schedule-task", 2, 0, 0, scm_t_subr(guile_schedule_task));
  scm_c_eval_string("(define* (schedule-task delay func #:rest argv) (raw-schedule-task delay (lambda () (apply func argv))))");

  return NULL;
}

void* guile_main(void* DATA) {
  scm_with_guile(*guile_setup, NULL);
  
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
  guile_main(NULL);
  //scm_with_guile(*guile_main, NULL);
}
