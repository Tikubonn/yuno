
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno
export LD_LIBRARY_PATH += $(CURDIR)

ifeq ($(target), windows)
executefile=yunoprocess.exe
else
ifeq ($(target), linux)
executefile=yunoprocess
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: .always
	rm -f compiled/main.o
	rm -f compiled/test-make-yunoprocess.o
	rm -f compiled/test-make-yunoprocess2.o

$(YUNODLL): $(rootdir)/dist/$(YUNODLL)
	cp $(rootdir)/dist/$(YUNODLL) $(YUNODLL)

compiled/main.o: src/main.c $(YUNODLL)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

compiled/test-make-yunoprocess.o: src/test-make-yunoprocess.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-make-yunoprocess.c -o compiled/test-make-yunoprocess.o

compiled/test-make-yunoprocess2.o: src/test-make-yunoprocess2.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-make-yunoprocess2.c -o compiled/test-make-yunoprocess2.o

$(executefile): compiled/main.o compiled/test-make-yunoprocess.o compiled/test-make-yunoprocess2.o $(YUNODLL)
	gcc $(CFLAGS) compiled/main.o compiled/test-make-yunoprocess.o compiled/test-make-yunoprocess2.o -o $(executefile)

.always:
