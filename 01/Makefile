CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra

all: test_allocator.exe

test_allocator.exe: test_allocator.o
	$(CC) $(FLAGS) -o test_allocator.exe test_allocator.o -lgtest -lgtest_main

test_allocator.o: test_allocator.cpp allocator.hpp
	$(CC) $(FLAGS) -c test_allocator.cpp

test: test_allocator.exe
	./test_allocator.exe

clean:
	rm -rf *.o test_allocator.exe