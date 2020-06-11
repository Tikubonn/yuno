
.PHONY: clean
clean: 
	rm -f compiled/test-yunoprocess.o
	rm -f compiled/test-yunoprocess1.o
	rm -f compiled/test-yunoprocess2.o
	rm -f yunoprocess.lib 

.PHONY: lib
lib: 
	make yunoprocess.lib 

yunoprocess.lib: compiled/test-yunoprocess.o compiled/test-yunoprocess1.o compiled/test-yunoprocess2.o 
	ar r yunoprocess.lib compiled/test-yunoprocess.o compiled/test-yunoprocess1.o compiled/test-yunoprocess2.o 

compiled/test-yunoprocess.o: src/test-yunoprocess.c 
	gcc $(CFLAGS) -c src/test-yunoprocess.c -o compiled/test-yunoprocess.o

compiled/test-yunoprocess1.o: src/test-yunoprocess1.c 
	gcc $(CFLAGS) -c src/test-yunoprocess1.c -o compiled/test-yunoprocess1.o

compiled/test-yunoprocess2.o: src/test-yunoprocess2.c 
	gcc $(CFLAGS) -c src/test-yunoprocess2.c -o compiled/test-yunoprocess2.o
