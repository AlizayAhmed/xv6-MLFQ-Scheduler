//-------------------------ADDITION(CPU-bound benchmark application)-------------------------
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int is_prime(int n) {
  if (n <= 1) return 0;
  if (n <= 3) return 1;
  if (n % 2 == 0 || n % 3 == 0) return 0;
  
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return 0;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  printf("========================================\n");
  printf("CPU-Bound Application Started\n");
  printf("PID: %d\n", getpid());
  printf("========================================\n");
  
  int count = 0;
  int limit = 5000;  // Reduced limit but MORE iterations
  
  uint start = uptime();
  
  printf("Calculating primes (heavy workload)...\n");
  
  // Do MANY passes to consume more CPU time
  for(int pass = 0; pass < 50; pass++) {  // 50 passes!
    for (int i = 2; i < limit; i++) {
      if (is_prime(i)) {
        count++;
      }
    }
    
    // Print progress every 10 passes
    if((pass + 1) % 10 == 0) {
      printf("  Pass %d/50 complete...\n", pass + 1);
    }
  }
  
  count = count / 50;  // Average count
  
  uint end = uptime();
  
  printf("\n");
  printf("========================================\n");
  printf("CPU-Bound Application Results\n");
  printf("========================================\n");
  printf("Primes found (per pass): %d\n", count);
  printf("Range: 2 to %d\n", limit);
  printf("Total passes: 50\n");
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
  } else {
    printf("Failed to get process info\n");
  }
  
  printf("========================================\n");
  
  exit(0);
}
