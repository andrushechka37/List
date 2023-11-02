.Phony: compile
compile: dump_list.o list.o 
	clang++ dump_list.o list.o -o list

dump_list.o: dump_list.cpp list.h
	clang++ -c dump_list.cpp
list.o: list.cpp list.h
	clang++ -c list.cpp