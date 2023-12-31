#pragma once
#include <iostream>
#include <memory>
#include "node.h"
template <typename Key>
class iterator
{
    using pointer = std::shared_ptr<Node<Key>>;
private:
    pointer cur;
    pointer root;
public:
    iterator(const pointer& ptr, const pointer& root)
            : cur(ptr),
              root(root) {}
    iterator& operator++()
    {
        if (!cur)
        {
            return *this;
        }
        if (cur->right)
        {
            cur = cur->right;
            while (cur->left)
            {
                cur = cur->left;
            }
        }
        else
        {
            pointer parent = nullptr;
            while (cur != root && !parent)
            {
                parent = cur->parent.lock();
                if (cur == parent->left)
                {
                    cur = parent;
                }
                else
                {
                    cur = parent;
                    parent.reset();
                }
            }
        }
        return *this;
    }
    iterator& operator--()
    {
        if (!cur)
        {
            if (!root)
                return *this;
            cur = root;
            while (cur->right)
            {
                cur = cur->right;
            }
            return *this;
        }
        if (cur->left)
        {
            cur = cur->left;
            while (cur->right)
            {
                cur = cur->right;
            }
        }
        else
        {
            pointer parent = nullptr;
            while (cur != root && !parent)
            {
                parent = cur->parent.lock();
                if (cur == parent->right)
                {
                    cur = parent;
                }
                else
                {
                    cur = parent;
                    parent.reset();
                }
            }
        }
        return *this;
    }
    Key& operator*()
    {
        return cur->key;
    }
    bool operator==(const iterator& other) const
    {
        return cur == other.cur;
    }
    bool operator!=(const iterator& other) const
    {
        return cur != other.cur;
    }
};