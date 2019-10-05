
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno

ifeq ($(target), windows)
executefile=yunoshared-memory.exe
else
ifeq ($(target), linux)
executefile=yunoshared-memory
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: .always
	rm -f compiled/main.o $(yunolib)
	rm -f compiled/test-allocate-yunoshared-memory.o

ifeq ($(target), windows)
yunolib=yuno.dll
else
ifeq ($(target), linux)
yunolib=yuno.so
else
endif
endif

$(yunolib): $(rootdir)/dist/$(yunolib)
	cp $(rootdir)/dist/$(yunolib) $(yunolib)

compiled/main.o: src/main.c $(yunolib)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

compiled/test-allocate-yunoshared-memory.o: src/test-allocate-yunoshared-memory.c $(yunolib)
	gcc $(CFLAGS) -c src/test-allocate-yunoshared-memory.c -o compiled/test-allocate-yunoshared-memory.o

$(executefile): compiled/main.o compiled/test-allocate-yunoshared-memory.o $(yunolib)
	gcc $(CFLAGS) compiled/main.o compiled/test-allocate-yunoshared-memory.o -o $(executefile)

.always:
