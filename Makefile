# LUNGU Mihai-Teodor - 313CD #

build: functions.c main.c
	gcc -Wall -g functions.c main.c -o quadtree -lm

clean:
	rm -f quadtree

run:
	./quadtree