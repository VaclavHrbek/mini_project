
CC = gcc
CFLAG = -g -O0 

all: build main

main: main.o my_math.a  
	$(CC) $(CFLAG) -I. build/$^ -o build/$@

my_math.o: my_math.c
	$(CC) $(CFLAG) -c $^ -o build/$@

main.o: main.c
	$(CC) $(CFLAG) -c $^ -o build/$@

my_math.a: my_math.o 
	ar -rcs $@ build/$^

build: 
	mkdir build/
