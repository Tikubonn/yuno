
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno

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

compiled/test-make-yunomutex.o: src/test-make-yunomutex.c $(yunolib)
	gcc $(CFLAGS) -c src/test-make-yunomutex.c -o compiled/test-make-yunomutex.o

compiled/test-make-yunomutex2.o: src/test-make-yunomutex2.c $(yunolib)
	gcc $(CFLAGS) -c src/test-make-yunomutex2.c -o compiled/test-make-yunomutex2.o

compiled/main.o: src/main.c $(yunolib)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

$(executefile): compiled/test-make-yunomutex.o compiled/test-make-yunomutex2.o compiled/main.o $(yunolib)
	gcc $(CFLAGS) compiled/test-make-yunomutex.o compiled/test-make-yunomutex2.o compiled/main.o -o $(executefile)

.always:
