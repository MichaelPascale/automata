/* nfa.cpp
   C++ Implementation of Non-Deterministic Finite Automata
   
   Copyright (c) 2018, Michael Pascale
*/

#include "nfa.h"

	int start_state;
		bool* current_state;										// Since NFA's can have simultaneous states, this flags current states.
		int num_states;
		int* transition_function;									// Transition Function will also include epsilon transitions.
		bool* accept_states;
		int** epsilon_transitions;

NFA::NFA(int n) {
	start_state = 0;								// Start at 0 for simplicity.
	num_states = n;									// Set the number of states
	current_state = new bool [num_states];			// We've got a flag to tell whether a state is running or not.
	current_state[start_state] = true;
	accept_states = new bool [num_states];			// Array holds flags for each accept state.
	transition_function = new int [num_states*2];	// Our transition function has options for input of 0 or 1. 
	epsilon_transitions = new bool* [num_states];	// Each state has a list of epsilon transtions associated with it.
	for (int i =0; i < num_states; i++)
		epsilon_transitions[i] = new bool [num_states];	// Soo leaky! "I'll add deletes later".
}

void NFA::Transition(int state, int input, int next_state){
	transition_function[state*2+input] = next_state;
}

int NFA::Transition(int state, int input) {
	int next_state = transition_function[state*2+input];
	cout << "From state " << state << " with input " << input << " the next state is " << next_state << endl;
	return next_state;
}

void NFA::Accept(int state, bool accepting) {
	accept_states[state] = accepting;
}

bool NFA::Accept(int state) {
	//cout << "State " << state << (accept_states[state]?" is accepting.":" is not an accept state.") << endl;
	return accept_states[state];
}

bool NFA::Run(int* input_string, int length) {
	// State 0 is the only active state.
	for (int i = 0; i < num_states; i++) {
		Active(i, false);
	}
	Active(0, true);
	
	// To avoid collisions with next states and current states disabling each other, we need a second array of current states.
	bool* active_state = new bool [num_states];
	copy(current_state, current_state+num_states, active_state);
	
	// For each input symbol...
	for (int i = 0; i < length; i++) {
		
		// Check what states are running...
		for (int state = 0; state < num_states; state++)
			if (active_state[state]) { 								// If state is active...		// WHAT IF A STATE BEGINS WITH EPSILON? CAN'T DEACTIVATE.
				Active(state, false);								// Deactivate the state.
				Active(Transition(state, input_string[i]), true);	// Activate the next state.
				Epsilon(state);										// Activate any epsilon transitions from the state.
			}
	}
	
	delete [] active_state;
	
	for (int i = 0; i < num_states; i++)
		if (Active(i) && Accept(i)) return true;		// If a current state is active and accepting, the string is accepted.
	
	return false;
}

void NFA::Epsilon(int state, int next_state) {
	epsilon_transitions[state][next_state] = true;
}

void NFA::Epsilon(int state) {
	for (int next_state = 0; next_state < num_states; next_state++)
		if (epsilon_transitions[state][next_state]) Active(next_state, true);	// if there is an epsilon transition to next_state, activate next_state.
}



void NFA::Active(int state, bool active) {
	current_state[state] = active;
}

bool NFA::Active(int state) {
	return current_state[state];
}
