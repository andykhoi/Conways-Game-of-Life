#include "brians_brain.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell_grid.h"
#include "cell.h"

/*
 * Input:
 *      int numRows, the number of rows in the game
 *      int numCols, the number of cols in the game
 * Output:
 *      Returns a CellGrid* that corresponds to the
 *      first generation game state
 * Summary:
 *      Returns the game state of the first generation
 */
CellGrid* FirstGeneration(int numRows, int numCols, List* seedCells) {
    CellGrid* result = CellGrid_Create(numRows, numCols);
    ListNode* currentNode;
    for (currentNode = seedCells->head; currentNode != NULL; currentNode = currentNode->next) {
        CellGrid_SetCell(result, currentNode->data);
    }
    return result;
}

/*
 * Input:
 *      CellGrid* generation, a pointer to a game state
 * Output:
 *      Returns a CellGrid*, a pointer to a game state
 * Summary:
 *      Calculates the game state of the generation directly
 *      after *generation and returns it
 */

CellGrid* NextGeneration(CellGrid* generation) {
    // TODO: complete this function
    
    CellGrid* nextGeneration = CellGrid_Create(generation->numRows, generation->numCols);
    nextGeneration->numRows = generation->numRows;
    nextGeneration->numCols = generation->numCols;
    for (int i = 0; i < generation->numRows; i++) {
        for (int j = 0; j < generation->numCols; j++) {
	    Cell nextCell = Cell_Create(i, j, generation->grid[i][j].s);
	    nextGeneration->grid[i][j] = nextCell;
	}
    }
    
    for (int i = 0; i < generation->numRows; i++) {
        for (int j = 0; j < generation->numCols; j++) {
	    if (generation->grid[i][j].s == 2) {
	        nextGeneration->grid[i][j].s = 0;
	    }
	    else if (generation->grid[i][j].s == 1) {
		nextGeneration->grid[i][j].s = 2;
	    }
	    else {
		/*int onCounter = 0;
	        if (j - 1 >= 0) {
		    if (generation->grid[i - 1][j - 1].s == 1 && i - 1 >= 0) {
		        onCounter++;
		    }
		    if (generation->grid[i][j - 1].s == 1) {
			onCounter++;
		    }
		    if (generation->grid[i + 1][j - 1].s == 1 && i + 1 < generation->numRows) {
			onCounter++;
		    }
		}
		if (generation->grid[i - 1][j].s == 1 && i - 1 >= 0) {
		    onCounter++;
		}
		if (generation->grid[i + 1][j].s == 1 && i + 1 < generation->numRows) {
                    onCounter++;
		}
		if (j + 1 < generation->numCols) {
		    if (generation->grid[i - 1][j + 1].s == 1 && i - 1 >= 0) {
			onCounter++;
		    }
		    if (generation->grid[i][j + 1].s == 1) {
			onCounter++;
		    }
		    if (generation->grid[i + 1][j + 1].s == 1 && i + 1 < generation->numRows) {
			onCounter++;
		    }
		}*/
		List* allNeighbors = List_Create();
		int numOnCells = 0;
		Cell newCell = Cell_Create(i, j, generation->grid[i][j].s);
		allNeighbors = GetNeighboringCells(newCell, generation);
                numOnCells = CountOnNeighborCells(generation, allNeighbors);
		//printf("%d\n", numOnCells);
		if (numOnCells == 2) {
		    nextGeneration->grid[i][j].s = 1;
		}
	    }
	}
    }
    return nextGeneration;
	    
}

/*
 * Input:
 *      CellGrid* generation, a pointer to a game state
 *      Cell coord, a Cell of the game state
 * Output:
 *      Returns true if the Cell is CellIsOn
 * Summary:
 *      Checks if coord is a valid index of *generation and
 *      its corresponding Cell is CellIsOn
 */
bool CellIsOn(CellGrid* generation, int row, int col) {
    if (!CellGrid_Inbounds(generation, row, col)) {
        printf("CellIsOn Error: invalid Cell\n");
        exit(0);
    }
    return generation->grid[row][col].s == ON;
}

/*
 * Input:
 *      Cell coord, a Cell of the game state
 *      CellGrid* generation, a pointer to a game state
 * Output:
 *      Returns a List* to a List of neighboring Cells
 * Summary:
 *      Calculates neighboring Cells of *generation at coord and
 *      returns them as a List
 */

List* GetNeighboringCells(Cell cell, CellGrid* generation) {
    // TODO: complete this function
    // Hint: Use List_Create to instantiate the list and List_PushFront to add elements to the list
    List* list = List_Create();
    if(cell.x + 1 < generation->numRows) {
	    Cell C1 = generation->grid[cell.x+1][cell.y];
	    List_PushFront(list, C1);
            if(cell.y - 1 >=0) {
		   Cell C2 = generation->grid[cell.x+1][cell.y-1];
		   List_PushFront(list,C2);
	    }
	    if(cell.y + 1 < generation->numCols) {
		   Cell C3 = generation->grid[cell.x+1][cell.y+1];
		   List_PushFront(list,C3);
	    }
    }
    if(cell.x - 1 >= 0) {
	   Cell C4 = generation->grid[cell.x-1][cell.y];
	   List_PushFront(list, C4);
	   if(cell.y + 1 < generation->numCols) {
		  Cell C5 = generation->grid[cell.x-1][cell.y+1];
		  List_PushFront(list,C5);
	   }
	   if(cell.y - 1 >= 0) {
		  Cell C6 = generation->grid[cell.x-1][cell.y-1];
		  List_PushFront(list,C6);
	   }
    }
    if(cell.y + 1 < generation->numCols) {
	   Cell C7 = generation->grid[cell.x][cell.y+1];
	   List_PushFront(list,C7);
    }
    if(cell.y - 1 >= 0) {
	   Cell C8 = generation->grid[cell.x][cell.y-1];
           List_PushFront(list,C8);
    }
    return list;
    
}

/*List* GetNeighboringCells(Cell cell, CellGrid* generation) {
    // TODO: complete this function
    // Hint: Use List_Create to instantiate the list and List_PushFront to add elements to the list
    
    List* result = List_Create();
    if (cell.y - 1 >= 0) {
	if (cell.x - 1 >= 0) {
            Cell C1 = generation->grid[cell.x - 1][cell.y - 1];
	    List_PushFront(result, C1);

	    Cell C2 = generation->grid[cell.x - 1][cell.y];
	    List_PushFront(result, C2);
        }
	Cell C3 = generation->grid[cell.x][cell.y - 1];
	List_PushFront(result, C3);
        if (cell.x + 1 < generation->numRows) {
	    Cell C4 = generation->grid[cell.x + 1][cell.y - 1];
            List_PushFront(result, C4);

	    Cell C5 = generation->grid[cell.x + 1][cell.y];
	    List_PushFront(result, C5);
	}
    }
    if (cell.y + 1 < generation->numCols) {
	if (cell.x - 1 >= 0) {
            Cell C6 = generation->grid[cell.x - 1][cell.y + 1];
	    List_PushFront(result, C6);
	}
        Cell C7 = generation->grid[cell.x][cell.y + 1];
	List_PushFront(result, C7);
        if (cell.x + 1 < generation->numRows) {
            Cell C8 = generation->grid[cell.x + 1][cell.y + 1];
	    List_PushFront(result, C8);
	}
    }
    Cell C1 = generation->grid[cell.x - 1][cell.y - 1];
    List_PushFront(result, C1);
    Cell C2 = generation->grid[cell.x - 1][cell.y];
    List_PushFront(result, C2);
    Cell C3 = generation->grid[cell.x][cell.y - 1];
    List_PushFront(result, C3);
    Cell C4 = generation->grid[cell.x + 1][cell.y - 1];
    List_PushFront(result, C4);
    Cell C5 = generation->grid[cell.x + 1][cell.y];
    List_PushFront(result, C5);
    Cell C6 = generation->grid[cell.x - 1][cell.y + 1];
    List_PushFront(result, C6);
    Cell C7 = generation->grid[cell.x][cell.y + 1];
    List_PushFront(result, C7);
    Cell C8 = generation->grid[cell.x + 1][cell.y + 1];
    List_PushFront(result, C8);

    return result;
*/

/*
 * Input:
 *      CellGrid* generation, a pointer to a game state
 *      List* neighbors, a List of neighbors of a Cell
 * Output:
 *      Returns the number of neighboring Cells that are on
 * Summary:
 *      Counts the number of Cells in *neighbors that
 *      correspond to live Cells in *generation
 */
int CountOnNeighborCells(CellGrid* generation, List* neighbors) {
    ListNode* ptr;
    int result = 0;
    if (generation == NULL || neighbors == NULL) {
        printf("Error in CountOnNeighborCells: NULL parameter passed\n");
        exit(0);
    }
    for (ptr = neighbors->head; ptr != NULL; ptr = ptr->next) {
        if (Cell_IsOn(ptr->data)) {
            result++;
        }
    }
    return result;
}
