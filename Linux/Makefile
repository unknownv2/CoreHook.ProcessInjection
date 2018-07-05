CC	= clang
CFLAGS	= -std=gnu99 -ggdb
UNAME_M := $(shell uname -m)

.PHONY: x86_64 arm arm64

all:
ifeq ($(UNAME_M),x86_64)
	$(MAKE) x86_64
endif
ifneq (,$(findstring arm,$(UNAME_M)))
	$(MAKE) arm
endif
ifeq ($(UNAME_M),aarch64)
	$(MAKE) arm64
endif

arm:
	$(CC) -marm $(CFLAGS) -DARM -shared -o inject.so utils.c elf-parse.c -ldl
arm64:
	$(CC) $(CFLAGS) -DARM64 -shared -o inject.so utils.c elf-parse.c -ldl -fPIC
x86_64:
	$(CC) $(CFLAGS) -shared -o inject.so utils.c elf-parse.c -fPIC
	
clean:
	rm -f inject.so
