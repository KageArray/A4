//Userland semaphores
#ifndef KUDOS_PROC_USR_SEM_H
#define KUDOS_PROC_USR_SEM_H

#include "kernel/klock.h"

typedef struct {

  int status;
  int max_ressources;
  char name[100];
  klock_t klock;

}usr_sem_t;

#endif //KUDOS_PROC_USR_SEM_H
