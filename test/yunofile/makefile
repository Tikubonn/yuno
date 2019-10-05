
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno
export LD_LIBRARY_PATH += $(CURDIR)

ifeq ($(target), windows)
executefile=yunofile.exe
else
ifeq ($(target), linux)
executefile=yunofile
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: .always
	rm -f compiled/main.o
	rm -f compiled/test-open-yunofile.o
	rm -f compiled/test-open-async-yunofile.o
	rm -f compiled/test-open-async-yunofile2.o

$(YUNODLL): $(rootdir)/dist/$(YUNODLL)
	cp $(rootdir)/dist/$(YUNODLL) $(YUNODLL)

compiled/main.o: src/main.c $(YUNODLL)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

compiled/test-open-yunofile.o: src/test-open-yunofile.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-open-yunofile.c -o compiled/test-open-yunofile.o

compiled/test-open-async-yunofile.o: src/test-open-async-yunofile.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-open-async-yunofile.c -o compiled/test-open-async-yunofile.o

compiled/test-open-async-yunofile2.o: src/test-open-async-yunofile2.c $(YUNODLL)
	gcc $(CFLAGS) -c src/test-open-async-yunofile2.c -o compiled/test-open-async-yunofile2.o

$(executefile): compiled/main.o compiled/test-open-yunofile.o compiled/test-open-async-yunofile.o compiled/test-open-async-yunofile2.o $(YUNODLL)
	gcc $(CFLAGS) compiled/main.o compiled/test-open-yunofile.o compiled/test-open-async-yunofile.o compiled/test-open-async-yunofile2.o -o $(executefile)

.always:
