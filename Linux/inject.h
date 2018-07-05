#ifndef INJECT_H
#define INJECT_H 1
#include <stdbool.h>

#if defined(__GNUC__)
#define INJECT_EXPORT __attribute__((visibility("default")))
#else
#define INJECT_EXPORT
#endif

#endif
