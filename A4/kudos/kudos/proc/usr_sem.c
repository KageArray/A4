#include "kernel/interrupt.h"
#include "kernel/semaphore.h"
#include "kernel/sleepq.h"
#include "kernel/config.h"
#include "kernel/assert.h"
#include "lib/libc.h"
#include "proc/usr_sem.h"

/// defining an array of entries and initialize them
void sem_init() {
  int i;
  for (i = 0; i < CONFIG_MAX_SEMAPHORES; ++i) {
    semaphore_table[i].status = -1;
  }
}
