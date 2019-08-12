/* tm.c
   Simple turing machine implementation in C.
   
   Copyright (c) 2018, Michael Pascale
*/
 
#include <stdio.h>
#include <stdlib.h>

#define NUMSTATE 10
#define NUMACEPT 1
#define NUMGAMMA 3	// Gamma includes blank character.
#define NUMSIGMA 2
#define LEN_TAPE 100

 
struct turing_machine {
	 
	// Q: Set of States
	char Q[NUMSTATE];
	 
	// Γ: Alphabet
	int gamma[NUMGAMMA];
	
	// Σ: Input Set
	char sigma[NUMSIGMA];
	
	// q0: Initial State
	int q0;
	
	// F: Accepting States
	int F[NUMACEPT];
	
	// δ: Transition Table
	int delta[NUMSTATE][NUMGAMMA*3];
	
	// Turing Machine Tape, Initial State
	char tape[LEN_TAPE];
	
	
	// index just keeps track of our current position on the tape.
	int index;
	// state just keeps track of our current state
	// state is an index of Q which holds the state names.
	int state;
	
} tm;

struct turing_machine tm = {
	// Double check size definitions before adding additional elements.
	
	// Q
	/* 0    1    2    4    4    5    6	  7    8    9		*/
	{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},	// state is just a number, but we'll give them names...
	
	// Γ
	{ '_', '0', '1' },
	
	// Σ
	{ '0', '1' },
	
	// q0
	0,									// 0 corresponding to state 'a'
	
	// F
	{9},								// State 9 is our only accept state
	
	// δ			delta[state][action] 		NUMSTATE x NUMGAMMA*3 array
	
		/*	i		j	0		1		2		3		4		5				*/
	{	/*	state		on _	move	next	on 0	move	next	on 1	move	next	*/
		/*	a 0	*/	{	'_',	'l',	5,		'_',	'l',	1,		'1',	'l',	3		},
		/*	b 1	*/	{	0,		0,		0,		'0',	'l',	1,		'1',	'l',	2		},
		/*	c 2	*/	{	0,		0,		0,		'0',	'l',	2,		'1',	'l',	3		},
		/*	d 3	*/	{	0,		0,		0,		'0',	'l',	3,		'0',	'r',	4		},
		/*	e 4	*/	{	'_',	'l',	0,		'0',	'r',	4,		'1',	'r',	4		},
		/*	f 5	*/	{	'_',	'l',	6,		'_',	'l',	2,		'1',	'l',	6		},
		/*	g 6	*/	{	'_',	'l',	0,		'0',	'r',	4,		'1',	'r',	4		},
		/*	h 7	*/	{	'_',	'l',	6,		'_',	'l',	2,		'1',	'l',	6		},
		/*	i 8	*/	{	'_',	'l',	6,		'_',	'l',	2,		'1',	'l',	6		},
		/*	j 9	*/	{	0,		0,		0,		0,		0,		0,		0,		0,		0		}
	},
	
	// tape
	{	/*   1    2    3    4    5    6    7    8    9    10  */	
			'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
			'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
			'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
			'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
			'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
			'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
			'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
			'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
			'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
			'1', '1', '1', '0', '0', '0', '0', '1', '0', '0'
			/*				4			 		+	 2		*/
	},
	
	// index
	LEN_TAPE - 1,
	
	// state	(starts at q0)
	0
};


/* Unary Addition
 * starting a right end of tape
 * state
 * 
 * See a digit
 * 0		see a 0, write _, move left, goto 1			see a _, write _, move left, goto 6		see a 1, goto 5
 * 1		see a 0, write 0, move left, goto 1			see a 1, write 1, move left, goto 2
 * 2		see a 0, write 0, move left, goto 2			see a 1, write 1, move left, goto 3
 * 
 * Write a digit
 * 3		see a 0, write 0, move left, goto 3			see a 1, write 0, move right, goto 4
 * 
 * Reset
 * 4		see a 0, write 0, move right, goto 4		see a 1, write 1, move right, goto 4		see a _, write _, move left, goto 0
 * 
 * 
 * 
 * We've completed the first number and so don't need to look for the second 1...
 * 5		see a 0, write _, move left, goto 2			see a _, write _, move left, goto 6		see a 1, write 1, move left, goto 6
 * 6		see a 0, write 0, move left, goto 2			see a 1, write 1, move left, goto 3
 * 
 * Write a digit
 * 7		see a 0, write 0, move left, goto 3			see a 1, write 0, move right, goto 8
 * 
 * Reset...
 * 8		see a 0, write 0, move right, goto 8		see a 1, write a 1, goto 9			see a _ write a _, move left, goto 5
 * 
 * HALT
 * 9	Accept state.
 * 
 * original tape	11111111111110000100
 * 
 * after tape		1111110000001____1__
 * */


// Print the contents of tm.tape.
void print_tape() {
	for (int i = 0; i < LEN_TAPE; i++)
		printf("%c", tm.tape[i]);
	printf("\n");
	return;
}

// Returns 1 if x is in array.
int isIn(int* array, int size, int x) {
	for (int i = 0; i < size; i++) {
		if (array[i] == x)
			return 1;
	}
	return 0;
}

// Returns the index of x if it is in array.
int lookup(int* array, int size, int x) {
	for (int i = 0; i < size; i++) {
		if (array[i] == x)
			return i;
	}
	return -1;
}

// Returns 1 if the current state is in F.
int Accept() {
	return isIn(tm.F, NUMACEPT, tm.state);
}

void Transition() {
	
	// Get the current char on the tape.
	char c = tm.tape[tm.index];
	
	// The transition table format is delta[state][action].
	// Figure out what part of the table we're looking at based on the state and current character.
	int action = 3 * lookup(tm.gamma, NUMGAMMA, c);
	
	// Use delta to determine what will be written, where we will move, 
	char character_to_write = tm.delta[tm.state][action];
	char direction_to_move  = tm.delta[tm.state][action+1];
	int state_to_goto 		= tm.delta[tm.state][action+2];
	
	// Write
	tm.tape[tm.index] = character_to_write;
	
	// Move
	if (direction_to_move == 'r')
		tm.index++;
	else 
		tm.index--;
		
	// Change State
	tm.state = state_to_goto;
	
	return;
}


int main (int argc, char** argv) {
	print_tape();
	
	// Run the Turing Machine
	while (!Accept())
		Transition();
		
	print_tape();
	
	return 0;
}
