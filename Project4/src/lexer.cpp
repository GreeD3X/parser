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
            str << lex.name;
            break;
        case LEX_NUM :
            str << lex.name;
            break;
        case LEX_PLUS :
            str << "+";
            break;
        case LEX_TIMES :
            str << "*";
            break;
        case LEX_LPAREN :
            str << "(";
            break;
        case LEX_RPAREN :
            str << ")";
            break;
        case LEX_LSQPAR :
            str << "[";
            break;
        case LEX_RSQPAR :
            str << "]";
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
    if (type.arr_dim != 0) {
        str << type.arr_dim << " dimensional array of ";
    }
    switch (type.type) {
        case TYPE_NULL :
            str << "TYPE_NULL, ";
            return str;
        case TYPE_INT :
            str << "integer ";
            return str;
        case TYPE_STRING :
            str << "string, ";
            return str;
	default :
	    str << type.type;
	    return str;
    }
}
            
std::ostream& operator << (std::ostream& str, Exception excp)
{
    str << excp.str_num << ":" << excp.char_num << ": " << excp.what;
    return str;
}

Lex Scaner::get_lex () 
{
    do {
        if (read_next) {
            c = file.get();
            ++char_num;
        } else {
            read_next = true;
        }
        switch (state) {
            case S :
                if (c == ' ' || c == '\n' || c == '\t' || c == '\r' ) {
                    if (c == '\n') {
                        ++str_num;
                        char_num = 0;
                    }
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
                    throw Exception("UNEXPECTED SYMBOL", str_num, char_num);
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
