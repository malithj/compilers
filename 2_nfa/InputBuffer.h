#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H

#include <iostream>
#include "NFA.h"


class InputBuffer
{
	// Buffer size and maximum lexeme size
	static const int BufferSize = 128;

	// Input stream
	std::istream *stream;

	// Buffer for input stream
	std::string buffer;

	// Pointers in input buffer
	int lexeme_begin = 0;
	int forward = 0;

public:

	/// Constructor
	InputBuffer(std::istream &stream) : stream(&stream)
	{
	}

	/// Return the next character in the input buffer, and advance the
	/// internal 'forward' pointer. If there are no more characters to read
	/// from the input, return 0.
	char nextChar();

	/// Extract a lexeme with the given length, starting at the 'lexeme_begin'
	/// pointer. The given length should not exceed the number of characters
	/// discovered so far with calls to nextChar().
	///
	/// The lexical analysis is restarted at the character following the end
	/// of the extracted lexeme. This means that 'lexeme_begin' is advanced
	/// to point to the beginning of the next lexeme, and 'forward' is
	/// rewound to point to the same location.
	///
	std::string getLexeme(int length);

	/// Return the next token found in the input as identified by the NFA
	/// passed in the first argument. The token is given as a pair token ID
	/// and the associated text.
	///
	/// If there are no more symbols to read from the input, the returned
	/// token ID is 0. If the next token in the input is unrecognizable,
	/// the returned token ID is -1.
	///
	std::pair<int, std::string> getToken(NFA &nfa);
};

#endif

