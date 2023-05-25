//
//  Calculus.h
//  Definite_Integral
//
//  Created by Evgeniy Raetsky on 20.03.2023.
//

#ifndef Calculus_h
#define Calculus_h
#include <iostream>
#include <functional>

class Integral
{
private:
    std::function<double(double)> f;
    double left_bound;
    double right_bound;
public:
    Integral() = default;
    Integral(std::function<double(double)> g, double l, double r) : f{g}, left_bound(l), right_bound(r) {}
    double rectangle_integral(int n);
    double trapezoidal_integral(int n);
    double parabolic_integral(int n);
};

double Integral::rectangle_integral(int n) //функція що обчислює визначений інтеграл методом прямокутників
{
    const double width = (this->right_bound - this->left_bound) / n;
    double res = 0;
    for(int i = 0; i < n; i++)
        res += this->f(this->left_bound + (i + 0.5) * width) * width;
    return res;
}

double Integral::trapezoidal_integral(int n) //функція що обчислює визначений інтеграл методом трапецій
{
    const double width = (this->right_bound - this->left_bound) / n;
    double res = 0, x1, x2;
    for(int i = 0; i < n; i++)
    {
        x1 = this->left_bound + i * width;
        x2 = this->left_bound + (i+1) * width;
        res += 0.5 * width * (this->f(x1) + this->f(x2));
    }
    return res;
}

double Integral::parabolic_integral(int n) //функція що обчислює визначений інтеграл методом параболічних трапецій
{
    const double width = (this->right_bound - this->left_bound) / n;
    double res = 0, x1 = this->left_bound;
    for (int i = 0; i < n; ++i)
        res += (width / 6) * (this->f(x1 + i * width) + 4 * this->f(x1 + (i + 0.5) * width) + this->f(x1 + (i + 1) * width));
    return res;
}

#endif /* Calculus_h */
