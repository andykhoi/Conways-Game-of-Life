brains_brain.o: brians_brain.c brians_brain.h
	gcc brains_brain.c brians_brain.h -c

list.o: list.c list.h
	gcc list.c -c

cell_grid.o: cell_grid.c cell_grid.h
	gcc cell_grid.c -c

cell.o: cell.c cell.h
	gcc cell.c -c

cell_tester: cell_tester.c cell.o
	gcc cell_tester.c -c 
	gcc cell_tester.o cell.o -lm -o cell_tester

list_tester: list_tester.c list.o cell.o
	gcc list_tester.c -c
	gcc list_tester.o list.o cell.o -o list_tester

cell_grid_tester: cell_grid_tester.c cell_grid.o cell.o
	gcc cell_grid_tester.c -c
	gcc cell_grid_tester.o cell_grid.o cell.o -o cell_grid_tester

brians_brain_cellular_automata: brians_brain_cellular_automata.c brians_brain.o cell_grid.o list.o cell.o
	gcc brians_brain_cellular_automata.c -c
	gcc brians_brain.o cell_grid.o cell.o list.o brians_brain_cellular_automata.o -o brians_brain_cellular_automata 

all: brians_brain_cellular_automata list_tester cell_tester cell_grid_tester

clean:
	rm *.o list_tester cell_tester cell_grid_tester brians_brain_cellular_automata
	
