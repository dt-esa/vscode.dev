/*
   2
   /\
 7/  \8	     | 0 1 2 3 4
 /  6 \	   --+----------
1------3   0 | 0 1 2 4 0
 |\5 /|	   1 | 1 0 5 3 0
 | \/ |	   2 | 2 5 0 6 7
2| /\ |3   3 | 4 3 6 0 8
 |/4 \|	   4 | 0 0 7 8 0
0-----4

Problem description
- 5 nodes with 8 pathes between them
- moving between nodes only allowed along a path (no jumping)
- each node needs to be visited at least once
- each path has to be used, only one time per path

Question:
- how many possible solutions

*/

#include<stdio.h>
#include<stdint.h>

// global array to store the path to node information (only half of array neeeded due to symmetry, row 4 & column 0 all zeros => not needed)
	int mat[4][5] = {
		{ 0, 2, 0, 4, 1 } ,
		{ 0, 0, 7, 6, 5 } ,
		{ 0, 0, 0, 8, 0 } ,
		{ 0, 0, 0, 0, 3 }
	};

	// global vector to store the visited nodes
	int path[9] = { 0,0,0,0,0,0,0,0,0 };
	int solution = 0;

	void recursion(int node, int depth) {
		int i = 0;
		int x = 0;
		int tmp;

		// add the current node to the path array
		path[depth] = node;

		// search for available pathes from current node vertical until node is reached
		while (i != node) {
			if (mat[i][node] != 0) {
				// save destination node path for returning from recursion
				tmp = mat[i][node];
				// mark identified path as used
				mat[i][node] = 0;
				// goto new node
				recursion(i, depth + 1);
				// restore now unused path after returning from recursion
				mat[i][node] = tmp;
			}
			// move one entry down in matrix
			i++;
		}

		// continue search for available pathes from current node horizontally
		// i can be incremented as previous value of i has already been checked in the while statement
		// and found to be equal to the node. We know that all notes have 0 pathes to themselves and
		// therefore we can move one to the right already ;)
		i++;
		for (; i < 5; i++) {
			if (mat[node][i] != 0) {
				tmp = mat[node][i];
				mat[node][i] = 0;
				recursion(i, depth + 1);
				mat[node][i] = tmp;
			}
		}
		if (depth == 8) {
			printf("\n%i:\t", ++solution);
			for (; x <= 8; x++)
				printf("%i", path[x]);
		}
		return;
	}

	int main(void) {
		int i = 0;

		printf("\nDas Haus vom Nicolaus\n");
		printf("     2\n");
		printf("    /\\ \n");
		printf("  7/  \\8      | 0 1 2 3 4\n");
		printf("  /  6 \\   -- + ----------\n");
		printf(" 1------3   0 | 0 2 0 4 1\n");
		printf(" | \\ 4/ |   1 | 2 0 7 6 5\n");
		printf(" |  \\/  |   2 | 0 7 0 8 0\n");
		printf("2|  /\\  |3  3 | 4 6 8 0 3\n");
		printf(" | / 5\\ |   4 | 1 5 0 3 0\n");
		printf(" 0------4\n");
		printf("    1\n");
		printf("\nLet's start ....\n");

		// only starting point 0,1 and 2 need to be tried. 3 and 4 are symmetric to 0 and 1.
		for (; i < 3; i++) {
			printf("\nStarting point: %i", i);
			recursion(i, 0);
			if (i == 1) solution = 2 * solution;
		}
		printf("\n\nNumber of identified solutions: %i (only solutions for starting point 0,1 and 2 printed due to symmetry)\n", solution);

		return(0);
	}

