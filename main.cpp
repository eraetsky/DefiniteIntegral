#include <iostream>
#include <fstream>
#include <filesystem>
#include "Calculus.h"
#include "Backend.h"
#include "Interface.h"
#include "Texts.h"
#include "Utils.h"

int main()
{
    utils::clear_console();
    std::string function, precision_str;
    double l,r,result;
    int precision;
    char ch;
    
    Texts texts;
    iConsole* ptr_greeting = new Greeting(texts.get_greeting());
    iConsole* ptr_instructions = new Instructions(texts.get_instructions());
    
    ptr_greeting->print(std::cout); 
    
    std::cin >> ch;
    while (ch != 'I' && ch != 'C' && ch != 'i' && ch != 'c')
    {
        texts.print(std::cout,texts.get_incorrect_input());
        std::cin >> ch;
    }
    
    if (ch == 'I' || ch == 'i')
        ptr_instructions->print(std::cout);
    do {
        std::cin.ignore();
        std::cout << "Choose input mode. Fetch input from text file or console? F/C:\n";
        std::cin >> ch;
        
        while (ch != 'F' && ch != 'C' && ch != 'f' && ch != 'c')
        {
            texts.print(std::cout,texts.get_incorrect_input());
            std::cin >> ch;
        }
        
        if (ch == 'C' || ch == 'c')
            utils::get_input_console(function, ch, l, r, precision);
        else
            utils::get_input_file(function, ch, l, r, precision);
        
        texts.print(std::cout, texts.get_solving());
        
        try
        {
            if (ch == 'R' || ch == 'r')
                result = solve(function,l,r,0,precision);
            else if (ch == 'T' || ch == 't')
                result = solve(function,l,r,1,precision);
            else if (ch == 'P' || ch == 'p')
                result = solve(function,l,r,2,precision);
            else {result = -1; throw ("Unexpected error occured: ");}
            
            if (isnan(result)) throw("Result is not a number. The integrated function is not correct\n");
        } catch (char const* err)
        {
            std::cerr << err;
            exit(1);
        }
        
        iConsole* ptr_result = new Result(function, l, r, result);
        texts.print(std::cout, texts.get_result());
        
        std::cin >> ch;
        while (ch != 'F' && ch != 'C' && ch != 'f' && ch != 'c')
        {
            texts.print(std::cout,texts.get_incorrect_input());
            std::cin >> ch;
        }
        
        if (ch == 'F' || ch == 'f')
            utils::write_result_to_file(ptr_result);
        else
            ptr_result->print(std::cout);
        
        texts.print(std::cout, texts.get_end());
        std::cin >> ch;
        } while (ch != 'Q');
    utils::clear_console();
    return 0;
}
