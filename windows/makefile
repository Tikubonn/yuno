
.PHONY: clean
clean:
	make clean -C yunosize
	make clean -C yunofile
	make clean -C yunothread
	make clean -C yunomemory
	make clean -C yunoshared-memory
	make clean -C yunoprocess
	make clean -C yunopipe 
	make clean -C yuno
	make clean -C yunotime
	make clean -C yunomutex
	make clean -C yunosemaphore
	make clean -C yunoerror
	make clean -C utility
	rm -f yuno.h
	rm -f yuno.lib
	rm -f yuno.dll
	rm -f yuno.def
	rm -f yuno.exp
	rm -f yuno.dll.lib

.PHONY: h
h:
	make h -C yunosize
	make h -C yunofile
	make h -C yunothread
	make h -C yunomemory
	make h -C yunoshared-memory
	make h -C yunoprocess
	make h -C yunopipe
	make h -C yuno
	make h -C yunotime
	make h -C yunomutex
	make h -C yunosemaphore
	make h -C yunoerror
	make h -C utility
	make yuno.h

.PHONY: lib
lib:
	make lib -C yunofile 
	make lib -C yunothread 
	make lib -C yunomemory 
	make lib -C yunoshared-memory
	make lib -C yunoprocess
	make lib -C yunopipe 
	make lib -C yunotime 
	make lib -C yunomutex
	make lib -C yunosemaphore
	make lib -C yunoerror
	make lib -C utility
	make yuno.lib 

.PHONY: dll
dll:
	make lib -C yunofile 
	make lib -C yunothread
	make lib -C yunomemory
	make lib -C yunoshared-memory
	make lib -C yunoprocess
	make lib -C yunopipe 
	make lib -C yunotime
	make lib -C yunomutex
	make lib -C yunosemaphore
	make lib -C yunoerror
	make lib -C utility
	make yuno.dll
	make yuno.def
	make yuno.exp
	make yuno.dll.lib

yuno.h: yunosize/yunosize.h $(SHAREDDIR)/shared.h yunofile/yunofile.h yunothread/yunothread.h yunomemory/yunomemory.h yunoshared-memory/yunoshared-memory.h yunoprocess/yunoprocess.h yunopipe/yunopipe.h yuno/yuno.h yunotime/yunotime.h yunomutex/yunomutex.h yunosemaphore/yunosemaphore.h yunoerror/yunoerror.h utility/utility.h
	echo "#pragma once" > yuno.h
	cat yunosize/yunosize.h $(SHAREDDIR)/shared.h yunofile/yunofile.h yunothread/yunothread.h yunomemory/yunomemory.h yunoshared-memory/yunoshared-memory.h yunoprocess/yunoprocess.h yunopipe/yunopipe.h yuno/yuno.h yunotime/yunotime.h yunomutex/yunomutex.h yunosemaphore/yunosemaphore.h yunoerror/yunoerror.h utility/utility.h >> yuno.h

tempdir = $(shell mktemp -d)
workdir = $(CURDIR)

yuno.lib: $(SHAREDDIR)/shared.lib yunofile/yunofile.lib yunothread/yunothread.lib yunomemory/yunomemory.lib yunoshared-memory/yunoshared-memory.lib yunoprocess/yunoprocess.lib yunopipe/yunopipe.lib yunotime/yunotime.lib yunomutex/yunomutex.lib yunosemaphore/yunosemaphore.lib yunoerror/yunoerror.lib utility/utility.lib 
	cd $(tempdir) && \
	ar x $(SHAREDDIR)/shared.lib && \
	ar x $(workdir)/yunofile/yunofile.lib && \
	ar x $(workdir)/yunothread/yunothread.lib && \
	ar x $(workdir)/yunomemory/yunomemory.lib && \
	ar x $(workdir)/yunoshared-memory/yunoshared-memory.lib && \
	ar x $(workdir)/yunoprocess/yunoprocess.lib && \
	ar x $(workdir)/yunopipe/yunopipe.lib && \
	ar x $(workdir)/yunotime/yunotime.lib && \
	ar x $(workdir)/yunomutex/yunomutex.lib && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.lib && \
	ar x $(workdir)/yunoerror/yunoerror.lib && \
	ar x $(workdir)/utility/utility.lib && \
	ar r $(workdir)/yuno.lib *.o

yuno.dll: $(SHAREDDIR)/shared.lib yunofile/yunofile.lib yunothread/yunothread.lib yunomemory/yunomemory.lib yunoshared-memory/yunoshared-memory.lib yunoprocess/yunoprocess.lib yunopipe/yunopipe.lib yunotime/yunotime.lib yunomutex/yunomutex.lib yunosemaphore/yunosemaphore.lib yunoerror/yunoerror.lib utility/utility.lib 
	cd $(tempdir) && \
	ar x $(SHAREDDIR)/shared.lib && \
	ar x $(workdir)/yunofile/yunofile.lib && \
	ar x $(workdir)/yunothread/yunothread.lib && \
	ar x $(workdir)/yunomemory/yunomemory.lib && \
	ar x $(workdir)/yunoshared-memory/yunoshared-memory.lib && \
	ar x $(workdir)/yunoprocess/yunoprocess.lib && \
	ar x $(workdir)/yunopipe/yunopipe.lib && \
	ar x $(workdir)/yunotime/yunotime.lib && \
	ar x $(workdir)/yunomutex/yunomutex.lib && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.lib && \
	ar x $(workdir)/yunoerror/yunoerror.lib && \
	ar x $(workdir)/utility/utility.lib && \
	gcc $(CFLAGS) -shared -o $(workdir)/yuno.dll *.o

yuno.dll.lib yuno.def yuno.exp: yuno.dll
	gendef yuno.dll 
	lib -machine:x86 -def:yuno.def -out:yuno.dll.lib
	mv yuno.dll.exp yuno.exp
