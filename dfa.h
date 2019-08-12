/* dfa.h
   C++ Implementation of Deterministic Finite Automata
   
   Copyright (c) 2018, Michael Pascale
*/

#include <iostream>

using namespace std;

class DFA {
	public:
		DFA(int n);													// Create a DFA with n states.
		void Transition(int state, int input, int next_state);		// Edits an entry in the transition table.
		int Transition(int state, int input);						// Returns the next state given current state and input.
		void Accept(int state, bool accepting);						// Edits the accepting flag of a state.
		bool Accept(int state);										// Returns whether the state is accepting.
		bool Run(int* input_string, int length);					// Run a DFA on a string and return whether it accepts.
	private:
		int start_state;
		int current_state;
		int num_states;
		int* transition_function;
		bool* accept_states;
		// Alphabet is assumed to be just binary {0, 1}.
};
