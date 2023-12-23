//
// Created by Nikita on 3/10/2023.
//

#ifndef UNTITLED7_POSTFIX_H
#define UNTITLED7_POSTFIX_H

#include <string>
#include "customVector.h"

class ans {
public:
     int priority(std::string alpha);
     std::string convert(customVector1<std::string> infix);
    long double result(std::string infix);
    std::string getPost(std::string infix);
};





#endif //UNTITLED7_POSTFIX_H
