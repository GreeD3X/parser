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
    parser.print_poliz();
    parser.print_expr();
}

int main() {
    //test_lexer("tests/test3.txt");
    std::cout << std::endl << "************" << std::endl << std::endl;
    test_parser("tests/test4.txt");
    return 0;
}
