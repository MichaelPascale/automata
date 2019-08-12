/* dfa_driver.cpp
   C++ Implementation of Deterministic Finite Automata
   
   Copyright (c) 2018, Michael Pascale
*/

#include <iostream>
#include <string>
#include "dfa.h"

using namespace std;
int main(){
	
	int start_state, num_states;
	int next_state, accepting;
	int* input_string;
	int input_length;
	int next_char;
	string transition_function;
	
	cout << "Deterministic Finite Automata C++ Class" << endl << " By Michael Pascale, Fall 2018" << endl << endl;
	
	
	cout << "Please enter the number of states in this DFA: ";
	cin >> num_states;
	
	cout << "This DFA will have " << num_states << " states." << endl << "The following table represents the state transition function. Please complete the appropriate fields:" << endl;
	
	DFA dfa(num_states); 
	cout << "\t State \t Input \t Next State" << endl;
	
	cout << "START: " << endl;
	for (int i=0; i < num_states; i++) {
		cout << "Accept s" << i << "? ";
		cin >> accepting;
		dfa.Accept(i, accepting);
		
		cout << endl << "\ts" << i << "\t 0 \t ";
		cin >> next_state;
		dfa.Transition(i, 0, next_state);
		
		cout << "\ts" << i << "\t 1 \t ";
		cin >> next_state;
		dfa.Transition(i, 1, next_state);
		
		cout << endl;
	}
	
	while (1) {
		cout << "How long will your input string be? ";
		cin >> input_length;
		
		input_string = new int [input_length];
		
		for (int i = 0; i < input_length; i++) {
			cout << "Character " << i << ": ";
			cin >> next_char;
			cout << endl;
			
			input_string [i] = next_char;
		}
		
		dfa.Run(input_string, input_length);
		
		delete[] input_string;
	}
	
	return 0;
}
