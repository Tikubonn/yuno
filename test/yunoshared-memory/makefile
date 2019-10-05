
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno
export LD_LIBRARY_PATH += $(CURDIR)

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
	rm -f compiled/main.o $(YUNODLL)
	rm -f compiled/test-allocate-yunoshared-memory.o

$(YUNODLL): $(rootdir)/dist/$(YUNODLL)
	cp $(rootdir)/dist/$(YUNODLL) $(YUNODLL)

compiled/main.o: src/main.c $(YUNODLL)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

compiled/test-allocate-yunoshared-memory.o: src/test-allocate-yunoshared-memory.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-allocate-yunoshared-memory.c -o compiled/test-allocate-yunoshared-memory.o

$(executefile): compiled/main.o compiled/test-allocate-yunoshared-memory.o $(YUNODLL)
	gcc $(CFLAGS) compiled/main.o compiled/test-allocate-yunoshared-memory.o -o $(executefile)

.always:

