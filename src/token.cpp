#include "token.h"

void Token::print()
{
    cout << "{\n  Type: " << type 
        << "\n  Value: " << val
        << "\n  Symbol: " << (symbol.length() == 0 ? "None" : symbol) << "\n}" 
        << endl;
}