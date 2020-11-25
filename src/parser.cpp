//
//  parser.cpp
//  FlexC++
//
//  Created by Алексей Зерцалов on 28/01/2019.
//  Copyright © 2019 Алексей Зерцалов. All rights reserved.
//

#include "parser.hpp"
#include <stack>
#include <string>

//
//  Generation part
//

bool cancel_pushing = false;

std::vector <generation_token> Generation_poliz;

void push_operation(Token operation)
{
    if (!cancel_pushing)
        Generation_poliz.push_back(generation_token(_operation_, operation.token));
}

void push_operation(std::string operation)
{
    if (!cancel_pushing)
        Generation_poliz.push_back(generation_token(_operation_, operation));
}

void push_constant(Token constant)
{
    if (!cancel_pushing)
        Generation_poliz.push_back(generation_token(_constant_, constant.token));
}

void push_constant(std::string constant)
{
    if (!cancel_pushing)
        Generation_poliz.push_back(generation_token(_constant_, constant));
}

void push_name(Token name)
{
    if (!cancel_pushing)
        Generation_poliz.push_back(generation_token(_name_, name.token));
}

void push_name(std::string name)
{
    if (!cancel_pushing)
        Generation_poliz.push_back(generation_token(_name_, name));
}

//
//  End of Generation part
//

std::list <std::map <std::string, variable> > tids;

// Functions

//std::map <std::string, std::pair <types, std::vector <std::pair <types, std::string> > > > functions;
//
//std::map <std::string, int> function_begin;

bool open_is_func = false;
types now_function_type;

types give_type(std::string _type_)
{
    if (_type_ == "string") {
        return _string_;
    }
    else if (_type_ == "char") {
        return _char_;
    }
    else if (_type_ == "int") {
        return _int_;
    }
    else if (_type_ == "double") {
        return _double_;
    }
    else if (_type_ == "float") {
        return _float_;
    }
    else if (_type_ == "bool") {
        return _bool_;
    }
    else if (_type_ == "void"){
        return _void_;
    }
    else {
        error_in_parser("unknown type");
    }
    return _int_;
}

std::string type_to_string(types _type_)
{
    if (_type_ == _string_) {
        return "string";
    }
    else if (_type_ == _char_) {
        return "char";
    }
    else if (_type_ == _int_) {
        return "int";
    }
    else if (_type_ == _double_) {
        return "double";
    }
    else if (_type_ == _float_) {
        return "float";
    }
    else if (_type_ == _bool_) {
        return "bool";
    }
    else if (_type_ == _void_) {
        return "void";
    }
    return "int";
}


variable * find_var(std::string var)
{
    for (auto it = tids.begin(); it != tids.end(); it++) {
        auto st = (*it).find(var);
        if (st != (*it).end()) {
            return &(st->second);
        }
    }
    error_in_parser("undefined variable");
    return nullptr;
}

void add_var(std::string _type_, int _pointer_, std::string _var_)
{
    if ((*tids.begin()).find(_var_) != (*tids.begin()).end()) {
        error_in_parser("redifintion of \"" + _var_ + "\"");
    }
    if (_type_ == "string") {
        (*tids.begin())[_var_] = variable(_string_, _pointer_);
    }
    else if (_type_ == "char") {
        (*tids.begin())[_var_] = variable(_char_, _pointer_);
    }
    else if (_type_ == "int") {
        (*tids.begin())[_var_] = variable(_int_, _pointer_);
    }
    else if (_type_ == "double") {
        (*tids.begin())[_var_] = variable(_double_, _pointer_);
    }
    else if (_type_ == "float") {
        (*tids.begin())[_var_] = variable(_float_, _pointer_);
    }
    else if (_type_ == "bool") {
        (*tids.begin())[_var_] = variable(_bool_, _pointer_);
    }
    else {
        error_in_parser("unknown type of variable");
    }
    
    push_operation("#");
}

void add_tid(bool is_func = false)
{
    if (!is_func) {
        push_operation("{");
    }
    
    tids.emplace_front();
}

void erase_tid()
{
    push_operation("}");
    tids.pop_front();
}

void add_function(std::string func_type, std::string func_name)
{
    if (functions.find(func_name) != functions.end()) {
        error_in_parser("redifintion of \"" + func_name + "\"");
    }
    if (func_type == "string") {
        functions[func_name].first = _string_;
    }
    else if (func_type == "char") {
        functions[func_name].first = _char_;
    }
    else if (func_type == "int") {
        functions[func_name].first = _int_;
    }
    else if (func_type == "double") {
        functions[func_name].first = _double_;
    }
    else if (func_type == "float") {
        functions[func_name].first = _float_;
    }
    else if (func_type == "bool") {
        functions[func_name].first = _bool_;
    }
    else if (func_type == "void") {
        functions[func_name].first = _void_;
    }
    else {
        error_in_parser("unknown type of variable");
    }
    
    push_operation("##");
}

void check_func(std::string func_name)
{
    if (functions.find(func_name) != functions.end()) {
        error_in_parser("redifintion of \"" + func_name + "\"");
    }
}

types check_operations(types A, types B, std::string oper)
{
    if (A == _string_) {
        if (B == _string_) {
            if (oper == "+" || oper == "+=" || oper == "=") {
                return _string_;
            }
            else if (oper == "==" || oper == "!=" ||
                     oper == "<" || oper == "<=" ||
                     oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                error_in_parser("invalid operands");
            }
        }
        else if (B == _bool_) {
            error_in_parser("invalid operands");
        }
        else if (B == _int_) {
            error_in_parser("invalid operands");
        }
        else if (B == _double_) {
            error_in_parser("invalid operands");
        }
        else if (B == _float_) {
            error_in_parser("invalid operands");
        }
        else if (B == _char_) {
            error_in_parser("invalid operands");
        }
    }
    else if (A == _bool_) {
        if (B == _string_) {
            error_in_parser("invalid operands");
        }
        else if (B == _bool_) {
            return _bool_;
        }
        else if (B == _int_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _int_;
            }
        }
        else if (B == _double_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _float_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _float_;
            }
        }
        else if (B == _char_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _char_;
            }
        }
    }
    else if (A == _int_) {
        if (B == _string_) {
            error_in_parser("invalid operands");
        }
        else if (B == _bool_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _int_;
            }
        }
        else if (B == _int_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _double_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _float_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _char_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
    }
    else if (A == _double_) {
        if (B == _string_) {
            error_in_parser("invalid operands");
        }
        else if (B == _bool_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _int_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _double_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _float_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _char_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
    }
    else if (A == _float_) {
        if (B == _string_) {
            error_in_parser("invalid operands");
        }
        else if (B == _bool_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _int_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _double_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _float_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _char_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
    }
    else if (A == _char_) {
        if (B == _string_) {
            error_in_parser("invalid operands");
        }
        else if (B == _bool_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _int_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _double_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _float_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _double_;
            }
        }
        else if (B == _char_) {
            if (oper == "==" || oper == "!=" ||
                oper == "<" || oper == "<=" ||
                oper == ">" || oper == ">=") {
                return _bool_;
            }
            else {
                return _char_;
            }
        }
    }
    if (A == _void_ || B == _void_) {
        error_in_parser("cannot convert void function to something");
    }
    return _int_;
}

/***********************/
/* syntaxical analyzer */
/***********************/

void error_in_parser()
{
    throw (std::string)"ERROR";
}

void error_in_parser(std::string _error_)
{
    throw "Error in line: " + std::to_string(line_now) + "\n" + _error_ + "\n";
}

void Parser::programm()
{
    while (_token_.type != -1) {
        function();
    }
}

void Parser::function()
{
    cancel_pushing = true;
    
    std::string type_func;
    
    type_func = type_function();
    
    std::string func_name = name();
    
    add_function(type_func, func_name);
    
    now_function_type = give_type(type_func);
    
    cancel_pushing = false;
    
    function_begin[func_name] = (int)Generation_poliz.size();
    
    push_operation("$B");
    
    add_tid();
    
    if (_token_.type != 3 || _token_.token != "(") {
        error_in_parser("expected '('");
    }
    
    _token_ = give_token(*fin);
    
    std::vector <std::pair<types, std::string> > arguments;
    
    if (_token_.type != 3 || _token_.token != ")") {
        
        arguments.push_back(description_func());
        
        while (_token_.type == 5 && _token_.token == ",") {
            
            _token_ = give_token(*fin);
            
            arguments.push_back(description_func());
        }
    }
    if (_token_.type != 3 || _token_.token != ")") {
        error_in_parser("expected ')'");
    }
    
    functions[func_name].second = arguments;
    
    _token_ = give_token(*fin);
    
    comp_operator(true);
    
    erase_tid();
    
    push_operation("$E");
}

std::string Parser::type_function()
{
    if (_token_.type != 6 || !(_token_.token == "bool" ||
                               _token_.token == "int" ||
                               _token_.token == "float" ||
                               _token_.token == "char" ||
                               _token_.token == "void" ||
                               _token_.token == "string" ||
                               _token_.token == "double")) {
        error_in_parser("expected function type");
    }
    std::string ans = _token_.token;
    
    _token_ = give_token(*fin);
    
    push_name(ans);
    
    return ans;
}

std::string Parser::type()
{
    if (_token_.type != 6 || !(_token_.token == "bool" ||
                               _token_.token == "int" ||
                               _token_.token == "char" ||
                               _token_.token == "float" ||
                               _token_.token == "string" ||
                               _token_.token == "double")) {
        error_in_parser("expected type");
    }
    
    std::string ans = _token_.token;
    
    _token_ = give_token(*fin);
    
    push_name(ans);
    
    return ans;
}

std::string Parser::name()
{
    if (_token_.type != 1) {
        error_in_parser("expected name");
    }
    std::string ans = _token_.token;
    
    _token_ = give_token(*fin);
    
    push_name(ans);
    
    return ans;
}

std::pair <types, std::string> Parser::description_func()
{
    cancel_pushing = true;
    
    std::string type_var;
    
    type_var = type();
    
    std::string name_var;
    
    name_var = name();
    
    add_var(type_var, 0, name_var);
    
    cancel_pushing = false;
    
    return {give_type(type_var), name_var};
}

void Parser::description()
{
    std::string _type_;
    
    _type_ = type();
    
    section(_type_);
    
    while (_token_.type == 5 && _token_.token == ",") {
        
        _token_ = give_token(*fin);
        
        section(_type_);
    }
    
    
    if (_token_.type == 5 && _token_.token == ";") {
        _token_ = give_token(*fin);
        
        push_operation(";");
        
        return;
    }
    else {
        error_in_parser("expected ';'");
    }
}

void Parser::section(std::string _type_)
{
    int _pointer_ = 0;
    
    while (_token_.type == 4 && _token_.token == "*") {
        _pointer_++;
        _token_ = give_token(*fin);
    }
    
    add_var(_type_, _pointer_, name());
    
    if (_token_.type != 4 || _token_.token != "=") {
        push_operation(";");
        return;
    }
    
    _token_ = give_token(*fin);
    
    types term_type = term();
    types var_type = give_type(_type_);
    
    check_operations(var_type, term_type, "=");
    
    push_operation("=");
    
    push_operation(";");
}


void Parser::comp_operator(bool is_func = false)
{
    if (_token_.type != 3 || _token_.token != "{")
        error_in_parser("expected '{'");
    
    if (!is_func)
        add_tid();
    
    _token_ = give_token(*fin);
    operator_();
    
    while (_token_.type != 3 || _token_.token != "}") {
        operator_();
    }
    if (_token_.type != 3 || _token_.token != "}")
        error_in_parser("expexted '}'");
    
    if (!is_func)
        erase_tid();
    
    _token_ = give_token(*fin);
}

void Parser::operator_()
{
    if (_token_.type == 3 && _token_.token == "{") {
        comp_operator();
    }
    else if ((_token_.type == 6 && _token_.token == "for") ||
             (_token_.type == 6 && _token_.token == "while") ||
             (_token_.type == 6 && _token_.token == "if") ||
             (_token_.type == 6 && _token_.token == "switch")) {
        spec_operator();
    }
    else if ((_token_.type == 6 && _token_.token == "bool") ||
             (_token_.type == 6 && _token_.token == "int") ||
             (_token_.type == 6 && _token_.token == "char") ||
             (_token_.type == 6 && _token_.token == "string") ||
             (_token_.type == 6 && _token_.token == "double")) {
        description();
    }
    else if (_token_.type == 6 && (_token_.token == "break" || _token_.token == "continue")) {
        _token_ = give_token(*fin);
        
        if (_token_.type != 5 || _token_.token != ";") {
            error_in_parser("expected ';'");
        }
        
        _token_ = give_token(*fin);
    }
    else if (_token_.type == 6 && _token_.token == "return") {
        _token_ = give_token(*fin);
        
        if (_token_.type == 5 && _token_.token == ";") {
            if (now_function_type != _void_) {
                error_in_parser("return in non-void function");
            }
            
            push_operation("$E");
            
            push_operation(";");
            
            _token_ = give_token(*fin);
            return;
        }
        
        types term_type = term();
        
        check_operations(now_function_type, term_type, "=");
        
        if (_token_.type != 5 || _token_.token != ";") {
            error_in_parser("expected ';'");
        }
        
        push_operation("$E");
        
        push_operation(";");
        
        _token_ = give_token(*fin);
    }
    else {
        term();
        
        if (_token_.type != 5 || _token_.token != ";") {
            error_in_parser("expected ';'");
        }
        
        push_operation(";");
        
        _token_ = give_token(*fin);
    }
}

void Parser::spec_operator()
{
    if (_token_.type == 6 && _token_.token == "for") {
        operator_for();
    }
    else if (_token_.type == 6 && _token_.token == "if") {
        operator_if();
    }
    else if (_token_.type == 6 && _token_.token == "while") {
        operator_while();
    }
    else if (_token_.type == 6 && _token_.token == "switch") {
        operator_switch();
    }
    else {
        error_in_parser("expected special operator");
    }
}

void Parser::operator_if()
{
    if (_token_.type != 6 || _token_.token != "if") {
        error_in_parser("expected \"if\"");
    }
    
    _token_ = give_token(*fin);
    
    if (_token_.type != 3 || _token_.token != "(") {
        error_in_parser("expected '('");
    }
    
    
    _token_ = give_token(*fin);
    
    term();
    
    if (_token_.type != 3 || _token_.token != ")") {
        error_in_parser("expected ')'");
    }
    
    size_t pos1 = Generation_poliz.size();
    
    push_constant("");
    
    push_operation("!F");
    
    _token_ = give_token(*fin);
    
    operator_();
    
    if (_token_.type == 6 && _token_.token == "else") {
        
        size_t pos2 = Generation_poliz.size();
        
        push_constant("");
        
        push_operation("!A");
        
        Generation_poliz[pos1].content = std::to_string(Generation_poliz.size());
        
        operator_else();
        
        Generation_poliz[pos2].content = std::to_string(Generation_poliz.size());
    }
    else {
        Generation_poliz[pos1].content = std::to_string(Generation_poliz.size());
    }
}

void Parser::operator_for()
{
    if (_token_.type != 6 || _token_.token != "for") {
        error_in_parser("expected \"for\"");
    }
    
    _token_ = give_token(*fin);
    
    if (_token_.type != 3 || _token_.token != "(") {
        error_in_parser("expected '('");
    }
    
    add_tid();
    
    _token_ = give_token(*fin);
    
    if (_token_.type != 5 && _token_.token != ";") {
        if (_token_.type == 6 && (_token_.token == "bool" ||
                                  _token_.token == "char" ||
                                  _token_.token == "float" ||
                                  _token_.token == "int")) {
            description();
        }
        else {
            term();
            
            if (_token_.type != 5 && _token_.token != ";") {
                error_in_parser("expected ';'");
            }
            
            push_operation(";");
            
            _token_ = give_token(*fin);
        }
    }
    else {
        _token_ = give_token(*fin);
    }
    
    size_t pos3 = Generation_poliz.size();
    
    term();
    
    size_t pos1 = Generation_poliz.size();
    
    push_constant("");
    
    push_operation("!F");
    
    size_t pos2 = Generation_poliz.size();
    
    push_constant("");
    
    push_operation("!A");
    
    if (_token_.type != 5 && _token_.token != ";") {
        error_in_parser("expected ';'");
    }
    
    _token_ = give_token(*fin);
    
    int pos4 = (int) Generation_poliz.size();
    
    if (_token_.type != 3 && _token_.token != ")") {
        term();
        
        push_operation(";");
    }
    
    push_constant(std::to_string(pos3));
    
    push_operation("!A");
    
    if (_token_.type != 3 && _token_.token != ")"){
        error_in_parser("expexted ')'");
    }
    
    Generation_poliz[pos2].content = std::to_string(Generation_poliz.size());
    
    _token_ = give_token(*fin);
    
    operator_();
    
    push_constant(std::to_string(pos4));
    
    push_operation("!A");
    
    Generation_poliz[pos1].content = std::to_string(Generation_poliz.size());
    
    erase_tid();
}

void Parser::operator_while()
{
    if (_token_.type != 6 || _token_.token != "while") {
        error_in_parser("expected \"while\"");
    }
    
    _token_ = give_token(*fin);
    
    if (_token_.type != 3 || _token_.token != "(") {
        error_in_parser("expected '('");
    }
    
    _token_ = give_token(*fin);
    
    int pos2 = (int) Generation_poliz.size();
    
    term();
    
    size_t pos1 = Generation_poliz.size();
    
    push_constant("");
    
    push_operation("!F");
    
    if (_token_.type != 3 || _token_.token != ")") {
        error_in_parser("expected ')'");
    }
    
    _token_ = give_token(*fin);
    
    operator_();
    
    push_constant(std::to_string(pos2));
    
    push_operation("!A");
    
    Generation_poliz[pos1].content = std::to_string(Generation_poliz.size());
}

void Parser::operator_switch()
{
    if (_token_.type != 6 || _token_.token != "switch") {
        error_in_parser("expected \"switch\"");
    }
    
    _token_ = give_token(*fin);
    
    add_tid();
    
    if (_token_.type != 3 || _token_.token != "(") {
        error_in_parser("expected '('");
    }
    
    _token_ = give_token(*fin);
    
    unsigned int type_position = (int)Generation_poliz.size();
    
    push_constant("");
    
    push_constant("#switch_param#");
    
    push_operation("#");
    
    types term_type = term();
    
    Generation_poliz[type_position].content = type_to_string(term_type);
    
    push_operation("=");
    
    push_operation(";");
    
    push_operation(";");
    
    unsigned int y_pos = (int)Generation_poliz.size();
    
    push_constant("");
    
    push_operation("!A");
    
    if (_token_.type != 3 || _token_.token != ")") {
        error_in_parser("expected ')'");
    }
    
    _token_ = give_token(*fin);
    
    if (_token_.type == 3 && _token_.token == "{") {
        
        _token_ = give_token(*fin);
        
        int pos = 0;
        
        while (_token_.type != 3 || _token_.token != "}") {
            y_pos = operator_case(pos, y_pos);
            
            pos++;
        }
        
        Generation_poliz[y_pos].content = std::to_string(Generation_poliz.size());
        
        _token_ = give_token(*fin);
        
        erase_tid();
    }
}

void Parser::operator_else()
{
    if (_token_.type != 6 || _token_.token != "else") {
        error_in_parser("expected \"else\"");
    }
    
    _token_ = give_token(*fin);
    
    operator_();
}

unsigned int Parser::operator_case(int pos, unsigned int prev_case)
{
    if (_token_.type == 6 && _token_.token == "case") {
        _token_ = give_token(*fin);
        
        unsigned int y_pos = (int)Generation_poliz.size();
        
        push_constant("");
        
        push_operation("!A");
        
        Generation_poliz[prev_case].content = std::to_string(Generation_poliz.size());
        
        push_constant("#switch_param#");
        
        push_operation("?");
        
        if (_token_.type != 2) {
            error_in_parser("expected constant");
        }
        
        push_constant(_token_);
        
        push_operation("==");
        
        _token_ = give_token(*fin);
        
        unsigned int return_pos = (int)Generation_poliz.size();
        
        push_constant("");
        
        push_operation("!F");
        
        if (_token_.type != 5 || _token_.token != ":") {
            error_in_parser("expected ':'");
        }
        
        _token_ = give_token(*fin);
        
        Generation_poliz[y_pos].content = std::to_string(Generation_poliz.size());
        
        while (_token_.token != "case" && _token_.token != "default" && _token_.token != "}") {
            operator_();
        }
        
        return return_pos;
    }
    else if (_token_.type == 6 && _token_.token == "default" && _token_.token != "}") {
        
        _token_ = give_token(*fin);
        
        Generation_poliz[prev_case].content = std::to_string(Generation_poliz.size());
        
        if (_token_.type != 5 || _token_.token != ":") {
            error_in_parser("expected ':'");
        }
        
        _token_ = give_token(*fin);
        
        while (_token_.token != "case" && _token_.token != "default" && _token_.token != "}") {
            operator_();
        }
    }
    else {
        error_in_parser("expected \"case\" or \"default\"");
    }
    
    return 0;
}

types Parser::term()
{
    types type_expr = term_1();
    
    return type_expr;
}

types Parser::term_1()
{
    types type_expr = term_2();
    
    std::string oper;
    types type_expr2;
    
    std::stack <std::string> stack_of_oper;
    
    while (_token_.type == 4 && (_token_.token == "=" || _token_.token == "+=" ||
                                 _token_.token == "-=" || _token_.token == "*=" ||
                                 _token_.token == "/=" || _token_.token == "%=" ||
                                 _token_.token == "|=" || _token_.token == "&=" ||
                                 _token_.token == "^=")) {
        Generation_poliz.pop_back();
        
        push_operation("@");
        
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_2();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        stack_of_oper.push(oper);
    }
    
    
    while (!stack_of_oper.empty()) {
        push_operation(stack_of_oper.top());
        stack_of_oper.pop();
    }
    
    return type_expr;
}

types Parser::term_2()
{
    types type_expr = term_3();
    
    std::string oper;
    types type_expr2;
    
    while (_token_.type == 4 && _token_.token == "||") {
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_3();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_3()
{
    types type_expr = term_4();
    
    std::string oper;
    types type_expr2;
    
    while (_token_.type == 4 && _token_.token == "&&") {
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_4();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_4()
{
    types type_expr = term_5();
    
    std::string oper;
    types type_expr2;
    
    while (_token_.type == 4 && _token_.token == "|") {
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_5();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_5()
{
    types type_expr = term_6();
    
    std::string oper;
    types type_expr2;
    
    while (_token_.type == 4 && _token_.token == "&") {
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_6();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_6()
{
    types type_expr = term_7();
    
    std::string oper;
    types type_expr2;
    
    while (_token_.type == 4 && (_token_.token == "==" || _token_.token == "!=")) {
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_7();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_7()
{
    types type_expr = term_8();
    
    std::string oper;
    types type_expr2;
    
    while (_token_.type == 4 && (_token_.token == "<" || _token_.token == "<=" ||
                                 _token_.token == ">" || _token_.token == ">=")) {
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_8();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_8()
{
    types type_expr = term_9();
    
    std::string oper;
    types type_expr2;
    
    while (_token_.type == 4 && (_token_.token == "+" || _token_.token == "-")) {
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_9();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_9()
{
    types type_expr = term_10();
    
    std::string oper;
    types type_expr2;
    
    while (_token_.type == 4 && (_token_.token == "*" || _token_.token == "/" || _token_.token == "%")) {
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_10();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_10()
{
    types type_expr = term_11();
    
    std::string oper;
    types type_expr2;
    
    while (_token_.type == 4 && _token_.token == "^^") {
        oper = _token_.token;
        
        _token_ = give_token(*fin);
        
        type_expr2 = term_11();
        
        type_expr = check_operations(type_expr, type_expr2, oper);
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_11()
{
    bool is_pref = false;
    std::string oper;
    
    if (_token_.type == 4 && (_token_.token == "++" || _token_.token == "--" ||
                              _token_.token == "+" || _token_.token == "-" ||
                              _token_.token == "!" || _token_.token == "~" ||
                              _token_.token == "*" || _token_.token == "&" ||
                              _token_.token == "^")) {
        is_pref = true;
        if (_token_.token == "-") {
            oper = "~-";
        }
        else if (_token_.token == "+") {
            oper = "~+";
        }
        else if (_token_.token == "++") { // prefix
            oper = "+#";
        }
        else if (_token_.token == "--") {
            oper = "-#";
        }
        else {
            oper = _token_.token;
        }
        _token_ = give_token(*fin);
        // do smth
    }
    
    types type_expr = term_12();
    
    if (is_pref && type_expr == _string_ && (oper != "*" && oper != "&")) {
        error_in_parser("cannot perform this (" + oper + ") operation with string");
    }
    
    if (oper.size() > 0) {
        Generation_poliz.pop_back();
        
        push_operation(oper);
    }
    
    return type_expr;
}

types Parser::term_12()
{
    types type_expr = term_13();
    std::string oper;
    
    if (_token_.type == 4 && (_token_.token == "++" || _token_.token == "--")) {
        Generation_poliz.pop_back();
        
        if (_token_.token == "++") { // postfix
            oper = "#+";
        }
        if (_token_.token == "--") {
            oper = "#-";
        }
        
        if (type_expr == _string_) {
            error_in_parser("cannot perform this (" + _token_.token + ") operation with string");
        }
        
        _token_ = give_token(*fin);
        
        //do smth
        
        push_operation(oper);
    }
    
    return type_expr;
}



types Parser::term_13()
{
    types type_expr = _int_;
    
    
    if (_token_.type == 3 && _token_.token == "(") {
        _token_ = give_token(*fin);
        
        type_expr = term();
        
        if (_token_.type != 3 || _token_.token != ")") {
            error_in_parser("expected ')'");
        }
        
        _token_ = give_token(*fin);
    }
    else if (_token_.type == 1) {
        // function
        
        Token previous_token = _token_;
        
        _token_ = give_token(*fin);
        
        if (_token_.type == 3 && _token_.token == "(") {
            
            _token_ = give_token(*fin);
            
            if (functions.find(previous_token.token) == functions.end()) {
                error_in_parser("unknown function");
            }
            
            unsigned int indx_arguments = 0;
            
            types argument_type;
            
            if (_token_.type != 3 || _token_.token != ")") {
                
                argument_type = term();
                
                if (indx_arguments >= functions[previous_token.token].second.size()) {
                    error_in_parser("too much arguments in function");
                }
                if (functions[previous_token.token].second[indx_arguments].first != argument_type) {
                    error_in_parser("wrong type of " + std::to_string(indx_arguments + 1) + " argument in function");
                }
                
                indx_arguments++;
                
                while (_token_.type == 5 && _token_.token == ",") {
                    _token_ = give_token(*fin);
                    
                    argument_type = term();
                    
                    if (indx_arguments >= functions[previous_token.token].second.size()) {
                        error_in_parser("too much arguments in function");
                    }
                    if (functions[previous_token.token].second[indx_arguments].first != argument_type) {
                        error_in_parser("wrong type of " + std::to_string(indx_arguments + 1) + " argument in function");
                    }
                    
                    indx_arguments++;
                }
            }
            
            if (indx_arguments != functions[previous_token.token].second.size()) {
                error_in_parser("too few arguments in function");
            }
            
            if (_token_.type != 3 || _token_.token != ")") {
                error_in_parser("expected ')'");
            }
            
            _token_ = give_token(*fin);
            
            push_name(previous_token);
            
            push_operation("$F");
            
            type_expr = functions[previous_token.token].first;
        }
        else {
            // <name> (previous)
            
            push_name(previous_token);
            
            push_operation("?");
            
            variable * var = find_var(previous_token.token);
            
            type_expr = (*var).type;
        }
    }
    else if (_token_.type == 2) {
        // constant
        
        push_constant(_token_);
        
        if (_token_.token[0] == '\"') {
            type_expr = _string_;
        }
        else if (_token_.token[0] == '\'') {
            type_expr = _char_;
        }
        else {
            if (_token_.token.find(".") != std::string::npos) {
                type_expr = _double_;
            }
            else {
                type_expr = _int_;
            }
        }
        
        _token_ = give_token(*fin);
    }
    else if (_token_.type == 6 && (_token_.token == "true" ||
                                   _token_.token == "false")) {
        // true false
        
        push_constant(_token_);
        
        type_expr = _bool_;
        
        _token_ = give_token(*fin);
    }
    else {
        error_in_parser("expected operator");
    }
    
    return type_expr;
}

void Parser::set(std::ifstream &_input_stream_, std::ofstream &_out_stream_)
{
    fin = &_input_stream_;
    fout = &_out_stream_;
}

void Parser::start()
{
    try {
        tids.emplace_front();
        _token_ = give_token(*fin);
        programm();
        print_poliz();
        (*fout).close();
        std::cout << "Сompilation completed successfully\n\n";
        result(Generation_poliz);
    }
    catch (const std::string & e) {
        std::cout << e << '\n';
    }
}

void Parser::print_poliz()
{
    for (int i = 0; i < Generation_poliz.size(); i++) {
        (*fout) << "(";
        if (Generation_poliz[i].Type == _name_) {
            (*fout) << "name) ";
        }
        else if (Generation_poliz[i].Type == _operation_) {
            (*fout) << "operation) ";
        }
        else if (Generation_poliz[i].Type == _constant_) {
            (*fout) << "constant) ";
        }
        (*fout) << Generation_poliz[i].content << '\n';
    }
}


