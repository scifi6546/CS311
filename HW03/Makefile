CFLAGS = -Wall -std=c++17 -ggdb -o0 -Wreorder
CC=g++
main:
	$(MAKE) catch
	$(MAKE) main_cpp
	$(MAKE) dp3
	$(CC) -std=c++17 test.o main.o dp3.o -o out
catch: dp3_test_suites.cpp
	$(CC) -c $(CFLAGS) dp3_test_suites.cpp -o test.o
main_cpp: dp3_test_main.cpp
	$(CC) -c $(CFLAGS) dp3_test_main.cpp -o main.o
dp3: dp3.cpp
	$(CC) -c $(CFLAGS) dp3.cpp -o dp3.o
run:
	$(MAKE) main
	./out
grind:
	$(MAKE) main
	valgrind --leak-check=full ./out
gdb:
	$(MAKE) main
	gdb ./out
