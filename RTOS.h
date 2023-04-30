#ifndef RTOS_H__
#define RTOS_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TASK_LIMIT
#define TASK_LIMIT 16
#endif

#ifndef MIN_PRIORITY
#define MIN_PRIORITY 0
#endif

#ifndef MAX_PRIORITY
#define MAX_PRIORITY 10
#endif

enum status {
  osOK = 0,
  osNotEnoughPlace,
  osNonExistentTask,
};

typedef uint8_t osStatus;
typedef void (*callbackFunc)();

typedef struct Task {
  bool recurring;
  uint32_t interval;
  uint32_t ticks;
  uint8_t priority;
  callbackFunc cbFunc;
} Task;

Task Tasks[TASK_LIMIT];


#ifdef __cplusplus
}
#endif

#endif // RTOS_H__
