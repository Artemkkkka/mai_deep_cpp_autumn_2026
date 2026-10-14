CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra

all: test_parser.exe

test_parser.exe: test_parser.o parser.o
	$(CC) $(FLAGS) -o test_parser.exe test_parser.o parser.o -lgtest -lgtest_main

parser.o: parser.cpp parser.hpp
	$(CC) $(FLAGS) -c parser.cpp

test_parser.o: test_parser.cpp parser.hpp
	$(CC) $(FLAGS) -c test_parser.cpp

test: test_parser.exe
	./test_parser.exe

clean:
	rm -rf *.o test_parser.exe