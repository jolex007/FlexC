//
//  main.cpp
//  FlexC++
//
//  Created by Алексей Зерцалов on 21/01/2019.
//  Copyright © 2019 Алексей Зерцалов. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include "lexical_analyzer.hpp"
#include "parser.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "This programm need 1 argument (input file, and file to write POLIZ)\n";
        return 1;
    }
    
    ifstream fin;
    ofstream fout;

    fin.open(argv[1]);
    fout.open(argv[2]);
    
    fin >> noskipws; // for no skip spaces
    
#ifdef DEBUG
   while (!fin.eof()) {
       Token a;
       a = give_token(fin);
       cout << (int) a.type << " " << a.token << endl;
   }
#endif
    

    
    Parser pars;
    pars.set(fin, fout);
    pars.start();
    
    fin.close();
    fout.close();
    
    return 0;
}


