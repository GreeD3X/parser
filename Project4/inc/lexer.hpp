#ifndef LEXER
#define LEXER

#include <fstream>
#include <vector>
#include <iostream>

enum type_of_lex {
    LEX_NULL,    //0
    LEX_ID,      //1
    LEX_NUM,     //2
    LEX_PLUS,    //3
    LEX_MINUS,   //4
    LEX_TIMES,   //5
    LEX_LPAREN,  //6
    LEX_RPAREN,  //7
    LEX_LSQPAR,  //8
    LEX_RSQPAR,  //9
    LEX_FIN      //10
};

enum types {
    TYPE_NULL,
    TYPE_INT,
    TYPE_STRING
};

class Type {

  public :
    types type;
    int arr_dim;
    Type (types type = TYPE_NULL, int arr_dim = 0) : type(type), arr_dim(arr_dim) {}
    bool operator == (const Type &type) { return this->type == type.type && this->arr_dim == type.arr_dim; }
    bool operator != (const Type &type) { return this->type != type.type || this->arr_dim != type.arr_dim; }

};

std::ostream& operator << (std::ostream&, Type);

class Lex {

    type_of_lex lex_type;
    std::string name;
    Type type;
  public:
    Lex (type_of_lex lex_type = LEX_NULL, const std::string &name = "", const Type &type = Type()) : lex_type(lex_type), name(name), type(type)  {}
    type_of_lex get_lex_type() const { return lex_type; }
    std::string get_name() const { return name; }
    Type get_type() const { return type; }
    void set_type(Type new_type) { type = new_type; }
    friend std::ostream& operator << (std::ostream& str, Lex lex);

}; 

class Scaner {

    enum states {S, IDENT, NUM, SIGN};
    std::ifstream file;
    states state;
    std::string buf;
    bool read_next;
    char c;
  public :
    int str_num;
    int char_num;
    Scaner (const std::string& name) : state(S), read_next(true), str_num(1), char_num(0) { file.open(name); }
    Lex get_lex ();

};  

class Lex_seq_input_iterator : public std::iterator<std::input_iterator_tag, std::string> {
    
    Scaner *scaner;
    int lex_num;
    Lex lex;
  public :
    int get_str_num () { return scaner->str_num; }
    int get_char_num () { return scaner->char_num; }
    int char_num;
    Lex_seq_input_iterator (Scaner *scaner, int lex_num) : scaner(scaner), lex_num(lex_num) {};
    Lex operator* (); 
    Lex_seq_input_iterator& operator++ ();
    Lex_seq_input_iterator operator++ (int);
    bool operator== (Lex_seq_input_iterator lex_seq_iterator) const {
        return (lex_num == lex_seq_iterator.lex_num);
    }
    bool operator!= (Lex_seq_input_iterator lex_seq_iterator) const {
        return (lex_num != lex_seq_iterator.lex_num);
    }
    
};

class Lex_seq {

    Scaner *scaner;
  public :
    Lex_seq (Scaner &scaner) : scaner(&scaner) {}
    Lex_seq_input_iterator begin () {
        return Lex_seq_input_iterator(scaner, 0);
    }
    Lex_seq_input_iterator end () {
        return Lex_seq_input_iterator(scaner, -1);
    }
    Lex_seq_input_iterator begin () const {
        return Lex_seq_input_iterator(scaner, 0);
    }
    Lex_seq_input_iterator end () const {
        return Lex_seq_input_iterator(scaner, -1);
    }

};

class Exception {
   
  public :
    std::string what;
    int str_num;
    int char_num;
    Exception (const std::string &what, const int str_num, const int char_num) : what(what), str_num(str_num), char_num(char_num) {}

};

std::ostream& operator << (std::ostream&, Exception);

#endif
