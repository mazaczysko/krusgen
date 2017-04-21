all: libobos/lib/libobos.a
	gcc -o krusgen src/krusgen.c src/maze.c -lobos -Wall -Ilibobos/include -Llibobos/lib

libobos/lib/libobos.a:
	cd libobos && make all

clean:
	cd libobos && make clean
	rm krusgen
