//
//  Backend.h
//  Definite_Integral
//
//  Created by Evgeniy Raetsky on 25.03.2023.
//

#ifndef Backend_h
#define Backend_h

#include <iostream>
#include <string>
#include <math.h>

const double PI = 3.141592;
using ul = unsigned long;


std::function<double(double)> power_function(const std::string &s)
{
    double c;
    ul index,p;
    index = s.find("x^");
    c = s.substr(0,index) != "" ? stod(s.substr(0,index)) : 1;
    p = stoi(s.substr(index+2, s.length()));
    return [c,p](double x){return c * pow(x,p);};
}

std::function<double(double)> inverse_ratio_function(const std::string &s)
{
    double c;
    ul index;
    index = s.find("/x");
    c = s.substr(0,index) != "" ? stod(s.substr(0,index)) : 1;
    return [c](double x){return c / x;};
}

std::function<double(double)> exponential_function(const std::string &s)
{
    double c,base;
    ul index, star;
    index = s.find("^x");
    star = s.find("*") != -1 ? s.find("*") : 0;
    c = s.substr(0,star) != "" ? stod(s.substr(0,star)) : 1;
    base = stod(s.substr(star+1, index));
    return [c,base](double x){return c * pow(base,x);};
}

std::function<double(double)> sin_function(const std::string &s)
{
    double c;
    ul index;
    index = s.find("sin");
    c = s.substr(0,index) != "" ? stod(s.substr(0,index)) : 1;
    return [c](double x){return c * sin(x);};
}

std::function<double(double)> cos_function(const std::string &s)
{
    double c;
    ul index;
    index = s.find("cos");
    c = s.substr(0,index) != "" ? stod(s.substr(0,index)) : 1;
    return [c](double x){return c * cos(x);};
}

std::function<double(double)> tg_function(const std::string &s)
{
    double c;
    ul index;
    index = s.find("tg");
    c = s.substr(0,index) != "" ? stod(s.substr(0,index)) : 1;
    return [c](double x){return c * tan(x);};
}

std::function<double(double)> ctg_function(const std::string &s)
{
    double c;
    ul index;
    index = s.find("ctg");
    c = s.substr(0,index) != "" ? stod(s.substr(0,index)) : 1;
    return [c](double x){return c * tan(PI/2 - x);};
}

double solve(const std::string &s, double l, double r, int method, int p)
{
    if (s.find("x^") != -1)
    {
        Integral I(power_function(s), l, r);
        if (!method){return I.rectangle_integral(p);}
        return method == 1 ? I.trapezoidal_integral(p) : I.parabolic_integral(p);
    }
    
    else if (s.find("/x") != -1)
    {
        Integral I(inverse_ratio_function(s), l, r);
        if (!method){return I.rectangle_integral(p);}
        return method == 1 ? I.trapezoidal_integral(p) : I.parabolic_integral(p);
    }
    
    else if (s.find("^x") != -1)
    {
        Integral I(exponential_function(s), l, r);
        if (!method){return I.rectangle_integral(p);}
        return method == 1 ? I.trapezoidal_integral(p) : I.parabolic_integral(p);
    }
    
    else if (s.find("sin") != -1)
    {
        Integral I(sin_function(s), l, r);
        if (!method){return I.rectangle_integral(p);}
        return method == 1 ? I.trapezoidal_integral(p) : I.parabolic_integral(p);
    }

    else if (s.find("cos") != -1)
    {
        Integral I(cos_function(s), l, r);
        if (!method){return I.rectangle_integral(p);}
        return method == 1 ? I.trapezoidal_integral(p) : I.parabolic_integral(p);
    }

    else if (s.find("ctg") != -1)
    {
        Integral I(ctg_function(s), l, r);
        if (!method){return I.rectangle_integral(p);}
        return method == 1 ? I.trapezoidal_integral(p) : I.parabolic_integral(p);
    }

    else if (s.find("tg") != -1)
    {
        Integral I(tg_function(s), l, r);
        if (!method){return I.rectangle_integral(p);}
        return method == 1 ? I.trapezoidal_integral(p) : I.parabolic_integral(p);
    }
    else
    {
        std::cout << "Parsing error. Incorrect input.\n"; return 0;
    }
    return 0;
}

#endif /* Backend_h */
