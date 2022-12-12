#include <map>
#include <string>
#include <any>
#include <mutex>
#include <vector>

extern std::map<std::string, std::any> GLOBAL_DATA;
extern bool GAME_RUN;
extern std::mutex OUTPUT_MUTEX;
unsigned long long get_time();
