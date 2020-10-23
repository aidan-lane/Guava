all: parser.cpp scanner.cpp scanner.out

parser.cpp: parser.y
	bison -o parser.cpp parser.y

scanner.cpp: scanner.l
	flex -o scanner.cpp scanner.l

scanner.out: ast.cpp scanner.cpp
	g++ -o scanner.out ast.cpp scanner.cpp -lfl