
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno

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

compiled/test-open-yunofile.o: src/test-open-yunofile.c $(yunolib)
	gcc $(CFLAGS) -c src/test-open-yunofile.c -o compiled/test-open-yunofile.o

compiled/test-open-async-yunofile.o: src/test-open-async-yunofile.c $(yunolib)
	gcc $(CFLAGS) -c src/test-open-async-yunofile.c -o compiled/test-open-async-yunofile.o

compiled/test-open-async-yunofile2.o: src/test-open-async-yunofile2.c $(yunolib)
	gcc $(CFLAGS) -c src/test-open-async-yunofile2.c -o compiled/test-open-async-yunofile2.o

$(executefile): compiled/main.o compiled/test-open-yunofile.o compiled/test-open-async-yunofile.o compiled/test-open-async-yunofile2.o $(yunolib)
	gcc $(CFLAGS) compiled/main.o compiled/test-open-yunofile.o compiled/test-open-async-yunofile.o compiled/test-open-async-yunofile2.o -o $(executefile)

.always:
