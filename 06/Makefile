CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra

all: test_format.exe

test_format.exe: test_format.o
	$(CC) $(FLAGS) -o test_format.exe test_format.o -lgtest -lgtest_main

test_format.o: test_format.cpp format.hpp
	$(CC) $(FLAGS) -c test_format.cpp

test: test_format.exe
	./test_format.exe

clean:
	rm -rf *.o test_format.exe