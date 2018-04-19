#ifndef PARSER
#define PARSER

#include "lexer.hpp"
#include <stack>

class Parser {
    
    Lex_seq_input_iterator cur_pos;
    Lex cur_lex;
    type_of_lex cur_type;
    std::stack<Type> st_type;
    void get_lex ();
    void S ();
    void Expr ();
    void Add_expr ();
    void Add_expr1 ();
    void Mult_expr ();
    void Mult_expr1 ();
    void Id ();
    void check ();
    void check_op ();
  public :
    Parser (Lex_seq &lex_seq) : cur_pos(lex_seq.begin()) {}
    void parse ();

};

#endif
