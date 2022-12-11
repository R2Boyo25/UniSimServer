#include <map>
#include <string>
#include <any>
#include <mutex>

extern std::map<std::string, std::any> globaldata;
extern bool GAME_RUN;
extern std::mutex OUTPUT_MUTEX;
