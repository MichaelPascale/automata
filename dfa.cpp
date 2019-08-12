/* dfa.cpp
   C++ Implementation of Deterministic Finite Automata
   
   Copyright (c) 2018, Michael Pascale
*/

#include "dfa.h"

DFA::DFA(int n) {
	start_state = 0;
	current_state = start_state;
	num_states = n;									// Set the number of states
	accept_states = new bool [num_states];			// Array holds flags for each accept state.
	transition_function = new int [num_states*2];	// Our transition function has options for input of 0 or 1. 
}

void DFA::Transition(int state, int input, int next_state){
	transition_function[state*2+input] = next_state;
}

int DFA::Transition(int state, int input) {
	int next_state = transition_function[state*2+input];
	cout << "From state " << state << " with input " << input << " the next state is " << next_state << endl;
	return next_state;
}

void DFA::Accept(int state, bool accepting) {
	accept_states[state] = accepting;
}

bool DFA::Accept(int state) {
	//cout << "State " << state << (accept_states[state]?" is accepting.":" is not an accept state.") << endl;
	return accept_states[state];
}

bool DFA::Run(int* input_string, int length) {
	current_state = start_state;
	
	for (int i = 0; i < length; i++) {
		current_state = Transition(current_state, input_string[i]);
	}
	
	cout << "END: The string runs to state " << current_state << endl;
	if (Accept(current_state)) cout << "The string is accepted." << endl;
	else cout << "The string is NOT accepted." << endl;
	
	return Accept(current_state);
}
