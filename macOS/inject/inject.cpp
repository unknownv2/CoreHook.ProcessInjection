#include <cstdio>
#include <cstring>
#include "mach_inject.h"
#include <dlfcn.h>
#include <libproc.h>

const char * bootstrapLib = "libbootstrap.dylib";

extern "C" pid_t findProcessByName(const char *name)
{
    int procCnt = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    pid_t pids[1024];
    memset(pids, 0, sizeof pids);
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    
    for (int i = 0; i < procCnt; i++)
    {
        if (!pids[i]) continue;
        char curPath[PROC_PIDPATHINFO_MAXSIZE];
        char curName[PROC_PIDPATHINFO_MAXSIZE];
        memset(curPath, 0, sizeof curPath);
        proc_pidpath(pids[i], curPath, sizeof curPath);
        int len = strlen(curPath);
        if (len)
        {
            int pos = len;
            while (pos && curPath[pos] != '/') --pos;
            strcpy(curName, curPath + pos + 1);
            if (!strcmp(curName, name))
            {
                return pids[i];
            }
        }
    }
    return 0;
}
void *module;
void *bootstrapfn;
extern "C" uintptr_t copyMemToProcess(char * processName, const void * input, size_t inputSize)
{
    uintptr_t remoteAddress = 0;
    pid_t pid = findProcessByName(processName);
    mach_copy_mem(pid, input, inputSize, &remoteAddress);
    return remoteAddress;
}
extern "C" uintptr_t copyMemToProcessByPid(pid_t pid, const void * input, size_t inputSize)
{
    uintptr_t remoteAddress = 0;
    mach_copy_mem(pid, input, inputSize, &remoteAddress);
    return remoteAddress;
}
extern "C" mach_error_t injectByName(char * processName, const char* lib, pid_t * outPid)
{
    module = dlopen(bootstrapLib,
                    RTLD_NOW | RTLD_LOCAL);
    
    printf("module: %p\n", module);
    if (!module)
    {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return -1;
    }
    
    bootstrapfn = dlsym(module, "bootstrap");
    printf("bootstrapfn: %p\n", bootstrapfn);
    
    if (!bootstrapfn)
    {
        fprintf(stderr, "could not locate bootstrap fn\n");
        return -2;
    }
    if (!module || !bootstrapfn)
    {
        fprintf(stderr, "failed to inject: module:0x%X bootstrapfn:0x%X\n", module, bootstrapfn);
        return -3;
    }
    pid_t pid = findProcessByName(processName);
    mach_error_t err = mach_inject((mach_inject_entry)bootstrapfn, lib, strlen(lib) + 1, pid, 0);
    if(outPid != nullptr)
    {
        *outPid = pid;
    }
    return err;
}
extern "C" mach_error_t injectByPid( pid_t pid, const char* lib)
{
    module = dlopen(bootstrapLib,
                    RTLD_NOW | RTLD_LOCAL);
    printf("module: %p\n", module);
    if (!module)
    {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return -1;
    }
    
    bootstrapfn = dlsym(module, "bootstrap");
    printf("bootstrapfn: %p\n", bootstrapfn);
    
    if (!bootstrapfn)
    {
        fprintf(stderr, "could not locate bootstrap fn\n");
        return -2;
    }
    if (!module || !bootstrapfn)
    {
        fprintf(stderr, "failed to inject: module:0x%X bootstrapfn:0x%X\n", module, bootstrapfn);
        return -3;
    }
    mach_error_t err = mach_inject((mach_inject_entry)bootstrapfn, lib, strlen(lib) + 1, pid, 0);
    return err;
}
extern "C" mach_error_t injectByPidWithArgs( pid_t pid, const void* params, size_t paramsSize)
{
    printf("lib name: %s\n", bootstrapLib);
    
    module = dlopen(bootstrapLib,
                    RTLD_NOW | RTLD_LOCAL);
    
    printf("module: %p\n", module);
    if (!module)
    {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return -1;
    }
    
    bootstrapfn = dlsym(module, "bootstrap");
    printf("bootstrapfn: %p\n", bootstrapfn);
    
    if (!bootstrapfn)
    {
        fprintf(stderr, "could not locate bootstrap fn\n");
        return -2;
    }
    if (!module || !bootstrapfn)
    {
        fprintf(stderr, "failed to inject: module:0x%X bootstrapfn:0x%X\n", module, bootstrapfn);
        return -3;
    }
    mach_error_t err = mach_inject((mach_inject_entry)bootstrapfn, params, paramsSize, pid, 0);
    return err;
}
