//
//  Utils.h
//  Definite_Integral
//
//  Created by Evgeniy Raetsky on 04.05.2023.
//

#ifndef Utils_h
#define Utils_h
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Texts.h"
#include "Interface.h"

namespace utils
{
    Texts texts;
    std::string special_chars = "`[]{}&@!$%<>,|~;:";

    std::tuple<double,double,bool> get_bounds(std::fstream& f) //функція що читає з файлу і повертає межі інтегрування
    {
        std::string line, chl, chr;
        double l, r; bool badcast = false;
        getline(f, line);
        chl = line.substr(0,line.find(' '));
        chr = line.substr(line.find(' ') + 1, line.length());
        try
        {
            l = stod(chl);
            r = stod(chr);
        } catch (...) {
            badcast = true;
        }
        return std::make_tuple(l, r, badcast);
    }

    std::tuple<double,double,bool> get_bounds() //функція що читає з консолі і повертає межі інтегрування
    {
        std::string chl,chr;
        double l, r; bool badcast = false;
        std::cout << "Please enter the integration bounds. Left bound must be less than the right.\n";
        std::cout << "Left bound: ";
        std::cin >> chl;
        std::cin.ignore();
        std::cout << "Right bound: ";
        std::cin >> chr;
        try
        {
            l = stod(chl);
            r = stod(chr);
        } catch(...)
        {
            badcast = true;
        }
        return std::make_tuple(l, r, badcast);
    }

    bool contains(const std::string&forbidden, const std::string& s) //функція що перевіряє чи рядок користувача містить спеціальні символи
    {
        for (const char ch : s)
        {
            if (forbidden.find(ch) != -1)
                if (ch != 'x')
                    return false;
        }
        return true;
    }


    void get_input_console(std::string& function, char& ch, double& l, double& r, int& precision) //функція що отримує вхідні дані для обчислення інтеграла з консолі
    {
        bool flag; std::string n;
        std::cin.ignore();
        std::cout << "Please enter the integrated function:\n";
        getline(std::cin,function);
        while (!contains(special_chars,function))
        {
            texts.print(std::cout,texts.get_incorrect_input());
            getline(std::cin,function);
        }
        std::tie(l,r,flag) = get_bounds();
        while (l >= r || flag)
        {
            texts.print(std::cout,texts.get_incorrect_input());
            std::tie(l,r,flag) = get_bounds();
        }
        texts.print(std::cout, texts.get_choose_method());
        std::cin.ignore();
        std::cin >> ch;
        while (ch != 'R' && ch != 'T' && ch != 'P' && ch != 'r' && ch != 't' && ch != 'p')
        {
            texts.print(std::cout,texts.get_incorrect_input());
            std::cin >> ch;
        }
    
        texts.print(std::cout, texts.get_precision());
        std::cin.ignore();
        getline(std::cin,n);
        try {
            precision = (n.empty()) ? 1000 : stod(n);
            if (precision > 100000) throw ("To great to use :(");
        }catch(...)
        {
            precision = 1000;
            std::cout << "Incorrect input, recommended precision used...\n";
        }
    }


    void get_input_file(std::string& function, char& ch, double& l, double& r, int& precision) //функція що отримує вхідні дані для обчислення інтеграла з файлу
    {
        bool flag; std::string n;
        std::cin.ignore();
        std::cout << "Please specify the full path to the input file:\n";
        std::string filepath, line;
        getline(std::cin, filepath);
        std::filesystem::path p{filepath};
        std::fstream file;
        file.open(filepath,std::ios::in);
        if (file.is_open())
        {
            getline(file, function);
            std::tie(l,r,flag) = get_bounds(file);
            if (l >= r || flag)
                std::cout << "File input is incorrect. Unexpected result may be received.\n";
            file >> ch;
            if (ch != 'R' && ch != 'T' && ch != 'P' && ch != 'r' && ch != 't' && ch != 'p')
                std::cout << "File input is incorrect. Unexpected result may be received.\n";
            getline(file, n);
            try {
                precision = (n.empty()) ? 1000 : stod(n);
                if (precision > 100000) throw ("To great to use :(");
            } catch (...) {
                precision = 1000;
                std::cout << "Incorrect input, recommended precision used...\n";
            }
        }
        else std::cout << "have not opened\n";
    }

    
     void clear_console() //функція що очищує консоль
     {
         system("clear");
     }
     
    void write_result_to_file(iConsole* ptr_result) //функція запису результатів до файлу
    {
        std::string filename, filepath, fullpath;
        std::cout << "Please enter a file name:\n";
        std::cin.ignore();
        getline(std::cin, filename);
        filename += ".txt";
        std::cout << "Enter a filepath or skip to save file in a default directory:\n";
        getline(std::cin, filepath);
        if (filepath.empty()) {filepath = std::filesystem::current_path().string(); }
        else {filepath = std::filesystem::path(filepath).lexically_normal().string();}
        fullpath = filepath + "/" + filename;
        std::fstream file;
        file.open(fullpath,std::ios::out|std::ios::app);
        if (file.is_open())
        {
            ptr_result->print(file);
            std::cout << "Result was saved in " + filename + " at the pass: " + filepath << std::endl;
        }
        else std::cout << "Error: can not open file\n";
        file.close();
    }
}

#endif /* Utils_h */
