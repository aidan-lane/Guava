#include "token.h"

void Token::print()
{
    cout << "{\n  Type: " << type << "\n  Value: " << val << "\n}," << endl;
}