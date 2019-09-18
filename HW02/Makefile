CFLAGS = -std=c++17
main:
	$(MAKE) catch
	$(MAKE) main_cpp
	g++ -std=c++17 test.o main.o -o out
catch: ksarray_test_suites.cpp
	g++ -c $(CFLAGS) ksarray_test_suites.cpp -o test.o
main_cpp: ksarray_test_main.cpp
	g++ -c $(CFLAGS) ksarray_test_main.cpp -o main.o
run:
	$(MAKE) main
	./out
