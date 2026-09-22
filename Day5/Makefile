CC = gcc

all: Day5-1 stackStuff

stackStuff: stack.o main.o
	$(CC) stack.o main.o -o stackTest

Day5-1: Day5-1.c
	$(CC) Day5-1.c -o Day5-1

Day5-2: Day5-2.c
	$(CC) Day5-2.c -o Day5-2
	
clean:
	rm *.o
    
.c.o:
	$(CC) -c $< -o $@
