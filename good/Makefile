CC       = gcc
CPPFLAGS =
CFLAGS   = -Wall -Wextra -std=c11 -O2
LDFLAGS  =

.PHONY: all clean

similar_lines : similar_lines.o row_counter.o row_counter.o helper_functions.o helper_functions.o row.o word.o

word.o : word.c word.h

row.o : row.c row.h word.c word.h

helper_functions.o : helper_functions.c helper_functions.h row.c row.h word.c word.h

row_counter.o : row_counter.c row_counter.h row.c row.h word.c word.h

similar_lines.o : similar_lines.c row_counter.c row_counter.h helper_functions.c helper_functions.h row.c row.h word.c word.h

clean :
	rm -f *.o similar_lines