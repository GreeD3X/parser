#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"

int main() {
    Scaner scaner("tests/test3.txt");
    /*do {
        auto x = scaner.get_lex();
        std::cout << x << std::endl;
        if (x.get_type() == LEX_FIN) {
            break;
        }
    } while (true);*/
    Lex_seq seq(scaner);
    /*std::cout << *(++seq.begin()) << std::endl;
    for (const auto &x : seq) {
        std::cout << x << std::endl;
    };
    scaner.print_TID();*/
    Parser parser(seq, &scaner.TID);
    parser.parse();
    return 0;
}
