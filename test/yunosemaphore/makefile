
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno
export LD_LIBRARY_PATH += $(CURDIR)

ifeq ($(target), windows)
executefile=yunosemaphore.exe
else
ifeq ($(target), linux)
executefile=yunosemaphore
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: .always
	rm -f compiled/main.o
	rm -f compiled/test-make-yunosemaphore.o

$(YUNODLL): $(rootdir)/dist/$(YUNODLL)
	cp $(rootdir)/dist/$(YUNODLL) $(YUNODLL)

compiled/main.o: src/main.c $(YUNODLL)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

compiled/test-make-yunosemaphore.o: src/test-make-yunosemaphore.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-make-yunosemaphore.c -o compiled/test-make-yunosemaphore.o

$(executefile): compiled/main.o compiled/test-make-yunosemaphore.o $(YUNODLL)
	gcc $(CFLAGS) compiled/main.o compiled/test-make-yunosemaphore.o -o $(executefile)

.always:
