all: scanner

parser: parser.y
	bison -oparser.c parser.y -d -v

flex: scanner.l parser
	flex -o scanner.c scanner.l

scanner: flex
	g++ parser.c scanner.c -o parser `llvm-config --cppflags` `llvm-config --ldflags` -lLTO -std=c++11

.PHONY: clean

clean: 
	rm -rf scanner.c parser.c parser.h parser.output parser
