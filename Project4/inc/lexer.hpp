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

class Lex {

    type_of_lex type;
    int val;
  public:
    Lex (type_of_lex type = LEX_NULL, int val = 0) : type(type), val(val) {}
    type_of_lex get_type() { return type; }
    int get_val() { return val; }
    friend std::ostream& operator << (std::ostream& str, Lex lex);

}; 

class Type {

  public :
    types type;
    int arr_dim;
    Type (types type = TYPE_NULL, int arr_dim = 0) : type(type), arr_dim(arr_dim) {}
    bool operator == (const Type &type) { return this->type == type.type && this->arr_dim == type.arr_dim; }
    bool operator != (const Type &type) { return this->type != type.type || this->arr_dim != type.arr_dim; }
    friend std::ostream& operator << (std::ostream&, Type);

};

class Ident {

    std::string name;
    Type type;
  public :
    Ident (const std::string &name, const Type &type = Type(TYPE_NULL, 0)) : name(name), type(type) {}
    const std::string& get_name () const { return name; }
    void set_name (const std::string &str) { name = str; }
    Type get_type () const { return type; }
    void set_type (const Type &new_type){ type = new_type; }

};

class Table { 
    
    std::vector<Ident> table;  
  public :
    Ident& operator[] (int i) { return table[i]; }
    int put (const std::string&);
    friend std::ostream& operator << (std::ostream&, Table);

};

class Scaner {

    enum states {S, IDENT, NUM, SIGN};
    std::ifstream file;
    states state;
    std::string buf;
    bool read_next;
    char c;
  public :
    Table TID;
    Scaner (const std::string& name) : state(S), read_next(true) { file.open(name); }
    Lex get_lex ();
    void print_TID () { std::cout << TID; }

};  

class Lex_seq_input_iterator : public std::iterator<std::input_iterator_tag, std::string> {
    
    Scaner *scaner;
    int lex_num;
    Lex lex;
  public :
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

#endif
