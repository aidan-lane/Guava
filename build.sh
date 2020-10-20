#!/bin/bash
bison -o parser.cpp parser.y
flex -o scanner.cpp scanner.l
g++ -o scanner.out scanner.cpp -lfl