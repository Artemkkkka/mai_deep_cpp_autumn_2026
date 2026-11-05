CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra

all: test_bigint.exe

test_bigint.exe: test_bigint.o bigint.o
	$(CC) $(FLAGS) -o test_bigint.exe test_bigint.o bigint.o -lgtest -lgtest_main

bigint.o: bigint.cpp bigint.hpp
	$(CC) $(FLAGS) -c bigint.cpp

test_bigint.o: test_bigint.cpp bigint.hpp
	$(CC) $(FLAGS) -c test_bigint.cpp

test: test_bigint.exe
	./test_bigint.exe

clean:
	rm -rf *.o test_bigint.exe