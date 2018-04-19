#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"

void test_lexer (const std::string &name)
{
    Scaner scaner(name);
    Lex_seq seq(scaner);
    for (const auto &x : seq) {
        std::cout << x << std::endl;
    }
}

void test_parser (const std::string &name)
{
    Scaner scaner(name);
    Lex_seq seq(scaner);
    Parser parser(seq);
    parser.parse();
}

int main() {
    test_lexer("tests/test0.txt");
    test_parser("tests/test3.txt");
    return 0;
}
