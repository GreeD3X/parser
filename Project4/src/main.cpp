#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"

int main() {
    {
        Scaner scaner("tests/test0.txt");
        Lex_seq seq(scaner);
        for (const auto &x : seq) {
            std::cout << x << std::endl;
        }
    }
    {
        Scaner scaner("tests/test3.txt");
        Lex_seq seq(scaner);
        Parser parser(seq, &scaner.TID);
        parser.parse();
    }
    return 0;
}
