#include "RTOS.h"

uint32_t getEmptyTask(void) {
	for (size_t index = 0; index < TASK_LIMIT; index++) {
		if (Tasks[index].cbFunc == NULL) return index;
	}
}

void removeTask(callbackFunc cb) {
  for (size_t index = 0; index < TASK_LIMIT; index++) {
		if (Tasks[index].cbFunc == cb) {
      Tasks[index].cbFunc = NULL;
      Tasks[index].interval = 0;
      Tasks[index].priority = 0;
      Tasks[index].recurring = 0;
      Tasks[index].ticks = 0;
    }
	}
}

void tickRTOS(uint32_t ticks) {
  for (size_t index = 0; index < TASK_LIMIT; index++) {
    if (Tasks[index].ticks < Tasks[index].interval) Tasks[index].ticks += ticks;
    else {
      if (!Tasks[index].recurring) removeTask(Tasks[index].cbFunc);
      Tasks[index].cbFunc();
    }
  }
}

void creatTask(callbackFunc cbFunc, uint32_t interval, uint8_t priority, bool recurring) {
	size_t index = getEmptyTask();
  Tasks[index].cbFunc = cbFunc;
  Tasks[index].interval = interval;
  Tasks[index].priority = priority;
  Tasks[index].recurring = recurring;
}