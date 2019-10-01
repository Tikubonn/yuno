
.always:

clean:
	rm -f yuno.a
	rm -f yuno.so
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

yuno.private: .always
	make yunosize.private -C yunosize
	make yunothread.private -C yunothread
	make yunoprocess.private -C yunoprocess
	make yunofile-buffer.private -C yunofile-buffer
	make yunofile.private -C yunofile
	make yunomutex.private -C yunomutex
	make yunosemaphore.private -C yunosemaphore
	make yunopipe.private -C yunopipe
	cat yunosize/yunosize.private yunothread/yunothread.private yunoprocess/yunoprocess.private yunofile-buffer/yunofile-buffer.private yunofile/yunofile.private yunomutex/yunomutex.private yunosemaphore/yunosemaphore.private yunopipe/yunopipe.private > yuno.private

yuno.public: .always
	make yunosize.public -C yunosize 
	make yunothread.public -C yunothread
	make yunoprocess.public -C yunoprocess
	make yunofile-buffer.public -C yunofile-buffer
	make yunofile.public -C yunofile
	make yunomutex.public -C yunomutex
	make yunosemaphore.public -C yunosemaphore
	make yunopipe.public -C yunopipe
	cat yunosize/yunosize.public yunothread/yunothread.public yunoprocess/yunoprocess.public yunofile-buffer/yunofile-buffer.public yunofile/yunofile.public yunomutex/yunomutex.public yunosemaphore/yunosemaphore.public yunopipe/yunopipe.public > yuno.public

temp=$(shell mktemp -d)
workdir:=$(CURDIR)

yuno.a: .always
	make yunothread.a -C yunothread
	make yunoprocess.a -C yunoprocess
	make yunofile-buffer.a -C yunofile-buffer
	make yunofile.a -C yunofile
	make yunomutex.a -C yunomutex
	make yunosemaphore.a -C yunosemaphore
	make yunopipe.a -C yunopipe
	cd $(temp) && \
	ar x $(workdir)/yunothread/yunothread.a && \
	ar x $(workdir)/yunoprocess/yunoprocess.a && \
	ar x $(workdir)/yunofile-buffer/yunofile-buffer.a && \
	ar x $(workdir)/yunofile/yunofile.a && \
	ar x $(workdir)/yunomutex/yunomutex.a && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.a && \
	ar x $(workdir)/yunopipe/yunopipe.a && \
	ar r $(workdir)/yuno.a *.o

yuno.so: .always
	make yunothread.a -C yunothread
	make yunoprocess.a -C yunoprocess
	make yunofile-buffer.a -C yunofile-buffer
	make yunofile.a -C yunofile
	make yunomutex.a -C yunomutex
	make yunosemaphore.a -C yunosemaphore
	make yunopipe.a -C yunopipe
	cd $(temp) && \
	ar x $(workdir)/yunothread/yunothread.a && \
	ar x $(workdir)/yunoprocess/yunoprocess.a && \
	ar x $(workdir)/yunofile-buffer/yunofile-buffer.a && \
	ar x $(workdir)/yunofile/yunofile.a && \
	ar x $(workdir)/yunomutex/yunomutex.a && \
	ar x $(workdir)/yunosemaphore/yunosemaphore.a && \
	ar x $(workdir)/yunopipe/yunopipe.a && \
	gcc $(CFLAGS) -shared -o $(workdir)/yuno.so *.o -lrt

