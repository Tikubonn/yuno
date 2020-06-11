
.PHONY: clean
clean:
	make clean -C utility
	make clean -C yuno
	make clean -C yunoerror
	make clean -C yunofile
	make clean -C yunomemory
	make clean -C yunomutex
	make clean -C yunopipe
	make clean -C yunoprocess
	make clean -C yunosemaphore
	make clean -C yunoshared-memory
	make clean -C yunosize
	make clean -C yunothread
	make clean -C yunotime
	rm -f yuno.h
	rm -f yuno.lib
	rm -f yuno.dll

.PHONY: h
h:
	make h -C utility
	make h -C yuno
	make h -C yunoerror
	make h -C yunofile
	make h -C yunomemory
	make h -C yunomutex
	make h -C yunopipe
	make h -C yunoprocess
	make h -C yunosemaphore
	make h -C yunoshared-memory
	make h -C yunosize
	make h -C yunothread
	make h -C yunotime
	make yuno.h

.PHONY: lib
lib: 
	make lib -C utility
	make lib -C yunoerror
	make lib -C yunofile
	make lib -C yunomemory
	make lib -C yunomutex
	make lib -C yunopipe
	make lib -C yunoprocess
	make lib -C yunosemaphore
	make lib -C yunoshared-memory
	make lib -C yunothread
	make lib -C yunotime
	make yuno.lib 

.PHONY: dll
dll: 
	make lib -C utility
	make lib -C yunoerror
	make lib -C yunofile
	make lib -C yunomemory
	make lib -C yunomutex
	make lib -C yunopipe
	make lib -C yunoprocess
	make lib -C yunosemaphore
	make lib -C yunoshared-memory
	make lib -C yunothread
	make lib -C yunotime
	make yuno.dll 

tempdir = $(shell mktemp -d)
workdir = $(CURDIR)

yuno.h: yunosize/yunosize.h $(SHAREDDIR)/shared.h yuno/yuno.h yunoerror/yunoerror.h yunofile/yunofile.h yunomemory/yunomemory.h yunomutex/yunomutex.h yunopipe/yunopipe.h yunoprocess/yunoprocess.h yunosemaphore/yunosemaphore.h yunoshared-memory/yunoshared-memory.h yunothread/yunothread.h yunotime/yunotime.h utility/utility.h
	echo "#pragma once" > yuno.h
	cat yunosize/yunosize.h $(SHAREDDIR)/shared.h yuno/yuno.h yunoerror/yunoerror.h yunofile/yunofile.h yunomemory/yunomemory.h yunomutex/yunomutex.h yunopipe/yunopipe.h yunoprocess/yunoprocess.h yunosemaphore/yunosemaphore.h yunoshared-memory/yunoshared-memory.h yunothread/yunothread.h yunotime/yunotime.h utility/utility.h >> yuno.h 

yuno.lib: $(SHAREDDIR)/shared.lib utility/utility.lib yunoerror/yunoerror.lib yunofile/yunofile.lib yunomemory/yunomemory.lib yunomutex/yunomutex.lib yunopipe/yunopipe.lib yunoprocess/yunoprocess.lib yunosemaphore/yunosemaphore.lib yunoshared-memory/yunoshared-memory.lib yunothread/yunothread.lib yunotime/yunotime.lib
	cd $(tempdir) && \
	ar x $(SHAREDDIR)/shared.lib && \
	ar x $(workdir)/utility/utility.lib && \
	ar x $(workdir)/yunoerror/yunoerror.lib && \
	ar x $(workdir)/yunofile/yunofile.lib && \
	ar x $(workdir)/yunomemory/yunomemory.lib && \
	ar x $(workdir)/yunomutex/yunomutex.lib && \
	ar x $(workdir)/yunopipe/yunopipe.lib && \
	ar x $(workdir)/yunoprocess/yunoprocess.lib && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.lib && \
	ar x $(workdir)/yunoshared-memory/yunoshared-memory.lib && \
	ar x $(workdir)/yunothread/yunothread.lib && \
	ar x $(workdir)/yunotime/yunotime.lib && \
	ar r $(workdir)/yuno.lib *.o 

yuno.dll: $(SHAREDDIR)/shared.lib utility/utility.lib yunoerror/yunoerror.lib yunofile/yunofile.lib yunomemory/yunomemory.lib yunomutex/yunomutex.lib yunopipe/yunopipe.lib yunoprocess/yunoprocess.lib yunosemaphore/yunosemaphore.lib yunoshared-memory/yunoshared-memory.lib yunothread/yunothread.lib yunotime/yunotime.lib
	cd $(tempdir) && \
	ar x $(SHAREDDIR)/shared.lib && \
	ar x $(workdir)/utility/utility.lib && \
	ar x $(workdir)/yunoerror/yunoerror.lib && \
	ar x $(workdir)/yunofile/yunofile.lib && \
	ar x $(workdir)/yunomemory/yunomemory.lib && \
	ar x $(workdir)/yunomutex/yunomutex.lib && \
	ar x $(workdir)/yunopipe/yunopipe.lib && \
	ar x $(workdir)/yunoprocess/yunoprocess.lib && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.lib && \
	ar x $(workdir)/yunoshared-memory/yunoshared-memory.lib && \
	ar x $(workdir)/yunothread/yunothread.lib && \
	ar x $(workdir)/yunotime/yunotime.lib && \
	gcc $(CFLAGS) -shared -o $(workdir)/yuno.dll *.o 
