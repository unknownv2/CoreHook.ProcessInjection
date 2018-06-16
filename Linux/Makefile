CC	= clang
CFLAGS	= -std=gnu99 -ggdb
UNAME_M := $(shell uname -m)

.PHONY: x86_64 arm

all:
ifeq ($(UNAME_M),x86_64)
	$(MAKE) x86_64
endif
ifneq (,$(findstring arm,$(UNAME_M)))
	$(MAKE) arm
endif

arm: sample-library.so
	$(CC) -marm $(CFLAGS) -DARM -shared -o inject.so utils.c ptrace.c inject-arm.c -ldl

x86_64: inject.so
	$(CC) $(CFLAGS) -shared -o inject.so utils.c ptrace.c inject-x86_64.c elf-parse.c -fPIC
	
clean:
	rm -f inject.so