#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int pid1, pid2;
  
  printf("========================================\n");
  printf("Starting Concurrent Test\n");
  printf("========================================\n");
  
  // Fork first child for cpubound
  pid1 = fork();
  if(pid1 == 0) {
    // Child 1: run cpubound
    char *args[] = {"cpubound", 0};
    exec("cpubound", args);
    printf("exec cpubound failed\n");
    exit(1);
  }
  
  // Fork second child for iobound
  pid2 = fork();
  if(pid2 == 0) {
    // Child 2: run iobound
    char *args[] = {"iobound", 0};
    exec("iobound", args);
    printf("exec iobound failed\n");
    exit(1);
  }
  
  // Parent: wait for both to complete
  printf("Both processes started...\n");
  printf("CPU-bound PID: %d\n", pid1);
  printf("I/O-bound PID: %d\n", pid2);
  printf("Waiting for completion...\n\n");
  
  wait(0);
  wait(0);
  
  printf("\n========================================\n");
  printf("Both processes completed!\n");
  printf("========================================\n");
  
  exit(0);
}
