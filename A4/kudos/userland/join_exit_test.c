#include "lib.h"


int main(){
  int tid;
  int retval;
  tid = syscall_spawn("[disk]proc", 0);
  retval = (syscall_join(tid));
  if (retval == 80085){
    printf("Test of syscall_join and syscall_exit succeeded\n");
  }
  else{
    printf("Test of syscall_join and syscall_exit failed\n");
  }
  syscall_halt();
  return (0);
}
