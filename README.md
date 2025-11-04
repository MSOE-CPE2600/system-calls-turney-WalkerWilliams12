# system-calls

This repository contains four C programs that demonstrate various POSIX system calls for system information, process control, and file management.

## Programs

1. **info** - Displays system information including time, hostname, OS details, CPU count, and memory statistics
2. **pinfo** - Shows process information including priority and scheduling method for a given PID
3. **pmod** - Modifies its own priority and sleeps for a specified duration
4. **finfo** - Displays detailed file information including type, permissions, owner, size, and modification time

## Building

Use the provided Makefile or compile individually:
```bash
make

gcc -o <filename> filename.c 