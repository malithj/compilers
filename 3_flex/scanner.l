%{
#include <fstream>
using namespace std;
%}

%option noyywrap
%option c++

DIGIT [0-9]
LETTER_ [a-zA-Z_]

%%

[ \n\t]+ {
	std::cout << "Token SPACE: '" << yytext << "'\n";
}

{DIGIT}+ {
	std::cout << "Token NUMBER: '" << yytext << "'\n";
}

int {
	std::cout << "Token INT: '" << yytext << "'\n";
}

float {
        std::cout << "Token FLOAT: '" << yytext << "'\n";
}

\"[^\"]*\" {
	std::cout << "Token STRING: '" << yytext << "'\n";
}

(\/\/[^\n]*)|(\/\*[^\*\/]*\*\/) {
	std::cout << "Token COMMENT: '" << yytext << "'\n";
}

{LETTER_}({LETTER_}|{DIGIT})* {
	std::cout << "Token ID: '" << yytext << "'\n";
}

&{LETTER_}({LETTER_}|{DIGIT})* {
	std::cout << "Token ADDRESS: '" << yytext << "'\n";
}

\= {
	std::cout << "Token ASSIGN: '" << yytext << "'\n";
}

\( {
	std::cout << "Token OPEN_BR: '" << yytext << "'\n";
}

\) {
	std::cout << "Token CLOSE_BR: '" << yytext << "'\n";
}

\{ { 
	std::cout << "Token OPEN_PR: '" << yytext << "'\n";
}

\} {
	std::cout << "Token CLOSE_PR: '" << yytext << "'\n";
}

\, {
	std::cout << "Token COMMA: '" << yytext << "'\n";
}

\; {
	std::cout << "Token SEMICOLON: '" << yytext << "'\n";
}

. {
	std::cout << "Token ERROR: '" << yytext << "'\n";
}

%%

int main(int argc, char **argv)
{
	std::ifstream f("code.c");
	yyFlexLexer lexer(&f);
	lexer.yylex();
	return 0;
}

