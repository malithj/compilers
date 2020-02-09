#include <iostream>

#include "NFA.h"


int main(int argc, char **argv)
{
	// Syntax
	if (argc != 2)
	{
		std::cerr << "Syntax: ./nfa-test <string>\n";
		return 1;
	}

	NFA nfa;
	nfa.debug = true;
	nfa.setFinalState(17);
	nfa.addTransition(0, 0, 1);
	nfa.addTransition(0, 0, 2);
	nfa.addTransition(1, '+', 3);
	nfa.addTransition(1, '-', 3);
	nfa.addTransition(2, 0, 4);
	nfa.addTransition(3, 0, 5);
	nfa.addTransition(4, 0, 5);
	for (char c = '0'; c <= '9'; c++)
	  nfa.addTransition(5, c, 6);
	for (char c = '0'; c <= '9'; c++)
	  nfa.addTransition(6, c, 7);
	nfa.addTransition(6, 0, 8);
	nfa.addTransition(7, 0, 6);
	nfa.addTransition(8, 0, 9);
	
	nfa.addTransition(9, 0, 10);
	nfa.addTransition(9, 0, 11);
	nfa.addTransition(11, 0, 12);
	nfa.addTransition(12, 0, 17);
	nfa.addTransition(16, 0, 17);
	nfa.addTransition(10, '.', 13);
	for (char c = '0'; c <= '9'; c++)
	  nfa.addTransition(13, c, 14);
	for (char c = '0'; c <= '9'; c++)
	  nfa.addTransition(14, c, 15);
	nfa.addTransition(14, 0, 16);
	nfa.addTransition(15, 0, 14);

	// Parse string
	bool accepted = nfa.accepts(argv[1]);
	std::cout << "String " << (accepted ? "accepted" : "rejected") << "\n";
	return 0;
}

