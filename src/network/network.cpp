#include <iostream>
#include "../globals.hpp"
#include <libguile.h>

void* networking_thread(void* DATA) {
  scm_c_eval_string("(display \"yes\n\")");
  
  return NULL;
}
