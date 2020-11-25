//
//  lexical_analyzer.hpp
//  FlexC++
//
//  Created by Алексей Зерцалов on 21/01/2019.
//  Copyright © 2019 Алексей Зерцалов. All rights reserved.
//

#ifndef lexical_analyzer_hpp
#define lexical_analyzer_hpp

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <unordered_set>

extern long long line_now;

struct Token
{
    char type;
    std::string token;
    
    Token()
    {
        
    }
    
    Token(char _type_, std::string _token_)
    {
        type = _type_;
        token = _token_;
    }
};


inline bool is_word (const char & x);
inline bool is_number (const char & x);
inline bool is_bracket (const char & x);
void error_in_lexical();
void error_in_lexical(std::string);

Token give_token (std::ifstream & fin);


#endif /* lexical_analyzer_hpp */
