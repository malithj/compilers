all: scanner

flex: scanner.l
	flex++ -o scanner.cc scanner.l

scanner: flex
	g++ -Wall scanner.cc -o scanner

.PHONY: clean

clean: 
	rm -rf scanner.cc scanner
