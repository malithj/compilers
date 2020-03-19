%{

#include <iostream>
#include <cstdio>
#include <cstring>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE * yyin;
 
void yyerror(const char *s);

llvm::Module *module;

%}

%token<name> TokenId
%token TokenOpenPar
%token TokenClosePar
%token TokenSemicolon
%token TokenComma
%token TokenFloat
%token TokenInt
%token TokenVoid

%type<types> A
%type<types> B
%type<type> Type

%union {
	char *name;
	llvm::Type *type;
	std::vector<llvm::Type *> *types;
}

%%
Function:
	Type TokenId TokenOpenPar A TokenClosePar TokenSemicolon
	{
		llvm::FunctionType *type = llvm::FunctionType::get($1, *$4, false);
		module->getOrInsertFunction($2, type);
	}
A:
	{
		$$ = new std::vector<llvm::Type *>();
	} | B Type TokenId 
	{
		$$ = $1;
		$$->push_back($2);	
	
	}

B:
 	{
		$$ = new std::vector<llvm::Type *>();
	} | B Type TokenId TokenComma 
	{
		$$ = $1;
		$$->push_back($2);	
	}

Type:
	TokenInt
	{
		$$ = llvm::Type::getInt32Ty(llvm::getGlobalContext());
	}
	| TokenFloat
	{
		$$ = llvm::Type::getFloatTy(llvm::getGlobalContext());
	}
	| TokenVoid
	{
		$$ = llvm::Type::getVoidTy(llvm::getGlobalContext());
	}	

%%

int main(int argc, char **argv)
{
	// Syntax
	if (argc != 2)
	{
		std::cerr << "Syntax: ./main <file>\n";
		exit(1);
	}
	// Open file in 'yyin'
	yyin = fopen(argv[1], "r");
	if (!yyin)
	{
		std::cerr << "Cannot open file\n";
		exit(1);
	}

	// Context, module
	llvm::LLVMContext &context = llvm::getGlobalContext();
	module = new llvm::Module("TestModule", context);

	// Parse input until there is no more
	do
	{
		yyparse();
	} while (!feof(yyin));
	
	// Dump module
	module->dump();
	return 0;
}

void yyerror(const char *s)
{
	std::cerr << s << std::endl;
	exit(1);
}

