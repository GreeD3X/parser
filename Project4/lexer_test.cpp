#include <iostream>
#include "lexer.hpp"

int main() {
    Scaner scaner("tests/test0.txt");
    Lex_seq seq(scaner);
    for (const auto &x : seq) {
        std::cout << x << std::endl;
    }
}
