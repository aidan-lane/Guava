#!/bin/bash
bison -o parser.c parser.y
flex -o scanner.c scanner.l
g++ -o scanner.out scanner.c -lfl -w