
export CC = gcc 
export CFLAGS = -Wall -Wextra -Werror -fPIC -I$(CURDIR)/dist -L$(CURDIR)/dist
export DEBUG_CFLAGS = -g3
export RELEASE_CFLAGS = -O2 -march=native

export ROOTDIR = $(CURDIR)
export DISTDIR = $(CURDIR)/dist
export SHAREDDIR = $(CURDIR)/shared

target = windows 

ifeq ($(target), windows)
export makefile = makefile-windows
else 
ifeq ($(target), linux)
export makefile = makefile-linux
else 
export makefile = makefile-windows
endif
endif

.PHONY: default
default:
	make debug 

.PHONY: clean
clean:
	make clean -f $(makefile) target=$(target)
	make clean -C test

.PHONY: debug
debug: export CFLAGS += $(DEBUG_CFLAGS)
debug: h lib dll test

.PHONY: release
release: export CFLAGS += $(RELEASE_CFLAGS)
release: h lib dll test

.PHONY: h
h: 
	make h -f $(makefile) target=$(target)

.PHONY: lib
lib: 
	make lib -f $(makefile) target=$(target)

.PHONY: dll
dll:
	make dll -f $(makefile) target=$(target)

.PHONY: test
test:
	make test -C test target=$(target)
