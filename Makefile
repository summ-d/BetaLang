FLAGS = -Wall -fconcepts -o main
CC = g++
DIR = src/compiler/util/collections

test:
	$(CC) -o deps $(DIR)/collections.hpp
				  $(DIR)/collections.cpp
				  $(DIR)/special/specialptr.hpp
				  $(DIR)/special/smartarray.hpp
				  $(DIR)/special/smartarray.cpp
	$(CC) -o main main.cpp deps.o
	./main