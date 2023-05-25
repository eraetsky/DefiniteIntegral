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
#include "exprtk.hpp"

std::function<double(double)> parse_function(const std::string& expr_str) { //функція синтаксичного аналізатора
    return [expr_str](double x){
        typedef exprtk::symbol_table<double> symbol_table_t;
        typedef exprtk::expression<double>     expression_t;
        typedef exprtk::parser<double>             parser_t;
        symbol_table_t symbol_table;
        expression_t   expression;
        parser_t       parser;
        symbol_table.add_variable("x",x);
        expression.register_symbol_table(symbol_table);
        parser.compile(expr_str,expression);
        return expression.value();
    };
}

double solve(const std::string &s, double l, double r, int method, int p) //функція що повертає результат користувачу
{
    Integral I(parse_function(s),l,r);
    if (!method){return I.rectangle_integral(p);}
    return method == 1 ? I.trapezoidal_integral(p) : I.parabolic_integral(p);
}

#endif /* Backend_h */
