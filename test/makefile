
CFLAGS += -I$(CURDIR)

usage: .always
	@echo "Usage:"
	@echo "  make clean     remove unnecessary files."
	@echo "  make [target]  build test and run."

clean: .always
	make clean -C yunobitarray
	make clean -C yunoallocator
	make clean -C yunofile
	make clean -C yunomutex
	make clean -C yunopipe
	make clean -C yunoprocess
	make clean -C yunosemaphore
	make clean -C yunoshared-memory
	make clean -C yunothread

yunobitarray: .always
	make test -C yunobitarray 

yunoallocator: .always
	make test -C yunoallocator 

yunofile: .always
	make test -C yunofile 

yunomutex: .always
	make test -C yunomutex 

yunopipe: .always
	make test -C yunopipe 

yunoprocess: .always
	make test -C yunoprocess 

yunosemaphore: .always
	make test -C yunosemaphore 

yunoshared-memory: .always
	make test -C yunoshared-memory 

yunothread: .always
	make test -C yunothread 

.always:
