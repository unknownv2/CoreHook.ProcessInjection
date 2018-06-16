#ifdef ARM
	#define REG_TYPE user_regs
#else
	#define REG_TYPE user_regs_struct
#endif
#include "inject.h"
#include <stdbool.h> // bool type
#include <signal.h>

INJECT_EXPORT void ptrace_attach(pid_t target);
INJECT_EXPORT void ptrace_detach(pid_t target);
void ptrace_getregs(pid_t target, struct REG_TYPE* regs);
INJECT_EXPORT void ptrace_cont(pid_t target);
void ptrace_setregs(pid_t target, struct REG_TYPE* regs);
siginfo_t ptrace_getsiginfo(pid_t target);
INJECT_EXPORT void ptrace_read(int pid, unsigned long addr, void *vptr, int len);
INJECT_EXPORT void ptrace_write(int pid, unsigned long addr, void *vptr, int len);
void checktargetsig(int pid);
char * ptrace_read_string(int pid, unsigned long start);
INJECT_EXPORT long ptrace_memory_search(int pid, long start, long end, void *data, long len);

INJECT_EXPORT bool ptrace_read2(int pid, unsigned long addr, void *data, unsigned int len);
void restoreStateAndDetach(pid_t target, unsigned long addr, void* backup, int datasize, struct REG_TYPE oldregs);
