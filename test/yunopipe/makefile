
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno
export LD_LIBRARY_PATH += $(CURDIR)

ifeq ($(target), windows)
executefile=yunopipe.exe
else
ifeq ($(target), linux)
executefile=yunopipe
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: .always
	rm -f compiled/main.o
	rm -f compiled/test-make-yunopipe.o
	rm -f compiled/test-make-yunopipe2.o

$(YUNODLL): $(rootdir)/dist/$(YUNODLL)
	cp $(rootdir)/dist/$(YUNODLL) $(YUNODLL)

compiled/main.o: src/main.c $(YUNODLL)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

compiled/test-make-yunopipe.o: src/test-make-yunopipe.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-make-yunopipe.c -o compiled/test-make-yunopipe.o

compiled/test-make-yunopipe2.o: src/test-make-yunopipe2.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-make-yunopipe2.c -o compiled/test-make-yunopipe2.o

$(executefile): compiled/main.o compiled/test-make-yunopipe.o compiled/test-make-yunopipe2.o $(YUNODLL)
	gcc $(CFLAGS) compiled/main.o compiled/test-make-yunopipe.o compiled/test-make-yunopipe2.o -o $(executefile)

.always:

