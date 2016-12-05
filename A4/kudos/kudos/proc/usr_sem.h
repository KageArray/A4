//Userland semaphores

#include "kernel/semaphore.h"

typedef struct {

  int status;
  kernel_semaphore *sem;
  char name[100];

}usr_sem_t
