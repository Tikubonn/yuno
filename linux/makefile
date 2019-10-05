
.always:

clean:
	rm -f libyuno.a
	rm -f libyuno.so
	rm -f yuno.private
	rm -f yuno.public
	make clean -C yunosize
	make clean -C yunothread
	make clean -C yunoprocess
	make clean -C yunofile-buffer
	make clean -C yunofile
	make clean -C yunomutex
	make clean -C yunosemaphore
	make clean -C yunopipe
	make clean -C yunobitarray
	make clean -C yunoallocator
	make clean -C yunoshared-memory
	make clean -C yunotime

yuno.private: .always
	make yunosize.private -C yunosize
	make yunothread.private -C yunothread
	make yunoprocess.private -C yunoprocess
	make yunofile-buffer.private -C yunofile-buffer
	make yunofile.private -C yunofile
	make yunomutex.private -C yunomutex
	make yunosemaphore.private -C yunosemaphore
	make yunopipe.private -C yunopipe
	make yunobitarray.private -C yunobitarray
	make yunoallocator.private -C yunoallocator
	make yunoshared-memory.private -C yunoshared-memory
	make yunotime.private -C yunotime
	cat yunosize/yunosize.private yunothread/yunothread.private yunoprocess/yunoprocess.private yunofile-buffer/yunofile-buffer.private yunofile/yunofile.private yunomutex/yunomutex.private yunosemaphore/yunosemaphore.private yunopipe/yunopipe.private yunobitarray/yunobitarray.private yunoallocator/yunoallocator.private yunoshared-memory/yunoshared-memory.private yunotime/yunotime.private > yuno.private

yuno.public: .always
	make yunosize.public -C yunosize 
	make yunothread.public -C yunothread
	make yunoprocess.public -C yunoprocess
	make yunofile-buffer.public -C yunofile-buffer
	make yunofile.public -C yunofile
	make yunomutex.public -C yunomutex
	make yunosemaphore.public -C yunosemaphore
	make yunopipe.public -C yunopipe
	make yunobitarray.public -C yunobitarray
	make yunoallocator.public -C yunoallocator
	make yunoshared-memory.public -C yunoshared-memory
	make yunotime.public -C yunotime
	cat yunosize/yunosize.public yunothread/yunothread.public yunoprocess/yunoprocess.public yunofile-buffer/yunofile-buffer.public yunofile/yunofile.public yunomutex/yunomutex.public yunosemaphore/yunosemaphore.public yunopipe/yunopipe.public yunobitarray/yunobitarray.public yunoallocator/yunoallocator.public yunoshared-memory/yunoshared-memory.public yunotime/yunotime.public > yuno.public

temp=$(shell mktemp -d)
workdir:=$(CURDIR)

yunothread/yunothread.a: .always
	make yunothread.a -C yunothread

yunoprocess/yunoprocess.a: .always
	make yunoprocess.a -C yunoprocess

yunofile-buffer/yunofile-buffer.a: .always
	make yunofile-buffer.a -C yunofile-buffer

yunofile/yunofile.a: .always
	make yunofile.a -C yunofile

yunomutex/yunomutex.a: .always
	make yunomutex.a -C yunomutex

yunosemaphore/yunosemaphore.a: .always
	make yunosemaphore.a -C yunosemaphore

yunopipe/yunopipe.a: .always
	make yunopipe.a -C yunopipe

yunobitarray/yunobitarray.a: .always
	make yunobitarray.a -C yunobitarray

yunoallocator/yunoallocator.a: .always
	make yunoallocator.a -C yunoallocator

yunoshared-memory/yunoshared-memory.a: .always
	make yunoshared-memory.a -C yunoshared-memory

yunotime/yunotime.a: .always
	make yunotime.a -C yunotime

libyuno.a: yunothread/yunothread.a yunoprocess/yunoprocess.a yunofile-buffer/yunofile-buffer.a yunofile/yunofile.a yunomutex/yunomutex.a yunosemaphore/yunosemaphore.a yunopipe/yunopipe.a yunobitarray/yunobitarray.a yunoallocator/yunoallocator.a yunoshared-memory/yunoshared-memory.a yunotime/yunotime.a
	make yunothread.a -C yunothread
	make yunoprocess.a -C yunoprocess
	make yunofile-buffer.a -C yunofile-buffer
	make yunofile.a -C yunofile
	make yunomutex.a -C yunomutex
	make yunosemaphore.a -C yunosemaphore
	make yunopipe.a -C yunopipe
	make yunobitarray.a -C yunobitarray
	make yunoallocator.a -C yunoallocator
	make yunoshared-memory.a -C yunoshared-memory
	make yunotime.a -C yunotime
	cd $(temp) && \
	ar x $(workdir)/yunothread/yunothread.a && \
	ar x $(workdir)/yunoprocess/yunoprocess.a && \
	ar x $(workdir)/yunofile-buffer/yunofile-buffer.a && \
	ar x $(workdir)/yunofile/yunofile.a && \
	ar x $(workdir)/yunomutex/yunomutex.a && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.a && \
	ar x $(workdir)/yunopipe/yunopipe.a && \
	ar x $(workdir)/yunobitarray/yunobitarray.a && \
	ar x $(workdir)/yunoallocator/yunoallocator.a && \
	ar x $(workdir)/yunoshared-memory/yunoshared-memory.a && \
	ar x $(workdir)/yunotime/yunotime.a && \
	ar r $(workdir)/libyuno.a *.o

libyuno.so: yunothread/yunothread.a yunoprocess/yunoprocess.a yunofile-buffer/yunofile-buffer.a yunofile/yunofile.a yunomutex/yunomutex.a yunosemaphore/yunosemaphore.a yunopipe/yunopipe.a yunobitarray/yunobitarray.a yunoallocator/yunoallocator.a yunoshared-memory/yunoshared-memory.a yunotime/yunotime.a
	make yunothread.a -C yunothread
	make yunoprocess.a -C yunoprocess
	make yunofile-buffer.a -C yunofile-buffer
	make yunofile.a -C yunofile
	make yunomutex.a -C yunomutex
	make yunosemaphore.a -C yunosemaphore
	make yunopipe.a -C yunopipe
	make yunobitarray.a -C yunobitarray
	make yunoallocator.a -C yunoallocator
	make yunoshared-memory.a -C yunoshared-memory
	make yunotime.a -C yunotime
	cd $(temp) && \
	ar x $(workdir)/yunothread/yunothread.a && \
	ar x $(workdir)/yunoprocess/yunoprocess.a && \
	ar x $(workdir)/yunofile-buffer/yunofile-buffer.a && \
	ar x $(workdir)/yunofile/yunofile.a && \
	ar x $(workdir)/yunomutex/yunomutex.a && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.a && \
	ar x $(workdir)/yunopipe/yunopipe.a && \
	ar x $(workdir)/yunobitarray/yunobitarray.a && \
	ar x $(workdir)/yunoallocator/yunoallocator.a && \
	ar x $(workdir)/yunoshared-memory/yunoshared-memory.a && \
	ar x $(workdir)/yunotime/yunotime.a && \
	gcc $(CFLAGS) -shared -o $(workdir)/libyuno.so *.o

.always:

