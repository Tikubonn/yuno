
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno

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

compiled/test-make-yunopipe.o: src/test-make-yunopipe.c $(yunolib)
	gcc $(CFLAGS) -c src/test-make-yunopipe.c -o compiled/test-make-yunopipe.o

compiled/test-make-yunopipe2.o: src/test-make-yunopipe2.c $(yunolib)
	gcc $(CFLAGS) -c src/test-make-yunopipe2.c -o compiled/test-make-yunopipe2.o

$(executefile): compiled/main.o compiled/test-make-yunopipe.o compiled/test-make-yunopipe2.o $(yunolib)
	gcc $(CFLAGS) compiled/main.o compiled/test-make-yunopipe.o compiled/test-make-yunopipe2.o -o $(executefile)

.always:
