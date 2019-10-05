
.always:

clean: .always
	rm -f yuno.private
	rm -f yuno.public
	rm -f yuno.lib
	rm -f yuno.dll
	make clean -C yunosize
	make clean -C yunoprocess
	make clean -C yunothread
	make clean -C yunofile-buffer
	make clean -C yunofile
	make clean -C yunomutex
	make clean -C yunosemaphore
	make clean -C yunotime
	make clean -C yunopipe
	make clean -C yunobitarray
	make clean -C yunoallocator
	make clean -C yunoshared-memory

yuno.private: .always
	make yunosize.private -C yunosize
	make yunoprocess.private -C yunoprocess
	make yunothread.private -C yunothread
	make yunofile-buffer.private -C yunofile-buffer
	make yunofile.private -C yunofile
	make yunomutex.private -C yunomutex
	make yunosemaphore.private -C yunosemaphore
	make yunotime.private -C yunotime
	make yunopipe.private -C yunopipe
	make yunobitarray.private -C yunobitarray
	make yunoallocator.private -C yunoallocator
	make yunoshared-memory.private -C yunoshared-memory
	cat yunosize/yunosize.private yunobitarray/yunobitarray.private yunoallocator/yunoallocator.private yunoshared-memory/yunoshared-memory.private yunoprocess/yunoprocess.private yunothread/yunothread.private yunofile-buffer/yunofile-buffer.private yunofile/yunofile.private yunomutex/yunomutex.private yunosemaphore/yunosemaphore.private yunotime/yunotime.private yunopipe/yunopipe.private > yuno.private

yuno.public: .always
	make yunosize.public -C yunosize
	make yunoprocess.public -C yunoprocess
	make yunothread.public -C yunothread
	make yunofile-buffer.public -C yunofile-buffer
	make yunofile.public -C yunofile
	make yunomutex.public -C yunomutex
	make yunosemaphore.public -C yunosemaphore
	make yunotime.public -C yunotime
	make yunopipe.public -C yunopipe
	make yunobitarray.public -C yunobitarray
	make yunoallocator.public -C yunoallocator
	make yunoshared-memory.public -C yunoshared-memory
	cat yunosize/yunosize.public yunobitarray/yunobitarray.public yunoallocator/yunoallocator.public yunoshared-memory/yunoshared-memory.public yunoprocess/yunoprocess.public yunothread/yunothread.public yunofile-buffer/yunofile-buffer.public yunofile/yunofile.public yunomutex/yunomutex.public yunosemaphore/yunosemaphore.public yunotime/yunotime.public yunopipe/yunopipe.public > yuno.public

temp=$(shell mktemp -d)
workdir=$(CURDIR)

yunoprocess/yunoprocess.lib: .always
	make yunoprocess.lib -C yunoprocess

yunothread/yunothread.lib: .always
	make yunothread.lib -C yunothread

yunofile-buffer/yunofile-buffer.lib: .always
	make yunofile-buffer.lib -C yunofile-buffer

yunofile/yunofile.lib: .always
	make yunofile.lib -C yunofile

yunomutex/yunomutex.lib: .always
	make yunomutex.lib -C yunomutex

yunosemaphore/yunosemaphore.lib: .always
	make yunosemaphore.lib -C yunosemaphore

yunotime/yunotime.lib: .always
	make yunotime.lib -C yunotime

yunopipe/yunopipe.lib: .always
	make yunopipe.lib -C yunopipe

publicyunopipe/yunopipe.lib: .always
	make yunopipe.lib -C yunopipe

yunobitarray/yunobitarray.lib: .always
	make yunobitarray.lib -C yunobitarray

yunoallocator/yunoallocator.lib: .always
	make yunoallocator.lib -C yunoallocator

yunoshared-memory/yunoshared-memory.lib: .always
	make yunoshared-memory.lib -C yunoshared-memory

yuno.lib: yunoprocess/yunoprocess.lib yunothread/yunothread.lib yunofile-buffer/yunofile-buffer.lib yunofile/yunofile.lib yunomutex/yunomutex.lib yunosemaphore/yunosemaphore.lib yunotime/yunotime.lib yunopipe/yunopipe.lib yunobitarray/yunobitarray.lib yunoallocator/yunoallocator.lib yunoshared-memory/yunoshared-memory.lib
	cd $(temp) && \
	ar x $(workdir)/yunoprocess/yunoprocess.lib && \
	ar x $(workdir)/yunothread/yunothread.lib && \
	ar x $(workdir)/yunofile-buffer/yunofile-buffer.lib && \
	ar x $(workdir)/yunofile/yunofile.lib && \
	ar x $(workdir)/yunomutex/yunomutex.lib && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.lib && \
	ar x $(workdir)/yunotime/yunotime.lib && \
	ar x $(workdir)/yunopipe/yunopipe.lib && \
	ar x $(workdir)/yunobitarray/yunobitarray.lib && \
	ar x $(workdir)/yunoallocator/yunoallocator.lib && \
	ar x $(workdir)/yunoshared-memory/yunoshared-memory.lib && \
	ar r $(workdir)/yuno.lib *.o

yuno.dll: yunoprocess/yunoprocess.lib yunothread/yunothread.lib yunofile-buffer/yunofile-buffer.lib yunofile/yunofile.lib yunomutex/yunomutex.lib yunosemaphore/yunosemaphore.lib yunotime/yunotime.lib yunopipe/yunopipe.lib yunobitarray/yunobitarray.lib yunoallocator/yunoallocator.lib yunoshared-memory/yunoshared-memory.lib
	cd $(temp) && \
	ar x $(workdir)/yunoprocess/yunoprocess.lib && \
	ar x $(workdir)/yunothread/yunothread.lib && \
	ar x $(workdir)/yunofile-buffer/yunofile-buffer.lib && \
	ar x $(workdir)/yunofile/yunofile.lib && \
	ar x $(workdir)/yunomutex/yunomutex.lib && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.lib && \
	ar x $(workdir)/yunotime/yunotime.lib && \
	ar x $(workdir)/yunopipe/yunopipe.lib && \
	ar x $(workdir)/yunobitarray/yunobitarray.lib && \
	ar x $(workdir)/yunoallocator/yunoallocator.lib && \
	ar x $(workdir)/yunoshared-memory/yunoshared-memory.lib && \
	gcc $(CFLAGS) -shared -o $(workdir)/yuno.dll *.o -lpsapi
