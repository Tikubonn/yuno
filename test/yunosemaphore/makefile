
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno

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

compiled/test-make-yunosemaphore.o: src/test-make-yunosemaphore.c $(yunolib)
	gcc $(CFLAGS) -c src/test-make-yunosemaphore.c -o compiled/test-make-yunosemaphore.o

$(executefile): compiled/main.o compiled/test-make-yunosemaphore.o $(yunolib)
	gcc $(CFLAGS) compiled/main.o compiled/test-make-yunosemaphore.o -o $(executefile)

.always:
