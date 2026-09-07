main: out/test.o out/queue.o
	gcc -o out/test out/test.o out/queue.o

out/test.o: test.c queue.h
	mkdir -p out
	gcc -c test.c -o out/test.o

out/queue.o: queue.c queue.h
	mkdir -p out
	gcc -c queue.c -o out/queue.o
	
clean:
	rm -rf out