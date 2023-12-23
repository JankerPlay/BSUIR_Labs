#include "customStack.h"
void CS::push(Node **head, std::string data)
{
    Node* temp = new Node;
    if (!temp)
    {
        throw out_of_range("stack overflow");
        exit(1);
    }
    temp->data = data;
    temp->link = (*head);
    (*head) = temp;
}
bool CS::isEmpty(Node **head)
{
    return *head == NULL;
}
string CS::top(Node *node)
{
    if (node == NULL)
    {
        exit(1);
    }
    return node->data;
}
string CS::pop(Node* node,Node **head)
{
    Node* temp = new Node;
    if (*head == NULL)
    {
        exit(1);
    }
    else
    {
        string get = node->data;
        temp = *head;
        *head = temp->link;
        free(temp);
        return get;
    }
}
