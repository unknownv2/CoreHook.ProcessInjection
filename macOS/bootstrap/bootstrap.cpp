#include <mach/mach.h>
#include <pthread.h>
#include <dlfcn.h>
#include <stddef.h>
#include <sys/syslimits.h>
#include "bootstrap.hpp"


#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_10_12
#define PTHREAD_SET_SELF _pthread_set_self
#else
#define PTHREAD_SET_SELF __pthread_set_self
#endif

extern "C" void PTHREAD_SET_SELF(void*);

void *loaderThread(DotnetAssemblyFunctionCall *args)
{
    printf("loaderThread %s\n",(char *)args->coreRunLib);
    
    void *bundle = dlopen((char *)args->coreRunLib, RTLD_NOW);
    if (!bundle) {
        fprintf(stderr, "Could not load patch bundle: %s\n", dlerror());
        return (void*)-1;
    }
    else {
        printf("\nOpened library at %p\n", bundle);
    }
    typedef void (*RunnerMethodFp)(const void * args);

    RunnerMethodFp loadAssemblyBinaryArgs = (RunnerMethodFp)dlsym(bundle, args->binaryLoaderFunctionName);
    
    printf("LoadAssemblyBinaryArgs is at %p\n", loadAssemblyBinaryArgs);
    
    loadAssemblyBinaryArgs(&args->binaryLoaderArgs);
    
    RunnerMethodFp executeManagedAssemblyClassFunction = (RunnerMethodFp)dlsym(bundle, args->assemblyCallFunctionName);
    
    printf("ExecuteManagedAssemblyClassFunction is at %p\n", executeManagedAssemblyClassFunction);
    
    executeManagedAssemblyClassFunction(&args->assemblyFunctionCall);
    
    return NULL;
}

void bootstrap(ptrdiff_t offset, void *param, size_t psize, void *dummy)
{
    
    PTHREAD_SET_SELF(dummy);
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    int policy;
    pthread_attr_getschedpolicy(&attr, &policy);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    
    struct sched_param sched;
    sched.sched_priority = sched_get_priority_max(policy);
    pthread_attr_setschedparam(&attr, &sched);
    
    pthread_t thread;
    pthread_create(&thread, &attr,
                   (void * (*)(void *))((long)loaderThread),
                   (void *)param);
    
    pthread_attr_destroy(&attr);
    
    thread_suspend(mach_thread_self());
}
