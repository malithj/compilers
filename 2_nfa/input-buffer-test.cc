#include <iostream>
#include <fstream>

#include "InputBuffer.h"
#include "NFA.h"

const int TokenSpace = 1;
const int TokenReturn = 2;
const int TokenIf = 3;
const int TokenId = 4;
const int TokenNumber = 5;
const int TokenAssign = 6;
const int TokenOpEqual = 7;
const int TokenOpenPar = 8;
const int TokenClosePar = 9;
const int TokenSemicolon = 10;

int main()
{
	NFA nfa;

	// Final states
	nfa.setFinalState(27, TokenSpace);
	nfa.setFinalState(25, TokenId);
	nfa.setFinalState(23, TokenNumber);
	nfa.setFinalState(21, TokenSemicolon);
	nfa.setFinalState(19, TokenClosePar);
	nfa.setFinalState(17, TokenOpenPar);
	nfa.setFinalState(15, TokenOpEqual);
	nfa.setFinalState(12, TokenAssign);
	nfa.setFinalState(10, TokenIf);
	nfa.setFinalState(7, TokenReturn);

	// Transitions from states 0, 1, 2
	nfa.addTransition(0, 0, 1);
	nfa.addTransition(0, 0, 8);
	nfa.addTransition(0, 0, 11);
	nfa.addTransition(0, 0, 13);
	nfa.addTransition(0, 0, 16);
	nfa.addTransition(0, 0, 18);
	nfa.addTransition(0, 0, 20);
	nfa.addTransition(0, 0, 22);
	nfa.addTransition(0, 0, 26);
	nfa.addTransition(0, 0, 24);
	nfa.addTransition(1, 'r', 2);
	nfa.addTransition(2, 'e', 3);
	nfa.addTransition(3, 't', 4);
	nfa.addTransition(4, 'u', 5);
	nfa.addTransition(5, 'r', 6);
	nfa.addTransition(6, 'n', 7);

	nfa.addTransition(8, 'i', 9);
	nfa.addTransition(9, 'f', 10);
	
	
	nfa.addTransition(11, '=', 12);

	nfa.addTransition(13, '=', 14);
	nfa.addTransition(14, '=', 15);

	nfa.addTransition(16, '(', 17);
	nfa.addTransition(18, ')', 19);
	
	nfa.addTransition(20, ';', 21);
	for (char c = '0'; c <= '9'; c ++)
		nfa.addTransition(22, c, 23);

	nfa.addTransition(26, '\n', 27);
	nfa.addTransition(26, ' ', 27);
	nfa.addTransition(26, '\t', 27);


	nfa.addTransition(24, '_', 25);
	nfa.addTransition(25, '_', 25);
	for (char c = 'a'; c <= 'z'; c ++)
		nfa.addTransition(24, c, 25);
	for (char c = 'A'; c <= 'Z'; c ++)
		nfa.addTransition(24, c, 25);
	for (char c = 'a'; c <= 'z'; c ++)
		nfa.addTransition(25, c, 25);
	for (char c = 'A'; c <= 'Z'; c ++)
		nfa.addTransition(25, c, 25);
	for (char c = '0'; c <= '9'; c ++)
		nfa.addTransition(25, c, 25);
	
        std::ifstream f("input.txt");
	
	// Create input buffer
	InputBuffer input_buffer(f);
	while (true)
	{
		std::pair<int, std::string> pair = input_buffer.getToken(nfa);

		// No more tokens
		if (!pair.first)
			break;

		// Token found
		std::cout << "Token " << pair.first << ": '"
				<< pair.second << "'\n";
	}

	// Done
	return 0;
}

