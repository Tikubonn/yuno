
.PHONY: clean
clean:
	make clean -C yunobuffer 
	make clean -C yunobitarray 
	make clean -C yunoallocator
	make clean -C yunofile 
	make clean -C yunothread
	make clean -C yunoprocess
	make clean -C yunopipe
	make clean -C yunomemory
	make clean -C yunoshared-memory
	make clean -C yunotime
	make clean -C yunomutex
	make clean -C yunosemaphore
	rm -f yuno.lib

.PHONY: lib
lib:
	make lib -C yunobuffer
	make lib -C yunobitarray
	make lib -C yunoallocator
	make lib -C yunofile
	make lib -C yunothread
	make lib -C yunoprocess
	make lib -C yunopipe 
	make lib -C yunomemory
	make lib -C yunoshared-memory
	make lib -C yunotime
	make lib -C yunomutex
	make lib -C yunosemaphore
	make test.lib 

tempdir = $(shell mktemp -d)
workdir = $(CURDIR)

test.lib: yunobuffer/yunobuffer.lib yunobitarray/yunobitarray.lib yunoallocator/yunoallocator.lib yunofile/yunofile.lib yunothread/yunothread.lib yunoprocess/yunoprocess.lib yunopipe/yunopipe.lib yunomemory/yunomemory.lib yunoshared-memory/yunoshared-memory.lib yunotime/yunotime.lib yunomutex/yunomutex.lib yunosemaphore/yunosemaphore.lib 
	cd $(tempdir) && \
	ar x $(workdir)/yunobuffer/yunobuffer.lib && \
	ar x $(workdir)/yunobitarray/yunobitarray.lib && \
	ar x $(workdir)/yunoallocator/yunoallocator.lib && \
	ar x $(workdir)/yunofile/yunofile.lib && \
	ar x $(workdir)/yunothread/yunothread.lib && \
	ar x $(workdir)/yunoprocess/yunoprocess.lib && \
	ar x $(workdir)/yunopipe/yunopipe.lib && \
	ar x $(workdir)/yunomemory/yunomemory.lib && \
	ar x $(workdir)/yunoshared-memory/yunoshared-memory.lib && \
	ar x $(workdir)/yunotime/yunotime.lib && \
	ar x $(workdir)/yunomutex/yunomutex.lib && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.lib && \
	ar r $(workdir)/test.lib *.o 
