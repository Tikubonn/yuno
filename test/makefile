

all: .always
	make test.exe 
	gdb test.exe 
	
clean: .always
	rm -f yuno.dll
	make clean -C yunoprocess
	make clean -C yunothread
	make clean -C yunofile
	make clean -C yunomutex
	make clean -C yunopipe
	make clean -C yunosemaphore

yunoprocess/yunoprocess.lib: .always
	make yunoprocess.lib -C yunoprocess

yunothread/yunothread.lib: .always
	make yunothread.lib -C yunothread

yunofile/yunofile.lib: .always
	make yunofile.lib -C yunofile

yunomutex/yunomutex.lib: .always
	make yunomutex.lib -C yunomutex

yunopipe/yunopipe.lib: .always
	make yunopipe.lib -C yunopipe

yunosemaphore/yunosemaphore.lib: .always
	make yunosemaphore.lib -C yunosemaphore

ifeq ($(target), windows)
dynamiclib=yuno.dll
else
ifeq ($(target), linux)
dynamiclib=yuno.so
else
# unknown target!
endif
endif

$(dynamiclib): $(rootdir)/dist/$(dynamiclib)
	cp $(rootdir)/dist/$(dynamiclib) $(dynamiclib)

test.exe: test.c yunoprocess/yunoprocess.lib yunothread/yunothread.lib yunofile/yunofile.lib yunomutex/yunomutex.lib yunopipe/yunopipe.lib yunosemaphore/yunosemaphore.lib $(dynamiclib)
	gcc $(CFLAGS) test.c yunoprocess/yunoprocess.lib yunothread/yunothread.lib yunofile/yunofile.lib yunomutex/yunomutex.lib yunopipe/yunopipe.lib yunosemaphore/yunosemaphore.lib $(dynamiclib) -o test.exe 

.always:

