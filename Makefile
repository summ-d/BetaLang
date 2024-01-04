CC = g++
OUT = build
SRC = src
SRCEXT = cpp
LIBSTR = -L lib/string
LIBALL = -L lib/alloc
LIBMAP = -L lib/map
LIBLL = -L lib/linkedlist
LIBSP = -L lib/smartpointer
INC = -I include

make_string:
	$(CC) $(SRC)/main.cpp $(LIBSTR) $(LIBALL) -o $(OUT)/main
