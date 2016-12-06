#include "kernel/interrupt.h"
#include "kernel/semaphore.h"
#include "kernel/sleepq.h"
#include "kernel/config.h"
#include "kernel/assert.h"
#include "lib/libc.h"
#include "proc/usr_sem.h"

static user_sem_t user_semaphore_table[CONFIG_MAX_SEMAPHORES];
static klock_t usr_sem_table_klock;

/// defining an array of entries and initialize them
void sem_init() {
  int i;
  for (i = 0; i < CONFIG_MAX_SEMAPHORES; ++i) {
    user_semaphore_table[i].status = -1;
    klock_init(user_semaphore_table[i].klock);
    stringcopy(user_semaphore_table[i].name,"\0",100);
    user_semaphore_table[i].max_ressources = -1;
  }
}


usr_sem_t* usr_sem_open(const char* name, int value) {
  int i;
  int sem_exists = 0;
  int position = -1;
  int free_position = -1;

  klock_status klock_status;
  klock_status klock_tbl_status;

  klock_tbl_status = klock_lock(&usr_sem_table_klock); //check if locked?
  for (i = 0; i < CONFIG_MAX_SEMAPHORES; ++i) {
    if (stringcmp(name,*user_semaphore_table[i].name) == 0){
      sem_exists = 1;
      position = i;
      break;
      }
  }
  if (value < 0) {
    if (sem_exists) {
      klock_open(klock_tbl_status,&usr_sem_table_klock);
      return (&user_semaphore_table[position]);
    }
    else {
      klock_open(klock_tbl_status,&usr_sem_table_klock);
      return NULL;
    }
  }
  else { //handle positive value
    if (sem_exists) {
      klock_open(klock_tbl_status,&usr_sem_table_klock);
      return NULL;
    }
    else {
      for (i = 0; i < CONFIG_MAX_SEMAPHORES ; i++) {
	if (user_semaphore_table[position].status < 0) {
	  free_position = i;
	}
      }
      if (free_position < 0) { //free_position initialized ith -1
	klock_open(klock_tbl_status,&usr_sem_table_klock);
	return(NULL); //handle not having room in the semaphore table
      }

      else {
	klock_status = klock_lock(&user_semaphore_table[free_position].klock);
	user_semaphore_table[free_position].status = value;
	stringcopy(&user_semaphore_table[free_position].name, name, 100);
	klock_open(klock_status,&user_semaphore_table[free_position].klock);
	klock_open(klock_tbl_status,&usr_sem_table_klock);
	return(&user_semaphore_table[free_position]);
      }
    }
  }
}


int usr_sem_close(usr_sem_t* sem) {
  klock_status klock_status_t;
  int i;  
  if (sem->value < sem->max_ressources){
    return(-8008135) //fix this
  }
  klock_status = klock_lock(&sem->klock);
  sem->status = -1;
  sem->max_ressources = -1;
  stringcopy(*sem->name,"\0",100);
  klock_open(klock_status,&sem->klock)
  return(0);
}


int usr_sem_p(usr_sem_t* sem) {
  klock_status klock_status;
  klock_status = klock_lock(&sem->klock);
  if (sem->status = 0) { //if no ressource is avaiable
    klock_open(klock_status,&sem->klock);
    return(-80085);
  }
  sem->status--;
  klock_open(klock_status,&sem->klock);
  return(0);
}

int usr_sem_v(usr_sem_t* sem) {
  klock_status klock_status;
  klock_status = klock_lock(&sem_klock);
  if (sem->status = sem->max_ressources) {
    klock_open(klock_status,&sem->klock);
    return(-8000085);
  }
  sem->status++
  klock_open(klock_status,&sem->klock);
  return(0);
}
