//
//  interpreter.hpp
//  FlexC
//
//  Created by Алексей Зерцалов on 18/04/2019.
//  Copyright © 2019 Алексей Зерцалов. All rights reserved.
//

#ifndef interpreter_hpp
#define interpreter_hpp



#include <stdio.h>
#include <iostream>
#include <set>
#include <algorithm>
#include <map>
#include <cmath>
#include <math.h>
#include <vector>
#include <stack>
#include "src/lexical_analyzer.hpp"

enum type_of_expression
{
    _operation_,
    _name_,
    _constant_,
    _link_
};

struct generation_token // for poliz
{
    type_of_expression Type;
    std::string content;
    
    generation_token()
    {
        Type = _constant_;
        content = "0";
    }
    
    generation_token(type_of_expression _Type_, std::string _content_)
    {
        Type = _Type_;
        content = _content_;
    }
};

enum types
{
    _string_,
    _bool_,
    _int_,
    _double_,
    _float_,
    _char_,
    _void_
};


struct variable
{
    types type;
    
    int pointer;
    
    variable (types type = _int_, int pointer = 0) : type(type), pointer(pointer) {}
};


struct variable_ {
    types Type;
    
    std::string content = "";
    
    variable_() {
        content = "";
    }
    variable_ (types _Type, std::string _content) {
        Type = _Type;
        content = _content;
    }
};

struct token {
    type_of_expression Type;
    
    std::string content;
    
    variable_ *link;
    
    token() {
        Type = _constant_;
        content = "0";
        link = nullptr;
    }
};

extern std::vector <generation_token> Generation_poliz;

extern std::map <std::string, std::pair <types, std::vector <std::pair <types, std::string> > > > functions;

extern std::map <std::string, int> function_begin;

char opersCharChar(char a, char b, std::string oper);

char opersCharInt(char a, int b, std::string oper);

char opersIntChar(char a, int b, std::string oper);

double opersDoubleDouble(double a, double b, std::string oper);

char opersIntInt(int a, int b, std::string oper);

types toType(std::string &s);

types getType(std::string &s);

variable_ mathOperations(variable_ fir, variable_ sec, std::string oper);

void operation(std::stack<token> &st, std::vector <generation_token> poliz, int &ind);

void result(std::vector <generation_token> &poliz);


#endif /* interpreter_hpp */
