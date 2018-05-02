#ifndef PARSER
#define PARSER

#include "lexer.hpp"
#include <stack>
#include <vector>

class Parser {
    
    Lex_seq_input_iterator cur_pos;
    Lex cur_lex;
    type_of_lex cur_type;
    std::stack<Type> st_type;
    std::vector<Lex> poliz;
    void get_lex ();
    void S ();
    void Expr ();
    void Add_expr ();
    void Add_expr1 ();
    void Mult_expr ();
    void Mult_expr1 ();
    void Index ();
    void check ();
    void check_op ();
  public :
    Parser (Lex_seq &lex_seq) : cur_pos(lex_seq.begin()) {}
    void parse ();
    void print_poliz ();
    void print_expr ();

};

class Syntax_exception : public Exception {
   
  public :
    Syntax_exception (const std::string &what, const int str_num, const int char_num) : Exception(what, str_num, char_num) { this->what = "SYNTAX:" + what; }

};

class Semantic_exception : public Exception {
   
  public :
    Semantic_exception (const std::string &what, const int str_num, const int char_num) : Exception(what, str_num, char_num) { this->what = "SENANTICS:" + what; }

};

#endif
