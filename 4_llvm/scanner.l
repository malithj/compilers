%{
#include <iostream>
#include <vector>
#include <cstring>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include "parser.h"
#define YY_DECL extern "C" int yylex()
using namespace std;
%}

%option noyywrap

DIGIT [0-9]
LETTER_ [a-zA-Z_]

%%

void {
	return TokenVoid;
}

int {
	return TokenInt;
}

float {
        return TokenFloat;
}


{LETTER_}[{LETTER_}{DIGIT}]* {
	yylval.name = strdup(yytext);
	return TokenId;
}

\( { 
	return TokenOpenPar;
}

\) {
	return TokenClosePar;
}

\, {
	return TokenComma;
}

\; {
	return TokenSemicolon;
}

[ \n\t]+ {
	// ignore whitespaces
}

. {
	std::cout << "Token ERROR\n";
}

%%

