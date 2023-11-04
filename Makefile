.PHONY: start
start: dump_list.o list_test.o list.o
	clang++ dump_list.o list.o list_test.o  -o list && "/Users/anzhiday/Documents/list/"list

dump_list.o: dump_list.cpp list.h
	clang++ -c dump_list.cpp
list_test.o: list_test.cpp list.h
	clang++ -c list_test.cpp
list.o: list.cpp
	clang++ -c list.cpp


