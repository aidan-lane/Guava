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
    lineno = 1;
    colno = 0;
    for (uint_fast32_t i = 0; i < mmap.size(); i++) {
        colno++;

        // skip whitespace
        if (mmap[i] == ' ') continue;
        if (mmap[i] == '\n') { lineno++; continue; }

        // numbers
        if (isdigit(mmap[i])) {
            while (isdigit(mmap[i])) { buffer += mmap[i]; i++; }
            if (mmap[i] == '.') {
                buffer += mmap[i]; i++;
                while (isdigit(mmap[i])) { buffer += mmap[i]; i++; }
            }

            tokens.push_back(Token(Number, stod(buffer)));
            buffer.clear();
            i--;
        }
        else if (isalpha(mmap[i])) { // names
            while (isalnum(mmap[i])) { buffer += mmap[i]; i++; }

            tokens.push_back(Token(Name, 0, buffer));
            buffer.clear();
            i--;
        }
        else if (mmap[i] == '\"') { // strings
            i++;
            while (mmap[i] != '\"') { buffer += mmap[i]; i++; }

            tokens.push_back(Token(String, 0, buffer));
            buffer.clear();
        }
        else {
            switch (mmap[i]) {
            case '+': tokens.push_back(Token(Plus, 0)); break;
            case '-': tokens.push_back(Token(Minus, 0)); break;
            case '*': tokens.push_back(Token(Mul, 0)); break;
            case '/': tokens.push_back(Token(Div, 0)); break;
            case '(': tokens.push_back(Token(OParen, 0)); break;
            case ')': tokens.push_back(Token(CParen, 0)); break;
            default: // error
                cerr << "Invalid character " << mmap[i] << " at " << lineno << ":" << colno << endl;
                exit(-1);
                break;
            }
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