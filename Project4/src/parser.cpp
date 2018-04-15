#include "parser.hpp"

void Parser::get_lex () 
{
    ++cur_pos;
    cur_lex = *cur_pos;
    //std::cout << cur_lex << std::endl;
    cur_type = cur_lex.get_type();
}   

void Parser::parse ()
{
    get_lex();
    S();
    std::cout << "SUCESS" << std::endl;
}

void Parser::S ()
{
    while (cur_type != LEX_FIN) {
        //std::cout << cur_lex << std::endl;
        Expr();
    }
}

void Parser::Expr ()
{
    //std::cout << cur_lex << std::endl;
    Add_expr();
    //get_lex();
    //std::cout << cur_lex  << " RPAREN"<< std::endl;
    Add_expr1();
}

void Parser::Add_expr1 ()
{
    if (cur_type == LEX_PLUS) {
        get_lex();
        //std::cout << cur_lex << std::endl;
        Expr();
    }
}

void Parser::Add_expr ()
{
    Mult_expr();
    Mult_expr1();
}

void Parser::Mult_expr1 ()
{
    if (cur_type == LEX_TIMES) {
        get_lex();
        Expr();
    }
}

void Parser::Mult_expr ()
{
    switch (cur_type) {
        case LEX_ID : 
            Id();
            break;
        case LEX_NUM : 
            get_lex();
            break;
        case LEX_LPAREN :
            get_lex();
            //std::cout << cur_lex << std::endl;
            Expr();
            if (cur_type != LEX_RPAREN) {
                throw std::runtime_error("NO RIGHT PAREN");
            }
            //std::cout << cur_lex << std::endl;
            get_lex();
            break;
        default :
            throw std::runtime_error("WRONG LEXEM");
    }
}

void Parser::Id ()
{
    get_lex();
    Id1();
}

void Parser::Id1 ()
{
    //std::cout << cur_lex << std::endl;
    if (cur_type == LEX_LSQPAR) {
        get_lex();
        Expr();
        if (cur_type != LEX_RSQPAR) {
            throw std::runtime_error("NO RIGHT SQUARE PAREN");
        }
        get_lex();
    }
}
