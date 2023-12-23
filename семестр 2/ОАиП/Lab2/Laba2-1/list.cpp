#include "field.h"
struct Node
{
    field x;
    Node* Next;
    Node* Prev;
};
class List
{
private:
    Node* _begin;
    Node* _end;
    ll count;
    Node* Move(ll ind) {
          Node* it = _begin;
          for (int i = 0; i < ind; ++i)
          {
              it = it->Next;
          }
          return it;
      }
    bool IsCorrectIndex(ll i)
    {
        return (i <= count) and (i >= 0);
    }
public:
    List()
    {
     _begin = nullptr;
     _end = nullptr;
     count = 0;
    }
    List(const List& lst)
    {
        _begin = lst._begin;
        _end= lst._end;
        count = lst.count;
    }
    void push_back(const field& data)
    {
        auto node = new Node();
        node->x = data;
        if(!count)
        {
            node->Prev = nullptr;
            node->Next = nullptr;
            _begin = _end = node;
        }
        else
        {
            node->Prev = _end;
            node->Next = nullptr;
            _end->Next = node;
            _end = node;
        }
        count++;
    }
    void push_front(const field& data)
    {
        auto node = new Node();
        node->x = data;
        if(!count)
        {
            node->Prev = nullptr;
            node->Next = nullptr;
            _begin = _end = node;
        }
        else
        {
            node->Prev = nullptr;
            node->Next = _begin;
            _begin->Prev = node;
            _end = node;
        }
    }
    void insert(const field& data, ll ind)
    {
        if(!IsCorrectIndex(ind))
            return;
        if(ind == count)
        {
            push_back(data);
            return;
        }
        else if(ind == 0)
        {
            push_front(data);
            return;
        }
        else
        {
            auto node = new Node();
            node->x = data;
            Node *nodeprev = Move(ind - 1);
            Node *nodenext = Move(ind);
            node->Prev = nodeprev;
            node->Next = nodenext;
            nodeprev->Next = node;
            nodenext->Prev = node;
            count++;
        }
    }
    void erase(ll i)
    {
        if(!count or (i < 0 and i >=count))
        {
            return;
        }
        if(count == 1)
        {
            Node *cur = _begin;
            for(ll i = 0; i < count - 1; i++)
            {
                cur = cur->Next;
                delete cur->Prev;
            }
            count = 0;
            _begin = nullptr;
            _end = nullptr;
        }
        else if(!i)
        {
            Node *node = Move(i);
            Node *next = node->Next;
            _begin = next;
            next->Prev = nullptr;
            delete node;
            count--;
        }
        else if(i == count - 1)
        {
            Node *node = Move(i);
            Node *prev = node->Prev;
            _end = prev;
            prev->Next = nullptr;
            delete node;
            count--;
        }
        else
        {
            Node *node = Move(i);
            Node *next = node->Next;
            Node *prev = node->Prev;
            next->Prev = prev;
            prev->Next = next;
            delete node;
            count--;
        }
    }
    void clear()
    {
        Node *cur = _begin;
        for(ll i = 0; i < count - 1; i++)
        {
            cur = cur->Next;
            delete cur->Prev;
        }
        count = 0;
        _begin = nullptr;
        _end = nullptr;
    }
    field& getElement(ll ind)
    {
        Node *node = _begin;
        for(ll i = 0; i < ind;i++)
        {
            node = node->Next;
        }
        return node->x;
    }
    [[nodiscard]] ll size() const
    {
        return count;
    }
    Node *begin()
    {
        return this->_begin;
    }
    Node *end()
    {
        return this->_end;
    }
    List& operator = (const List& other)
    {
        _begin = other._begin;
        _end = other._end;
        count = other.count;
        return *this;
    }
    field& operator[](ll ind)
    {
        return getElement(ind);
    }
};
