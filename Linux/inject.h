#ifndef INJECT_H
#define INJECT_H 1

#ifdef WIN32
#ifdef INJECT_EXPORTS
#define INJECT_EXPORT __declspec(dllexport)
#else /* INJECT_EXPORTS */
#define INJECT_EXPORT __declspec(dllimport)
#endif /* INJECT_EXPORTS */
#elif defined(__GNUC__)
#define INJECT_EXPORT __attribute__((visibility("default")))
#else
#define INJECT_EXPORT
#endif /* WIN32 */


INJECT_EXPORT int injectByPid(pid_t targetPid, char* libName);
INJECT_EXPORT int injectByName(char * processName, char* libName, pid_t* pid);

#endif
