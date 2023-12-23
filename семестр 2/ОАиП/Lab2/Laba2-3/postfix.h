#ifndef UNTITLED7_POSTFIX_H
#define UNTITLED7_POSTFIX_H
#include "bibl.h"
#include "customStack.h"
#include "customVector.h"
class postfix
{
public:
     ll priority(string alpha);
     string convert(CV<string> infix);
     ld result(string infix);
     string getPost(string infix);
};
#endif
