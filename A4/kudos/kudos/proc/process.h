/// Kernel support for userland processes.

#ifndef KUDOS_PROC_PROCESS_H
#define KUDOS_PROC_PROCESS_H

#include "lib/types.h"
#include "vm/memory.h"
#include "kernel/klock.h"

#define PROCESS_PTABLE_FULL  (-1)
#define PROCESS_ILLEGAL_JOIN (-2)
#define PROCESS_SLEEPING (-3)
#define PROCESS_RUNNING (-4)
#define PROCESS_DEAD (-5)


#define PROCESS_MAX_FILELENGTH (256)
#define PROCESS_MAX_PROCESSES  (128)
#define PROCESS_MAX_FILES      (10)

typedef int pid_t;

typedef struct {
  pid_t pid;
  int *sleep_resource;
  int retval;
  char path[256];
  int status;
  klock_t klock;
} pcb_t;

/// Initialize process table.
/// Should be called during boot.
void process_init();

int process_read(int filehandle, void *buffer, int length);

int process_write(int filehandle, const void *buffer, int length);

/// Load and run the executable as a new process in a new thread.
/// Arguments: Path to the executable and arguments.
/// Flags are documented below.
/// Returns the process ID of the new process.
pid_t process_spawn(char const* executable, int flags);

#endif // KUDOS_PROC_PROCESS_H
