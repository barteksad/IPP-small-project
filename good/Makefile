CC       = gcc
CPPFLAGS =
CFLAGS   = -Wall -Wextra -std=c11 -O2 -g
LDFLAGS  =

.PHONY: all clean

similar_lines : similar_lines.o row_counter.o row_counter.o helper_functions.o helper_functions.o row.o row.h bintree.o bintree.o

bintree.o : bintree.c bintree.h

row.o : row.c row.h bintree.c bintree.h

helper_functions.o : helper_functions.c helper_functions.h row.c row.h bintree.c bintree.h

row_counter.o : row_counter.c row_counter.h row.c row.h bintree.c bintree.h

similar_lines.o : similar_lines.c row_counter.c row_counter.h helper_functions.c helper_functions.h row.c row.h bintree.c bintree.h

clean :
	rm -f *.o similar_lines