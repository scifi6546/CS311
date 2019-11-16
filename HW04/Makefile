CFLAGS = -Wall -std=c++17 -ggdb -o3 -Wreorder
CC=g++
main:
	$(MAKE) catch
	$(MAKE) main_cpp
	$(MAKE) counthar
	$(CC) -std=c++17 test.o main.o counthar.o -o out
catch: counthar_test_suites.cpp counthar.h
	$(CC) -c $(CFLAGS) counthar_test_suites.cpp -o test.o
main_cpp: counthar_test_main.cpp
	$(CC) -c $(CFLAGS) counthar_test_main.cpp -o main.o
counthar: 
	$(CC) -c $(CFLAGS) counthar.cpp -o counthar.o
run:
	$(MAKE) main
	./out
time:
	$(MAKE) main
	time ./out
grind:
	$(MAKE) main
	valgrind --leak-check=full ./out
gdb:
	$(MAKE) main
	gdb ./out
