.PHONY: start
start: dump_list.o list.o list_func.o
	clang++ dump_list.o list.o  list_func.o -o list && "/Users/anzhiday/Documents/list/"list

dump_list.o: dump_list.cpp list.h
	clang++ -c dump_list.cpp
list.o: list.cpp list.h
	clang++ -c list.cpp
list_func.o: list_func.cpp
	clang++ -c list_func.cpp