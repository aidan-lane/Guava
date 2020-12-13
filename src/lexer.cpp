#include "lexer.h"

int Lexer::handle_error(const error_code& error) 
{
    const auto& errmsg = error.message();
    cout << "Error mapping file: " << errmsg << ", exiting..." << endl;
    return error.value();
}

list<Token>* Lexer::lex(const string& path)
{
    error_code error;
    mio::mmap_source mmap;
    mmap.map(path, error);
    if (error) { handle_error(error); }

    // read
    string buffer;
    for (uint_fast32_t i = 0; i < mmap.size(); i++) {
        // skip whitespace
        if (mmap[i] == ' ') continue;

        // parse number
        if (isdigit(mmap[i])) {
            while (isdigit(mmap[i])) { buffer += mmap[i]; i++; }
            if (mmap[i] == '.') {
                buffer += mmap[i]; i++;
                while (isdigit(mmap[i])) { buffer += mmap[i]; i++; }
            }

            tokens.push_back(Token(Number, stod(buffer)));
            buffer.clear();
        }

        switch (mmap[i]) {
            case '+': tokens.push_back(Token(Plus, 0)); break;
            case '-': tokens.push_back(Token(Minus, 0)); break;
            case '*': tokens.push_back(Token(Mul, 0)); break;
            case '/': tokens.push_back(Token(Div, 0)); break;
            case '(': tokens.push_back(Token(OParen, 0)); break;
            case ')': tokens.push_back(Token(CParen, 0)); break;
            default: break; // error
        }
    }

    // cleanup
    mmap.unmap();

    return &tokens;
}

void Lexer::print_tokens()
{
    for (auto& tok : tokens) {
        tok.print();
    }
}