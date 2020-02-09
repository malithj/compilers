all: nfa-test input-buffer-test

nfa-test: nfa-test.cc NFA.cc NFA.h
	g++ -Wall NFA.cc nfa-test.cc -o nfa-test -std=c++11 

input-buffer-test: input-buffer-test.cc InputBuffer.cc InputBuffer.h NFA.cc NFA.h
	g++ -Wall NFA.cc InputBuffer.cc input-buffer-test.cc -o input-buffer-test -std=c++11

.PHONY: clean

clean: 
	rm -rf nfa-test input-buffer-test
