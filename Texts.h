//
//  Texts.h
//  Definite_Integral
//
//  Created by Evgeniy Raetsky on 13.04.2023.
//

#ifndef Texts_h
#define Texts_h
#include "Constants.h"

class Texts : public TextConstants
{
private:
    const std::string greeting_text;
    const std::string instructions_text;
    const std::string incorrect_input_text;
    const std::string choose_method_text;
    const std::string precision_text;
    const std::string solving_text;
    const std::string result_text;
    const std::string end_text;
public:
    Texts(): greeting_text(greeting), instructions_text(instructions), incorrect_input_text(incorrect_input),
        choose_method_text(choose_method), precision_text(precision), solving_text(solving), result_text(result), end_text(end){}
    const std::string& get_greeting(){return this->greeting_text;}
    const std::string& get_instructions(){return this->instructions_text;}
    const std::string& get_incorrect_input(){return this->incorrect_input_text;}
    const std::string& get_choose_method(){return this->choose_method_text;}
    const std::string& get_precision(){return this->precision_text;}
    const std::string& get_solving(){return this->solving_text;}
    const std::string& get_result(){return this->result_text;}
    const std::string& get_end(){return this->end_text;}
    void print(std::ostream& outs, const std::string& s){outs << s;}
};

#endif /* Texts_h */
