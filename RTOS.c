#include "RTOS.h"

int32_t getEmptyTask(void) {
  for (size_t index = 0; index < TASK_LIMIT; index++) {
    if (Tasks[index].cbFunc == NULL) return index;
  }

  return -1;
}

osStatus removeTask(callbackFunc cb) {
  for (size_t index = 0; index < TASK_LIMIT; index++) {
    if (Tasks[index].cbFunc == cb) {
      Tasks[index].cbFunc = NULL;
      Tasks[index].interval = 0;
      Tasks[index].priority = 0;
      Tasks[index].recurring = 0;
      Tasks[index].ticks = 0;
      return osOK;
    }
  }

  return osNonExistentTask;
}

osStatus tickRTOS(uint32_t ticks) {
  for (size_t index = 0; index < TASK_LIMIT; index++) {
    if (Tasks[index].ticks < Tasks[index].interval) Tasks[index].ticks += ticks;
    else {
      if (!Tasks[index].recurring) removeTask(Tasks[index].cbFunc);
      Tasks[index].cbFunc();
    }
  }

  return osOK;
}

osStatus creatTask(callbackFunc cbFunc, uint32_t interval, uint8_t priority, bool recurring) {
  size_t index = getEmptyTask();
  if (!index) return osNotEnoughPlace;
  Tasks[index].cbFunc = cbFunc;
  Tasks[index].interval = interval;
  Tasks[index].priority = priority;
  Tasks[index].recurring = recurring;

  return osOK;
}
