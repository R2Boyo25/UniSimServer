#include "globals.hpp"

std::map<std::string, std::any> globaldata = {};
bool GAME_RUN = true;
std::mutex OUTPUT_MUTEX;
