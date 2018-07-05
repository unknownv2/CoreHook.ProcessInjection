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

arm:
	$(CC) -marm $(CFLAGS) -DARM -shared -o inject.so utils.c ptrace.c elf-parse.c -ldl

x86_64:
	$(CC) $(CFLAGS) -shared -o inject.so utils.c ptrace.c elf-parse.c -fPIC
	
clean:
	rm -f inject.so
