# CoreHook.ProcessInjection


Helper libraries for process injection used by CoreHook on Linux and macOS.

## Building

First, clone the repository with:
```
git clone https://github.com/unknownv2/CoreHook.ProcessInjection
```
## Linux

Make sure you have `clang` installed, then build with:
```
cd Linux
make
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