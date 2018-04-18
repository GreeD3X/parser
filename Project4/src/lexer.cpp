#include <iostream>
#include "lexer.hpp"
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>

std::ostream& operator << (std::ostream& str, Lex lex) 
{
    str << lex.type << " , " << lex.val;
    return str;
}

std::ostream& operator << (std::ostream& str, Type type)
{
    switch (type.type) {
        case TYPE_NULL :
            str << "TYPE_NULL, " << type.arr_dim;
            return str;
        case TYPE_INT :
            str << "TYPE_INT, " << type.arr_dim;
            return str;
        case TYPE_STRING :
            str << "TYPE_STRING, " << type.arr_dim;
            return str;
    }
}
            
std::ostream& operator << (std::ostream& str, Table table) 
{
    for (auto const &x : table.table) {
        str << x.get_name() << " , " << x.get_type() << std::endl;
    }
    return str;
}

int Table::put (const std::string& buf)
{
    int ind = 0;
    for (const Ident& x : this->table) {
        if (x.get_name() == buf)     
            return ind;
        ++ind;
    }
    table.push_back(Ident(buf));
    return ind;
}

Lex Scaner::get_lex () 
{
    do {
        if (read_next) {
            c = file.get();
        } else {
            read_next = true;
        }
        switch (state) {
            case S :
                if (c == ' ' || c == '\n' || c == '\t' || c == '\r' ) {
                    break;
                } else {
                    buf.clear();
                    if (isalpha(c)) {
                        state = IDENT;
                        buf += c;
                        break;
                    }
                    if (isdigit(c)) {
                        state = NUM;
                        buf += c;
                        break;
                    }    
                    if (c == EOF) {
                        return Lex (LEX_FIN);
                    }
                    state = SIGN;
                    read_next = false;
                }
                break;
            case IDENT :
                if (isalpha(c) || isdigit(c)) {
                    buf += c;
                } else {
                    state = S;
                    read_next = false;
                    return Lex (LEX_ID, TID.put(buf));
                }
                break;
            case NUM :
                if (isdigit(c)) {
                    buf += c;
                } else {
                    state = S;
                    read_next = false;
                    return Lex (LEX_NUM, stoi(buf));
                }
                break;
            case SIGN :
                switch (c) {
                case '+' :
                    state = S; 
                    return Lex (LEX_PLUS);
                case '*' : 
                    state = S; 
                    return Lex (LEX_TIMES);
                case '(' : 
                    state = S; 
                    return Lex (LEX_LPAREN);
                case ')' : 
                    state = S; 
                    return Lex (LEX_RPAREN);
                case '[' : 
                    state = S; 
                    return Lex (LEX_LSQPAR);
                case ']' : 
                    state = S; 
                    return Lex (LEX_RSQPAR);
                default : 
                    throw std::runtime_error("UNEXPECTED SYMBOL");
                }
        }
    } while (true);
}            

Lex Lex_seq_input_iterator::operator* () 
{
    if (lex.get_type() == LEX_FIN) {
        lex_num = -1;
    }
    return lex;
}

Lex_seq_input_iterator& Lex_seq_input_iterator::operator++ () 
{
    if (lex_num != -1) {
        ++lex_num;
    }
    lex = scaner->get_lex();
    return *this;
}

Lex_seq_input_iterator Lex_seq_input_iterator::operator++ (int) 
{
    Lex_seq_input_iterator tmp(scaner, lex_num);
    ++*this;
    return tmp;
}
