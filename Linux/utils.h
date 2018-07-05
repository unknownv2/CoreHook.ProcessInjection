#include "inject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

INJECT_EXPORT void ptrace_attach(int pid);
INJECT_EXPORT void ptrace_detach(int pid);
INJECT_EXPORT char * ptrace_read_string(int pid, unsigned long start);
INJECT_EXPORT long ptrace_memory_search(int pid, long start, long end, void *data, long len);
INJECT_EXPORT bool ptrace_read2(int pid, unsigned long addr, void *data, unsigned int len);
INJECT_EXPORT void ptrace_read(int pid, unsigned long addr, void *data, int len);
INJECT_EXPORT void ptrace_write(int pid, unsigned long addr, void *data, int len);
