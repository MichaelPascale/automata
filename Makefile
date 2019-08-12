CC = g++
CFLAGS = -Wall -pedantic
OBJECTS = dfa.o dfa_driver.o nfa.o nfa_driver.o tm.o
EXE = run_dfa run_nfa run_tm

all: run_dfa run_nfa run_tm

run_dfa: dfa.o dfa_driver.o
	$(CC) $(CFLAGS) -o run_dfa dfa.o dfa_driver.o

run_nfa: nfa.o nfa_driver.o
	$(CC) $(CFLAGS) -o run_nfa nfa.o nfa_driver.o

run_tm: tm.o
	$(CC) $(CFLAGS) -o run_tm tm.o

dfa_driver.o: dfa_driver.cpp
	$(CC) $(CFLAGS) -c dfa_driver.cpp -o dfa_driver.o
	
dfa.o: dfa.cpp dfa.h
	$(CC) $(CFLAGS) -c dfa.cpp -o dfa.o
	
nfa_driver.o: nfa_driver.cpp
	$(CC) $(CFLAGS) -c nfa_driver.cpp -o nfa_driver.o
	
nfa.o: nfa.cpp nfa.h
	$(CC) $(CFLAGS) -c nfa.cpp -o nfa.o

tm.o: tm.c
	$(CC) $(CFLAGS) -c tm.c -o tm.o
	

clean:
	rm $(OBJECTS) $(EXE)
