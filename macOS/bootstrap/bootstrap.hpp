#ifndef bootstrap_hpp
#define bootstrap_hpp

#include <stdio.h>
#define DLLEXPORT __attribute__((visibility("default")))
extern "C" void bootstrap(ptrdiff_t offset, void *param, size_t psize, void *dummy) DLLEXPORT;

#define BYTE unsigned char

#define FunctionNameMax 256
struct BinaryLoaderArgs
{
    bool Verbose;
    bool WaitForDebugger;
    bool StartAssembly;
    char Reserved[5];
    char BinaryFilePath[PATH_MAX];
    char CoreRootPath[PATH_MAX];
    char CoreLibrariesPath[PATH_MAX];
};

struct AssemblyFunctionCall
{
    char Assembly[FunctionNameMax];
    char Class[FunctionNameMax];
    char Function[FunctionNameMax];
    BYTE Arguments[FunctionNameMax];
};

struct DotnetAssemblyFunctionCall
{
    char coreRunLib[PATH_MAX];
    
    char binaryLoaderFunctionName[FunctionNameMax];
    char assemblyCallFunctionName[FunctionNameMax];
    
    BinaryLoaderArgs binaryLoaderArgs;
    AssemblyFunctionCall assemblyFunctionCall;
};

#endif /* bootstrap_hpp */
