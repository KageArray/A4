#include "lib.h"
#define SEM1 "semafor1"

int main() {
  sem_t* sema1 = syscall_sem_open(SEM1, 2);
  printf("Starting tests\n");
  if (sema1 == NULL) {
    printf("failed test 1, couldn't initialize semaphore\n");
  }
  if (syscall_sem_open(SEM1, 3) != NULL) {
    printf("failed test 2, made two copies with same name\n");
  }  
  if (syscall_sem_open(SEM1, -1) == NULL) {
    printf("failed test 3, couldn't open\n");
  }
  if (syscall_sem_open(SEM1, -1) != sema1) {
    printf("failed test 4, recieved incorrect semaphore location\n");
  }
  if (syscall_sem_p(sema1) < 0){
    printf("failed test 5, syscall_sem_p exited with error code\n");
  }
  if (syscall_sem_p(sema1) < 0){
    printf("failed test 6, syscall_sem_p exited with error code\n");
  }
  if (syscall_sem_p(sema1) > -1){
    printf("failed test 7, syscall_sem_p didn't exit with error code\n");
  }
  if (syscall_sem_v(sema1) <0){
    printf("failed test 8, syscall_sem_v returned error code\n");
  }
  if (syscall_sem_p(sema1) != 0){
    printf("failed test 9, syscall_sem_p returned error code\n");
  }
  if (syscall_sem_p(sema1) > -1){
    printf("failed test 10, syscall_sem_p didn't exit with error code\n");
  }
  if (syscall_sem_close(sema1) > -1){
    printf("failed test 11, syscall_sem_close didn't exit with error code. Warning the rest of semaphoere tests might fail\n");
  }
  if (syscall_sem_v(sema1) <0){
    printf("failed test 12, syscall_sem_v returned error code\n");
  }
  if (syscall_sem_v(sema1) <0){
    printf("failed test 13, syscall_sem_v returned error code\n");
  }
  if (syscall_sem_close(sema1) < 0){
    printf("failed test 11, syscall_sem_close exited with error code\n");
  }
  printf("tests finished\n");
  syscall_halt();
  return(0);
}
