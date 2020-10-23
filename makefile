all: parser scanner compiler

parser: parser.y
	bison -o parser.cpp parser.y

scanner: scanner.l
	flex -o scanner.cpp scanner.l

compiler: scanner.cpp
	g++ -o scanner.out scanner.cpp -lfl
