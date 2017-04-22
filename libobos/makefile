all:
	-mkdir obj
	-mkdir lib
	gcc -c src/obos.c -o obj/obos.o
	ar -cvq lib/libobos.a obj/obos.o
	ar -t lib/libobos.a
	
clean:
	-rm -rf obj
	-rm -rf lib
