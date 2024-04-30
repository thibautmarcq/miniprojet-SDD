# MONO 3
# Maëlle LIU 21204734
# Thibaut MARCQ 21202966

CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
# CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS =   main ex3-1 ex3-3

.PHONY:	all clean

all: $(PROGRAMS)

main: biblioLC/biblioLC.o biblioLC/entreeSortieLC.o biblioH/biblioH.o biblioH/entreeSortieH.o main.c
	$(CC) -o $@ $(CFLAGS) $^

ex3-1: biblioLC/biblioLC.o biblioLC/entreeSortieLC.o biblioH/biblioH.o biblioH/entreeSortieH.o ex3-1.c
	$(CC) -o $@ $(CFLAGS) $^

ex3-3: biblioLC/biblioLC.o biblioLC/entreeSortieLC.o biblioH/biblioH.o biblioH/entreeSortieH.o ex3-3.c
	$(CC) -o $@ $(CFLAGS) $^


biblioLC/biblioLC.o: biblioLC/biblioLC.c
	$(CC) $(CFLAGS) -c $< -o $@

biblioLC/entreeSortieLC.o: biblioLC/entreeSortieLC.c
	$(CC) $(CFLAGS) -c $< -o $@

biblioH/biblioH.o: biblioH/biblioH.c
	$(CC) $(CFLAGS) -c $< -o $@

biblioH/biblioH/entreeSortieH.o: biblioH/entreeSortieH.c
	$(CC) $(CFLAGS) -c $< -o $@


#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)
	rm -f biblioH/*.o biblioLC/*.o
