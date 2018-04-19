#include <iostream>
#include "lexer.hpp"
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>

std::ostream& operator << (std::ostream& str, Lex lex) 
{
    switch (lex.lex_type) {
        case LEX_FIN :
            str << "LEX_FIN" << " , " << lex.name;
            break;
        case LEX_ID :
            str << "LEX_ID" << " , " << lex.name;
            break;
        case LEX_NUM :
            str << "LEX_NUM" << " , " << lex.name;
            break;
        case LEX_PLUS :
            str << "LEX_PLUS" << " , " << lex.name;
            break;
        case LEX_TIMES :
            str << "LEX_TIMES" << " , " << lex.name;
            break;
        case LEX_LPAREN :
            str << "LEX_LPAREN" << " , " << lex.name;
            break;
        case LEX_RPAREN :
            str << "LEX_RPAREN" << " , " << lex.name;
            break;
        case LEX_LSQPAR :
            str << "LEX_LSQPAR" << " , " << lex.name;
            break;
        case LEX_RSQPAR :
            str << "LEX_RSQPAR" << " , " << lex.name;
            break;
        case LEX_NULL :
            str << "LEX_NULL" << " , " << lex.name;
            break;
        default :
            str << lex.lex_type << " , " << lex.name;
        }
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
	default :
	    str << type.type << ", " << type.arr_dim;
	    return str;
    }
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
                    return Lex (LEX_ID, buf);
                }
                break;
            case NUM :
                if (isdigit(c)) {
                    buf += c;
                } else {
                    state = S;
                    read_next = false;
                    return Lex (LEX_NUM, buf);
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
    if (lex.get_lex_type() == LEX_FIN) {
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
