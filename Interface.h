//
//  Interface.h
//  Definite_Integral
//
//  Created by Evgeniy Raetsky on 13.04.2023.
//

#ifndef Interface_h
#define Interface_h

#include <iostream>
#include <string>

class iConsole
{
protected:
    std::string message;
public:
    iConsole() = default;
    iConsole(const std::string& s): message{s} {}
    virtual ~iConsole(){}
    virtual void print(std::ostream&) = 0;
    virtual void set_message(const std::string&) = 0;

};

class Instructions : public iConsole
{
public:
    Instructions(): iConsole(){}
    Instructions(const std::string& s): iConsole(s) {}
    virtual void print(std::ostream& outs) override {outs << this->message;} 
    virtual void set_message(const std::string& s) override {this->message = s;}
};

class Greeting : public iConsole
{
public:
    Greeting(): iConsole(){}
    Greeting(const std::string& s): iConsole(s) {}
    virtual void print(std::ostream& outs) override {outs << this->message;}
    virtual void set_message(const std::string& s) override {this->message = s;}
};

class Result : public iConsole
{
private:
    double left_bound;
    double right_bound;
    double answer;
public:
    Result(): iConsole(){}
    Result(const std::string& s, double l, double r, double ans): iConsole(s),
        left_bound(l), right_bound(r), answer(ans) {}
    virtual void print(std::ostream&) override;
    virtual void set_message(const std::string& s) override {this->message = s;}
};

void Result::print(std::ostream& outs)
{
    outs << "\u222B";
    outs << "(" << this->message << ")dx from " << this->left_bound << " to " << this->right_bound <<  " = " << std::setprecision(9) << this->answer <<std::endl;
}

#endif /* Interface_h */
