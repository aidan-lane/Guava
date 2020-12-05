#include <iostream>
#include "lexer.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "Invalid arguments, must be [filename]" << endl;
        return EXIT_FAILURE;
    }

    Lexer lexer;
    lexer.lex(argv[1]);

    return EXIT_SUCCESS;
}