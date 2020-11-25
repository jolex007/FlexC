//
//  parser.hpp
//  FlexC++
//
//  Created by Алексей Зерцалов on 28/01/2019.
//  Copyright © 2019 Алексей Зерцалов. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <list>
#include <map>
#include <set>
#include <vector>
#include "src/lexical_analyzer.hpp"
#include "src/interpreter.hpp"

// Generation part


//enum type_of_expression
//{
//    _operation_,
//    _name_,
//    _constant_
//};
//
//struct generation_token // for poliz
//{
//    type_of_expression Type;
//    std::string content;
//
//    generation_token()
//    {
//        Type = _constant_;
//        content = "0";
//    }
//
//    generation_token(type_of_expression _Type_, std::string _content_)
//    {
//        Type = _Type_;
//        content = _content_;
//    }
//};
//
//extern std::vector <generation_token> Generation_poliz;

// end of generation part

void error_in_parser();
void error_in_parser(std::string);
//
//enum types
//{
//    _string_,
//    _bool_,
//    _int_,
//    _double_,
//    _float_,
//    _char_, 
//    _void_
//};
//
//
//struct variable
//{
//    types type;
//
//    int pointer;
//
//    variable (types type = _int_, int pointer = 0) : type(type), pointer(pointer) {}
//};

extern std::list <std::map <std::string, variable> > tids;

types check_operations(types A, types B, std::string op);

class Parser
{
    
private:
    
    std::ifstream *fin;
    
    std::ofstream *fout;
    
    Token _token_;
    
    // Analyzer
    
    void programm();

    void function();
    
    std::string type_function();
    
    std::string type();
    
    std::string name();
    
    std::pair <types, std::string> description_func();
    
    void description();
    
    void section(std::string _type_);
    
    void comp_operator(bool is_func);
    
    void operator_();
    
    void spec_operator();

    void operator_if();
    
    void operator_for();
    
    void operator_while();
    
    void operator_switch();
    
    void operator_else();
    
    unsigned int operator_case(int pos = 0, unsigned int prev_case = 0);
    
    types term();
    
    types term_1();
    
    types term_2();
    
    types term_3();
    
    types term_4();
    
    types term_5();
    
    types term_6();
    
    types term_7();
    
    types term_8();
    
    types term_9();
    
    types term_10();
    
    types term_11();
    
    types term_12();
    
    types term_13();
    
public:
    
    void set(std::ifstream &_input_stream_, std::ofstream &_out_stream_);
    
    void start();
    
    void print_poliz();
};


#endif /* parser_hpp */
