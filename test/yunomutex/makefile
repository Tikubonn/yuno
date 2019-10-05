
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno
export LD_LIBRARY_PATH += $(CURDIR)

ifeq ($(target), windows)
executefile=yunomutex.exe
else
ifeq ($(target), linux)
executefile=yunomutex
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: 
	rm -f compiled/test-make-yunomutex.o
	rm -f compiled/test-make-yunomutex2.o
	rm -f compiled/main.o

$(YUNODLL): $(rootdir)/dist/$(YUNODLL)
	cp $(rootdir)/dist/$(YUNODLL) $(YUNODLL)

compiled/test-make-yunomutex.o: src/test-make-yunomutex.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-make-yunomutex.c -o compiled/test-make-yunomutex.o

compiled/test-make-yunomutex2.o: src/test-make-yunomutex2.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-make-yunomutex2.c -o compiled/test-make-yunomutex2.o

compiled/main.o: src/main.c $(YUNODLL)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

$(executefile): compiled/test-make-yunomutex.o compiled/test-make-yunomutex2.o compiled/main.o $(YUNODLL)
	gcc $(CFLAGS) compiled/test-make-yunomutex.o compiled/test-make-yunomutex2.o compiled/main.o -o $(executefile)

.always:
