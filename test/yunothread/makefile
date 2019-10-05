
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno

ifeq ($(target), windows)
executefile=yunothread.exe
else
ifeq ($(target), linux)
executefile=yunothread
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: .always
	rm -f compiled/main.o
	rm -f compiled/test-make-yunothread.o
	rm -f compiled/test-make-yunothread2.o

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

compiled/test-make-yunothread.o: src/test-make-yunothread.c $(yunolib)
	gcc $(CFLAGS) -c src/test-make-yunothread.c -o compiled/test-make-yunothread.o

compiled/test-make-yunothread2.o: src/test-make-yunothread2.c $(yunolib)
	gcc $(CFLAGS) -c src/test-make-yunothread2.c -o compiled/test-make-yunothread2.o

$(executefile): compiled/main.o compiled/test-make-yunothread.o compiled/test-make-yunothread2.o $(yunolib)
	gcc $(CFLAGS) compiled/main.o compiled/test-make-yunothread.o compiled/test-make-yunothread2.o -o $(executefile)

.always:
