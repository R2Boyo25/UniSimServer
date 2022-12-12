#include <iostream>
#include "../globals.hpp"

extern "C" void rs_network(const char* bind);

void* networking_thread(void* DATA) {
  const char* bind = "0.0.0.0:6028";
  rs_network(bind);

  return NULL;
}
