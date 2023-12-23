#ifndef UNTITLED7_CUSTOMSTACK_H
#define UNTITLED7_CUSTOMSTACK_H
#include "bibl.h"
struct Node
{
    string  data;
    Node* link;
};
class CS
{
public:
    void push(Node** head, string  data);
    bool isEmpty(Node** head);
    string top(Node* node);
    string pop(Node* node,Node** head);
};
#endif
