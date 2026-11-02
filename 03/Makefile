CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra

all: test_matrix.exe

test_matrix.exe: test_matrix.o matrix.o
	$(CC) $(FLAGS) -o test_matrix.exe test_matrix.o matrix.o -lgtest -lgtest_main

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) -c matrix.cpp

test_matrix.o: test_matrix.cpp matrix.hpp
	$(CC) $(FLAGS) -c test_matrix.cpp

test: test_matrix.exe
	./test_matrix.exe

clean:
	rm -rf *.o test_matrix.exe