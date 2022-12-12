#include "../globals.hpp"
#include "schedule.hpp"
#include <bits/stdc++.h>
#include <mutex>
#include <iostream>

namespace sc = std::chrono;

std::mutex TASK_MUTEX;
std::vector<ScheduledTask> SCHEDULED_TASKS = {};

unsigned long long get_time() {
  auto time = sc::system_clock::now();
  auto since_epoch = time.time_since_epoch();
  auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);

  return millis.count();
}

ScheduledTask::ScheduledTask(unsigned long long time, SCM exec) {
  this->time = time;
  this->exec = exec;
}

void schedule_task(unsigned long long time, SCM func) {
  SCHEDULED_TASKS.push_back(ScheduledTask(time, func));
}

void guile_schedule_task(SCM delay, SCM func) {
  TASK_MUTEX.lock();
  //schedule_task(get_time() + scm_to_ulong_long(delay), func);
  TASK_MUTEX.unlock();
}

void* scheduling_thread(void* DATA) {
  while (GAME_RUN | SCHEDULED_TASKS.size()) {
    unsigned long long time = get_time();
    for (long unsigned int i = 0; i < SCHEDULED_TASKS.size(); i++) {
      auto task = SCHEDULED_TASKS[i];
      if (time >= task.time) {
        TASK_MUTEX.lock();
        SCM exec = task.exec;
        std::swap(SCHEDULED_TASKS[i], SCHEDULED_TASKS[SCHEDULED_TASKS.size()-1]);
        SCHEDULED_TASKS.pop_back();
        scm_call_0(exec);
        TASK_MUTEX.unlock();
      }
    }
  }
  
  return NULL;
}
