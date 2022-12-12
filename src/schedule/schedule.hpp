#include <vector>
#include <libguile.h>

class ScheduledTask {
public:
  unsigned long long time;
  SCM exec;

  ScheduledTask();
  ScheduledTask(unsigned long long time, SCM exec);
};

extern std::vector<ScheduledTask> SCHEDULED_TASKS;

void* scheduling_thread(void* DATA);
void schedule_task(unsigned long long time, SCM func);
void guile_schedule_task(SCM delay, SCM func);
