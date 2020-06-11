
.PHONY: clean
clean:
	make clean -C yunobuffer
	make clean -C yunobitarray
	make clean -C yunoallocator
	make clean -C yunoerror
	make clean -C yunofile
	make clean -C yunoentrypoint
	make clean -C yunoalignment
	make clean -C yunoseconds
	rm -f shared.h
	rm -f shared.lib

.PHONY: h
h:
	make h -C yunobuffer
	make h -C yunobitarray
	make h -C yunoallocator
	make h -C yunoerror
	make h -C yunofile
	make h -C yunowait-mode
	make h -C yunoentrypoint
	make h -C yunoalignment
	make h -C yunoseconds
	make shared.h

.PHONY: lib
lib:
	make lib -C yunobuffer
	make lib -C yunobitarray
	make lib -C yunoallocator
	make shared.lib

temp = $(shell mktemp -d)
workdir = $(CURDIR)

shared.h: yunobuffer/yunobuffer.h yunobitarray/yunobitarray.h yunoallocator/yunoallocator.h yunoerror/yunoerror.h yunofile/yunofile.h yunowait-mode/yunowait-mode.h yunoentrypoint/yunoentrypoint.h yunoalignment/yunoalignment.h yunoseconds/yunoseconds.h
	cat yunobuffer/yunobuffer.h yunobitarray/yunobitarray.h yunoallocator/yunoallocator.h yunoerror/yunoerror.h yunofile/yunofile.h yunowait-mode/yunowait-mode.h yunoentrypoint/yunoentrypoint.h yunoalignment/yunoalignment.h yunoseconds/yunoseconds.h > shared.h

shared.lib: yunobuffer/yunobuffer.lib yunobitarray/yunobitarray.lib yunoallocator/yunoallocator.lib
	cd $(temp) && \
	ar x $(workdir)/yunobuffer/yunobuffer.lib && \
	ar x $(workdir)/yunobitarray/yunobitarray.lib && \
	ar x $(workdir)/yunoallocator/yunoallocator.lib && \
	ar r $(workdir)/shared.lib *.o 
