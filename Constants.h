//
//  Constants.h
//  Definite_Integral
//
//  Created by Evgeniy Raetsky on 04.05.2023.
//

#ifndef Constants_h
#define Constants_h

class TextConstants
{
protected:
    std::string greeting = "\t\t*** DEFINITE INTEGRAL CALCULATION ***\nWelcome to the definite integral calcuation program. Type 'I' to Check the instructions or 'C' to calculate your definite integral.\n";

    std::string instructions = "Examples of integrated functions: sqrt(1 - (3 / x^2)), sin(2.5 * x), log2(x) * 25x^2\n The full documentation about integrated functions is avaliable here: https://github.com/ArashPartow/exprtk/blob/master/readme.txt\n";

    std::string incorrect_input = "The input is incorrect. Please enter again.\n";

    std::string choose_method = "Now choose integration method. Enter one character:\nR - to use rectangle method\nT - to use trapezoidal method\nP - to use parabolic method.\n";

    std::string precision = "Finally, you can choose the precision of calculation. You can enter the integer value from 100 to 10^5, or just skip to continue with recommended precision.\n";

    std::string solving = "Solving your integral...\n";

    std::string result = "Do you want to save the results in the text file or view it in console? F/C:\n";

    std::string end = "Thank you for using!\nEnter Q to quit or type any other character to calculate one more integral.\n";

};


#endif /* Constants_h */
