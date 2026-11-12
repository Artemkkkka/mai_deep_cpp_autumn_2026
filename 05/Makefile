CC=g++
FLAGS=-std=c++20 -Wall -Werror -Wextra

all: test_serializer.exe

test_serializer.exe: test_serializer.o serializer.o
	$(CC) $(FLAGS) -o test_serializer.exe test_serializer.o serializer.o -lgtest -lgtest_main

serializer.o: serializer.cpp serializer.hpp
	$(CC) $(FLAGS) -c serializer.cpp

test_serializer.o: test_serializer.cpp data.hpp serializer.hpp
	$(CC) $(FLAGS) -c test_serializer.cpp

test: test_serializer.exe
	./test_serializer.exe

clean:
	rm -rf *.o test_serializer.exe