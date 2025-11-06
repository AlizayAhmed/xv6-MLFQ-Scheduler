//-------------------------ADDITION(I/O-bound benchmark application)-------------------------
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  printf("========================================\n");
  printf("I/O-Bound Application Started\n");
  printf("PID: %d\n", getpid());
  printf("========================================\n");
  
  int fd;
  int iterations = 200;
  int writes_per_iteration = 20;
  
  uint start = uptime();
  
  printf("Performing %d I/O iterations...\n", iterations);
  
  for (int i = 0; i < iterations; i++) {
    fd = open("iotest.txt", O_CREATE | O_WRONLY);
    if (fd < 0) {
      printf("I/O-Bound: Failed to open file\n");
      exit(1);
    }
    
    for (int j = 0; j < writes_per_iteration; j++) {
      write(fd, "IO", 2);
    }
    
    close(fd);
    // Simulate I/O wait with a small delay
    for(int k = 0; k < 1000; k++) {
      // Small busy wait
    }
    
    if ((i + 1) % 20 == 0) {
      printf("  Completed %d/%d iterations...\n", i + 1, iterations);
    }
  }
  
  uint end = uptime();
  
  printf("\n");
  printf("========================================\n");
  printf("I/O-Bound Application Results\n");
  printf("========================================\n");
  printf("Total iterations: %d\n", iterations);
  printf("Writes per iteration: %d\n", writes_per_iteration);
  printf("Total writes: %d\n", iterations * writes_per_iteration);
  printf("Execution time: %d ticks\n", end - start);
  printf("\n");
  
  int info[4];
  
  if (getprocinfo(getpid(), info) == 0) {
    printf("Process Performance Metrics:\n");
    printf("  Process ID: %d\n", info[0]);
    printf("  CPU Ticks Consumed: %d\n", info[1]);
    printf("  Times Scheduled: %d\n", info[2]);
    printf("  Final Priority Queue: %d (0=highest, 3=lowest)\n", info[3]);
    
    if (info[2] > 0) {
      printf("  Average CPU burst: %d ticks\n", info[1] / info[2]);
    }
    
    printf("  I/O operations: %d\n", iterations);
    printf("  CPU/IO ratio: 1:%d\n", iterations / (info[1] > 0 ? info[1] : 1));
  } else {
    printf("Failed to get process info\n");
  }
  
  printf("========================================\n");
  
  unlink("iotest.txt");
  
  exit(0);
}
//-------------------------END ADDITION-------------------------
