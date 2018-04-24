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
        Add_expr();
        check_op();
        poliz.push_back(Lex(LEX_PLUS));
        Add_expr1();
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
        Mult_expr();
        check_op();
        poliz.push_back(Lex(LEX_TIMES));
        Mult_expr1();
    }
}

void Parser::Mult_expr ()
{
    switch (cur_type) {
        case LEX_ID : 
            check();
            st_type.push(cur_lex.get_type());
            poliz.push_back(cur_lex);
            //std::cout << cur_lex.get_type() << std::endl;
            get_lex();
            Id();
            break;
        case LEX_NUM : 
            cur_lex.set_type(Type(TYPE_INT, 0));
            st_type.push(Type(TYPE_INT, 0));
            poliz.push_back(cur_lex);
            get_lex();
            break;
        case LEX_LPAREN :
            get_lex();
            //std::cout << cur_lex << std::endl;
            Expr();
            if (cur_type != LEX_RPAREN) {
                throw Exception("NO RIGHT PAREN", cur_pos.get_str_num(), cur_pos.get_char_num());
            }
            //std::cout << cur_lex << std::endl;
            get_lex();
            break;
        default :
            throw Exception("WRONG LEXEM", cur_pos.get_str_num(), cur_pos.get_char_num());
    }
}

void Parser::Id ()
{
    //std::cout << cur_lex << std::endl;
    if (cur_type == LEX_LSQPAR) {
        poliz.push_back(cur_lex);
        Type tmp = st_type.top();
        st_type.pop();
        --tmp.arr_dim;
        if (tmp.arr_dim < 0) {
            throw Exception("INDEX APPEAL ERROR", cur_pos.get_str_num(), cur_pos.get_char_num());
        }
        st_type.push(tmp);
        get_lex();
        Expr();
        //std::cout << "<" << st_type.top() << ">" << std::endl;
        if (st_type.top() != Type(TYPE_INT, 0)) {
            throw Exception("INDEX IS NOT INTEGER", cur_pos.get_str_num(), cur_pos.get_char_num());
        }
        st_type.pop();
        if (cur_type != LEX_RSQPAR) {
            throw Exception("NO RIGHT SQUARE PAREN", cur_pos.get_str_num(), cur_pos.get_char_num());
        }
        poliz.push_back(cur_lex);
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
            throw Exception("WRONG ID", cur_pos.get_str_num(), cur_pos.get_char_num());
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
                throw Exception("WRONG ID", cur_pos.get_str_num(), cur_pos.get_char_num());
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
        throw Exception("WRONG TYPES", cur_pos.get_str_num(), cur_pos.get_char_num());
    }
}

void Parser::print_poliz ()
{
    for (const Lex &lex : poliz) {
        std::cout << lex << ' ';
    }
    std::cout << std::endl;
}

void Parser::print_expr ()
{
    std::stack<Lex> st_poliz;
    Lex lex0;
    int i = 1;
    for (Lex lex : poliz) {
    type_of_lex lex_type = lex.get_lex_type();
        if (lex_type != LEX_PLUS && lex_type != LEX_TIMES && lex_type != LEX_RSQPAR) {
            if (lex_type == LEX_LSQPAR) {
                Lex lex1 = st_poliz.top();
                st_poliz.pop();
                Type type = lex1.get_type();
                --type.arr_dim;
                lex1.set_type(type);
                st_poliz.push(lex1);
            }
            st_poliz.push(lex);
        } else {
            if (lex_type == LEX_RSQPAR) {
                do {
                    lex0 = st_poliz.top();
                    st_poliz.pop();
                } while (lex0.get_lex_type() != LEX_LSQPAR);
            } else {
                Lex lex1 = st_poliz.top();
                st_poliz.pop();
                Lex lex2 = st_poliz.top();
                st_poliz.pop();
                std::cout << i << ") " << lex1 << ' ' << lex << ' ' << lex2 << " -----> " << Type(TYPE_INT, 0) << std::endl;
                st_poliz.push(Lex(lex1.get_lex_type(), "Expr" + std::to_string(i), lex1.get_type()));
                ++i;
            }
        }
    }
    std::cout << "Standalone expresions : " << std::endl;
    while (!st_poliz.empty()) {
        Lex lex = st_poliz.top();
        std::cout << i << ") " << st_poliz.top() << " -----> " << lex.get_type() << std::endl;
        ++i;
        st_poliz.pop();
    }
}
