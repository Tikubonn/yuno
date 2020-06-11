
.PHONY: clean
clean:
	rm -f compiled/make-yunoprocess.o
	rm -f compiled/start-yunoprocess.o
	rm -f compiled/wait-yunoprocess.o
	rm -f compiled/close-yunoprocess.o
	rm -f compiled/get-yunoprocess-exit-code.o
	rm -f yunoprocess.h
	rm -f yunoprocess.lib

.PHONY: h
h:
	make yunoprocess.h 

.PHONY: lib
lib:
	make yunoprocess.lib

yunoprocess.h: yunoprocess.p src/make-yunoprocess.h src/start-yunoprocess.h src/wait-yunoprocess.h src/close-yunoprocess.h src/get-yunoprocess-exit-code.h
	cat yunoprocess.p src/make-yunoprocess.h src/start-yunoprocess.h src/wait-yunoprocess.h src/close-yunoprocess.h src/get-yunoprocess-exit-code.h > yunoprocess.h 

yunoprocess.lib: compiled/make-yunoprocess.o compiled/start-yunoprocess.o compiled/wait-yunoprocess.o compiled/close-yunoprocess.o compiled/get-yunoprocess-exit-code.o
	ar r yunoprocess.lib compiled/make-yunoprocess.o compiled/start-yunoprocess.o compiled/wait-yunoprocess.o compiled/close-yunoprocess.o compiled/get-yunoprocess-exit-code.o

compiled/make-yunoprocess.o: src/make-yunoprocess.c 
	gcc $(CFLAGS) -c src/make-yunoprocess.c -o compiled/make-yunoprocess.o

compiled/start-yunoprocess.o: src/start-yunoprocess.c 
	gcc $(CFLAGS) -c src/start-yunoprocess.c -o compiled/start-yunoprocess.o

compiled/wait-yunoprocess.o: src/wait-yunoprocess.c 
	gcc $(CFLAGS) -c src/wait-yunoprocess.c -o compiled/wait-yunoprocess.o

compiled/close-yunoprocess.o: src/close-yunoprocess.c 
	gcc $(CFLAGS) -c src/close-yunoprocess.c -o compiled/close-yunoprocess.o

compiled/get-yunoprocess-exit-code.o: src/get-yunoprocess-exit-code.c 
	gcc $(CFLAGS) -c src/get-yunoprocess-exit-code.c -o compiled/get-yunoprocess-exit-code.o
