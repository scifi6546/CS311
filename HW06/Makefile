CFLAGS = -Wall -ansi -pedantic -Wextra -Wconversion -std=c++17 -ggdb -o0 -Wreorder
CC=g++
main:
	$(MAKE) catch
	$(MAKE) main_cpp
	$(CC) -std=c++17 test.o main.o -o out
catch: dp6_test_suites.cpp
	$(CC) -c $(CFLAGS) dp6_test_suites.cpp -o test.o
main_cpp: dp6_test_main.cpp
	$(CC) -c $(CFLAGS) dp6_test_main.cpp -o main.o
run:
	$(MAKE) main
	./out
grind:
	$(MAKE) main
	valgrind --leak-check=full ./out
gdb:
	$(MAKE) main
	gdb ./out
