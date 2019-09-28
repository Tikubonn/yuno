
.always:

clean: .always
	rm -f yunotime.lib
	rm -f yunotime.private
	rm -f yunotime.public
	rm -f compiled/yunosleep.o
	
yunotime.private:
	echo > yunotime.private

yunotime.public:
	echo > yunotime.public

yunotime.lib: compiled/yunosleep.o
	ar r yunotime.lib compiled/yunosleep.o

compiled/yunosleep.o: src/yunosleep.c
	gcc $(CFLAGS) -c src/yunosleep.c -o compiled/yunosleep.o
