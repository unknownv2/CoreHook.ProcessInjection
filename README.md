# CoreHook.ProcessInjection


Helper libraries for process injection used by [CoreHook](https://github.com/unknownv2/CoreHook) on Linux and macOS.

## Building

First, clone the repository with:
```
git clone https://github.com/unknownv2/CoreHook.ProcessInjection.git
```
## Linux

Make sure you have `clang` installed, then build with:
```
cd Linux
make
```

**Note:** The `Linux` injection method uses `ptrace` to attach and inject the library into the target process, which is prevented by the kernel if the target process was not created by the process attempting injection.

To disable this security feature until the next reboot, use the command:

```
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
``` 

## macOS

You need `Xcode` installed, then build with:

```
cd macOS
xcodebuild -workspace CoreHook.ProcessInjection.xcworkspace -scheme inject
xcodebuild -workspace CoreHook.ProcessInjection.xcworkspace -scheme bootstrap
```
## References

* [osxinj](https://github.com/scen/osxinj)
* [mach_inject](https://github.com/rentzsch/mach_inject)
* [linux-inject](https://github.com/gaffe23/linux-inject)
* [evilELF](https://github.com/jmpews/evilELF)