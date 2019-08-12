/* nfa.h
   C++ Implementation of Non-Deterministic Finite Automata
   
   Copyright (c) 2018, Michael Pascale
*/

#include <iostream>

using namespace std;

class NFA {
	public:
		NFA(int n);													// Create an NFA.
		void Transition(int state, int input, int next_state);		// Edits an entry in the transition table.
		int Transition(int state, int input);						// Returns the next state given current state and input.
		void Epsilon(int state, int next_state);					// Edits the implicit epsilon transitions of a state.
		void Epsilon(int state);									// Activate the epsilon transitions from a state.
		void Active(int state, bool active);						// Make a state current or not current.
		bool Active(int state);										// Return whether a state is running.
		void Accept(int state, bool accepting);						// Edits the accepting flag of a state.
		bool Accept(int state);										// Returns whether the state is accepting.
		bool Run(int* input_string, int length);					// Run a NFA on a string and return whether it accepts.
		
	private:
		int start_state;
		bool* current_state;										// Current running states are represented as a list of flags.
		int num_states;
		int* transition_function;									// Transition Function will also include epsilon transitions.
		bool* accept_states;
		bool** epsilon_transitions;									// A 2d array holds the epsilon transitions.

		// Alphabet is assumed to be just binary {0, 1}.
};
