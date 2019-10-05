
export CFLAGS := -g
export MAKEFLAGS := -r

export rootdir := $(CURDIR)
export CFLAGS += -I$(CURDIR) -I$(CURDIR)/dist

ifeq ($(target), windows)
export CFLAGS += -lpsapi
else
ifeq ($(target), linux)
export CFLAGS += -pthread -lrt
else
endif
endif

all: .always
ifeq ($(target), windows)
	make windows
else
ifeq ($(target), linux)
	make linux
else
	@echo "Usage:"
	@echo "  make target=[windows|linux]         build library for target system."
	@echo "  make clean                          cleanup the intermediate file."
	@echo "  make test target=[windows|linux]    build and run the test."
endif
endif

test: .always
ifeq ($(target), windows)
	make windows-test
else
ifeq ($(target), linux)
	make linux-test
else
	@echo "Usage:"
	@echo "  make test target=[windows|linux]    build and run the test."
endif
endif

clean: .always
	rm -f yuno.p
	rm -f yuno-function.p
	rm -f yuno.private
	rm -f yuno.public
	make clean -C windows 
	make clean -C linux
	make clean -C test

yuno.p: yunocall.p yunosize.p yunoprocess.p yunothread.p yunofile.p yunomutex.p yunosemaphore.p yunotime.p yunopipe.p yunoshared-memory.p
	cat yunocall.p yunosize.p yunoprocess.p yunothread.p yunofile.p yunomutex.p yunosemaphore.p yunotime.p yunopipe.p yunoshared-memory.p > yuno.p

yuno-function.p: yunoprocess-function.p yunothread-function.p yunofile-function.p yunomutex-function.p yunosemaphore-function.p yunotime-function.p yunopipe-function.p yunoshared-memory-function.p
	cat yunoprocess-function.p yunothread-function.p yunofile-function.p yunomutex-function.p yunosemaphore-function.p yunotime-function.p yunopipe-function.p yunoshared-memory-function.p > yuno-function.p

linux-test: .always
	make yunobitarray yunofile yunomutex yunopipe yunoprocess yunosemaphore yunoshared-memory yunothread -C test

linux: .always
	make yuno.p
	make yuno-function.p
	make yuno.private -C linux
	make yuno.public -C linux
	cat yuno.p linux/yuno.private yuno-function.p > yuno.private
	cat yuno.p linux/yuno.public yuno-function.p > yuno.public
	cp yuno.public dist/yuno.h
	make yuno.a -C linux
	make yuno.so -C linux
	cp linux/yuno.a dist/yuno.a
	cp linux/yuno.so dist/yuno.so

windows-test: .always
	make yunofile yunoprocess yunothread yunomutex yunosemaphore yunopipe yunobitarray yunoallocator yunoshared-memory -C test

windows: .always 
	make yuno.p
	make yuno-function.p
	make yuno.private -C windows
	make yuno.public -C windows
	cat yuno.p windows/yuno.private yuno-function.p > yuno.private
	cat yuno.p windows/yuno.public yuno-function.p > yuno.public
	cp yuno.public dist/yuno.h
	make yuno.lib -C windows
	make yuno.dll -C windows
	cp windows/yuno.lib dist/yuno.lib
	cp windows/yuno.dll dist/yuno.dll

.always:
