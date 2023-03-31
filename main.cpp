#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include "Calculus.h"
#include "Backend.h"

void text_typing(const std::string& text)
{
    for (int i = 0; i < text.length(); ++i)
    {
        std::cout << text[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void instructions()
{
    std::string text = "The list of avaliable integrals:\n";
    text += "x^a, a^x, 1/x, sin, cos, tg, ctg\n";
    text += "You may enter your function if the function type is listed bellow. Please do not type any unnecessary characters while entering integrated function.\n";
    text += "There is an example of correct input for all of functions avaliable:\n";
    text += "3x^7, 7*2^x, 5/x, sin(x), cosx, 4tg(x), -7ctgx\n";
    text += "Try it!\n";
    text_typing(text);
}

void greeting()
{
    std::string begin_text;
    begin_text = "\t\t*** DEFINITE INTEGRAL CALCULATION ***\nWelcome to the definite integral calcuation program. Type 'I' to Check the instructions or 'C' to calculate your definite integral.\n";
    text_typing(begin_text);
}

void write_integral(std::ostream& out_stream, const std::string& s, double l, double r, double res)
{
    out_stream << "\u222B";
    out_stream<< "(" << s << ")dx from " << l << " to " << r <<  " = " << res <<std::endl;
}

bool correct_expr(const std::string& s)
{
    std::string forbidden = "+`[]{}&@!$%<>,|~;:";
    for (const char ch : s)
    {
        if (forbidden.find(ch) != -1)
            if (ch != 'x')
                return false;
    }
    return true;
}

int main() {
    std::string s; std::string n; std::string begin_text;
    double l,r,result; int precision;
    char method, ch;
    greeting();
    std::cin >> ch;
    while (ch != 'I' && ch != 'C')
    {
        std::cout << "Incorrect character. Please enter the correct one\n";
        std::cin >> ch;
    }
    if (ch == 'I')
        instructions();
    std::cin.ignore();
    std::cout << "Please enter the integrated function:\n";
    getline(std::cin,s);
    while (!correct_expr(s))
    {
        std::cout << "Incorrect expression. Please enter the correct one\n";
        getline(std::cin,s);
    }
    std::cout << "Please enter the integration bounds.\n";
    std::cout << "Left bound: ";
    std::cin >> l;
    std::cout << "Right bound: ";
    std::cin >> r;
    std::cout << "Now choose integration method. Enter one character:\n";
    std::cout << "R - to use rectangle method\nT - to use trapezoidal method\nP - to use parabolic method.\n";
    std::cin >> method;
    while (method != 'R' && method != 'T' && method != 'P')
    {
        std::cout << "Incorrect character. Enter the correct one\n";
        std::cin >> method;
    }
    std::cout << "Finally, you can choose the precision of calculation. You can enter the integer value from 1 to 10^5, or just skip to continue with recommended precision.\n";
    std::cin.ignore();
    getline(std::cin,n);
    precision = (n.empty()) ? 100 : stod(n);
    std::cout << "Solving your integral...\n";
    if (method == 'R')
        result = solve(s,l,r,0,precision);
    else if (method == 'T')
        result = solve(s,l,r,1,precision);
    else if (method == 'P')
        result = solve(s,l,r,2,precision);
    else {std::cout << "Unexpected error occured."; exit(1);}
    
    std::cout << "Do you want to save the results in the text file or view it in console? F/C:\n";
    std::cin >> ch;
    while (ch != 'F' && ch != 'C')
    {
        std::cout << "Incorrect character. Enter the correct one\n";
        std::cin >> ch;
    }
    if (ch == 'F')
    {
        std::string filename;
        std::cout << "Please set a file name:\n";
        std::cin.ignore();
        getline(std::cin, filename);
        filename += ".txt";
        std::fstream file;
        file.open(filename,std::ios::out);
        if (file.is_open())
            write_integral(file, s, l, r, result);
        else std::cout << "Error: can not open file\n";
        file.close();
    }
    else
        write_integral(std::cout, s, l, r, result);
    std::cout << "Thank you for using!\n";
    return 0;
}
