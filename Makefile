FLAGS = -stdc++20
COMPILER = g++

clangTest:
	clang++  test.cpp -o main

test:
	g++ $(FLAGS) main.cpp -o main

test2:
	$(COMPILER) main.cpp src/compiler/util/collections/collections.hpp src/compiler/util/collections/collections.cpp src/compiler/util/collections/special/specialptr.hpp src/compiler/util/collections/special/smartarray.hpp src/compiler/util/collections/special/smartarray.cpp -g -o main

run:
	./main
