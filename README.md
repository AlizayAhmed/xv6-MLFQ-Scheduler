
### XV6 MLFQ SCHEDULER IMPLEMENTATION


PROJECT OVERVIEW

This project implements a Multi-Level Feedback Queue (MLFQ) scheduler in the
xv6-riscv operating system, replacing the default round-robin scheduler.

Key Features:
- 4-level priority queue system (Q0, Q1, Q2, Q3)
- Time quantum-based scheduling (1, 2, 4, 8 ticks)
- Aging mechanism to prevent starvation
- New system call: getprocinfo() for performance analysis
- CPU-bound and I/O-bound benchmark applications


FILES MODIFIED

Kernel Files:
1. kernel/proc.h       - Added MLFQ fields to process structure
2. kernel/proc.c       - Implemented MLFQ scheduler logic
3. kernel/trap.c       - Added time quantum enforcement
4. kernel/syscall.h    - Added getprocinfo system call number
5. kernel/syscall.c    - Registered getprocinfo system call
6. kernel/sysproc.c    - Implemented getprocinfo system call

User Files:
7. user/user.h         - Added getprocinfo prototype
8. user/usys.pl        - Added getprocinfo assembly stub
9. user/cpubound.c     - CPU-intensive benchmark (NEW FILE)
10. user/iobound.c     - I/O-intensive benchmark (NEW FILE)
11. user/testboth.c    - Concurrent test program (NEW FILE)

Build System:
12. Makefile           - Added new user programs


BUILD INSTRUCTIONS

Prerequisites:
- Ubuntu 20.04 or later
- RISC-V toolchain (gcc-riscv64-linux-gnu)
- QEMU for RISC-V (qemu-system-misc)

Steps:
1. Clone the original xv6-riscv repository:
   git clone https://github.com/mit-pdos/xv6-riscv.git

2. Apply the patch:
   cd xv6-riscv
   git apply cep_solution.patch

3. Build xv6:
   make clean
   make

4. Run xv6:
   make qemu

TESTING INSTRUCTIONS

Inside xv6:

1. Test CPU-bound application:
   $ cpubound

2. Test I/O-bound application:
   $ iobound

3. Test concurrent execution (most important):
   $ testboth

4. Exit QEMU:
   Press Ctrl+A, then X


PERFORMANCE RESULTS

Individual Execution:
- CPU-bound: 3 ticks, 4 CPU ticks, 36 schedules, Priority Q2
- I/O-bound: 916 ticks, 508 CPU ticks, 24,119 schedules, Priority Q3

Concurrent Execution:
- CPU-bound: 5 ticks, 24 CPU ticks, 70 schedules, Priority Q3
- I/O-bound: 1,872 ticks, 1,011 CPU ticks, 24,240 schedules, Priority Q3

Key Finding: I/O-bound scheduled 346x more frequently than CPU-bound during
concurrent execution, demonstrating MLFQ's effectiveness.


MLFQ DESIGN PARAMETERS

Queue Levels: 4 (Q0 = highest priority, Q3 = lowest priority)
Time Quanta: Q0=1 tick, Q1=2 ticks, Q2=4 ticks, Q3=8 ticks
Aging Threshold: 30 ticks
Initial Queue: All new processes start at Q0

Rules:
1. Always run process from highest non-empty queue
2. Demote process if it uses full time quantum
3. Maintain priority if process yields voluntarily
4. Promote process if waiting > 30 ticks (aging)


REPOSITORY STRUCTURE

xv6-riscv-mlfq-submission/
├── README.md               (this file)
├── benchmark_apps/
│   ├── cpubound.c
│   ├── iobound.c
│   └── testboth.c
├── modified_files/
│   ├── kernel/
│   ├── user/
│   └── Makefile
└── cep_solution.patch
