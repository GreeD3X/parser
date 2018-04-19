#include "parser.hpp"

void Parser::get_lex () 
{
    ++cur_pos;
    cur_lex = *cur_pos;
    //std::cout << cur_lex << std::endl;
    cur_type = cur_lex.get_lex_type();
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
        check_op();
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
        check_op();
    }
}

void Parser::Mult_expr ()
{
    switch (cur_type) {
        case LEX_ID : 
            check();
            st_type.push(cur_lex.get_type());
            //std::cout << cur_lex.get_type() << std::endl;
            get_lex();
            Id();
            break;
        case LEX_NUM : 
            st_type.push(Type(TYPE_INT, 0));
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
    //std::cout << cur_lex << std::endl;
    if (cur_type == LEX_LSQPAR) {
        Type tmp = st_type.top();
        st_type.pop();
        --tmp.arr_dim;
        if (tmp.arr_dim < 0) {
            throw std::runtime_error("INDEX APPEAL ERROR");
        }
        st_type.push(tmp);
        get_lex();
        Expr();
        //std::cout << "<" << st_type.top() << ">" << std::endl;
        if (st_type.top() != Type(TYPE_INT, 0)) {
            throw std::runtime_error("INDEX IS NOT INTEGER");
        }
        st_type.pop();
        if (cur_type != LEX_RSQPAR) {
            throw std::runtime_error("NO RIGHT SQUARE PAREN");
        }
        get_lex();
        Id();
    }
}

void Parser::check ()
{
    std::string name = cur_lex.get_name();
    char letter = 0;
    int cnt = -1;
    for (auto c : name) {
        //std::cout << '|' << c << "|\n";
        if (c != 'i' && c != 'j' && c != 'k' && c != 's' && c != 't' && c != 'a') {
            throw std::runtime_error("WRONG ID");
        } else {
            ++cnt;
            letter = c;
        }
    }
    if (letter == 'i' || letter == 'j' || letter == 'k') {
        cur_lex.set_type(Type(TYPE_INT, cnt));
    } else {
        if (letter == 's' || letter == 't') {
                cur_lex.set_type(Type(TYPE_STRING, cnt));
        } else { 
                throw std::runtime_error("WRONG ID");
        }
    }
}

void Parser::check_op ()
{
    Type type1, type2;
    type2 = st_type.top();
    st_type.pop();
    type1 = st_type.top();
    //std::cout << type1 << " " << type2 << std::endl;
    st_type.pop();
    if (type1 == Type(TYPE_INT, 0) && type2 == Type(TYPE_INT, 0)) {
        st_type.push(Type(TYPE_INT, 0));
    } else {
        throw std::runtime_error("WRONG TYPES");
    }
}
