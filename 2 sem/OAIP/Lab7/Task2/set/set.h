#pragma once
#include <iostream>
#include <memory>
#include "node.h"
template <typename Key>
class set
{
    using pointer = std::shared_ptr<Node<Key>>;
private:
    pointer root;
    size_t _size;
    void insert(pointer);
    void fix_insertion(pointer&);
    void left_rotate(pointer);
    void right_rotate(pointer);
    void fix_deletion(pointer&);
    void add_other(pointer);
    void clear(pointer&);
public:
    class Iterator;
    using iterator = Iterator;
    set()
            : root(nullptr),
              _size(0) {}
    set(const set&);
    set& operator=(const set&);
    void insert(const Key&);
    void erase(const Key&);
    iterator begin();
    iterator end();
    iterator find(const Key&);
    void clear();
    pointer& get_root(){ return root; }
};
template <typename Key>
class set<Key>::Iterator
        {
    using pointer = std::shared_ptr<Node<Key>>;
private:
    pointer cur;
    pointer root;
public:
    Iterator(const pointer& ptr, const pointer& root)
            : cur(ptr),
              root(root) {}
    Iterator& operator++()
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
    Iterator& operator--()
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
    bool operator==(const Iterator& other) const
    {
        return cur == other.cur;
    }
    bool operator!=(const Iterator& other) const
    {
        return cur != other.cur;
    }
};
template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key)
{
    auto cur = root;
    while (cur)
    {
        if (key < cur->key)
        {
            cur = cur->left;
        }
        else if (key > cur->key)
        {
            cur = cur->right;
        }
        else
        {
            return { cur, root };
        }
    }
    return { nullptr, root };
}
template <typename Key>
void set<Key>::insert(pointer node)
{
    ++_size;
    if (!root)
    {
        root = node;
        return;
    }
    auto cur = root;
    do
    {
        if (cur->key < node->key)
        {
            if (!cur->right)
            {
                node->parent = cur;
                cur->right = node;
                return;
            }
            cur = cur->right;
        }
        else if (cur->key > node->key)
        {
            if (!cur->left)
            {
                node->parent = cur;
                cur->left = node;
                return;
            }
            cur = cur->left;
        }
        else
        {
            --_size;
            return;
        }
    }
    while (true);
}
template <typename Key>
void set<Key>::insert(const Key& key)
{
    auto node = std::make_shared<Node<Key>>(key);
    insert(node);
    fix_insertion(node);
}
template <typename Key>
void set<Key>::erase(const Key& key)
{
    auto cur = root;
    while (cur)
    {
        if (key < cur->key)
        {
            cur = cur->left;
        }
        else if (key > cur->key)
        {
            cur = cur->right;
        }
        else
        {
            --_size;
            auto parent = cur->parent.lock();
            if (!cur->left && !cur->right)
            {
                if (!parent)
                {
                    root.reset();
                } else if (cur == parent->left)
                {
                    parent->left.reset();
                }
                else
                {
                    parent->right.reset();
                }
                fix_deletion(parent);
                return;
            }
            if (!cur->left || !cur->right)
            {
                auto child = cur->left ? cur->left : cur->right;
                if (!parent)
                {
                    root = child;
                    child->parent.reset();
                }
                else if (cur == parent->left)
                {
                    parent->left = child;
                    child->parent = parent;
                }
                else
                {
                    parent->right = child;
                    child->parent = parent;
                }
                fix_deletion(child);
                return;
            }
            auto successor = cur->right;
            while (successor->left)
            {
                successor = successor->left;
            }
            cur->key = successor->key;
            cur = successor;
        }
    }
}
template <typename Key>
void set<Key>::fix_insertion(pointer& node)
{
    while (true)
    {
        auto parent = node->parent.lock();
        if (!parent || !parent->color)
        {
            break;
        }
        auto grandparent = parent->parent.lock();
        auto uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
        if (uncle && uncle->color)
        {
            parent->color = false;
            uncle->color = false;
            grandparent->color = true;
            node = grandparent;
        }
        else
        {
            if (parent == grandparent->left)
            {
                if (node == parent->right)
                {
                    left_rotate(parent);
                    node = parent;
                    parent = node->parent.lock();
                }
                right_rotate(grandparent);
            }
            else
            {
                if (node == parent->left)
                {
                    right_rotate(parent);
                    node = parent;
                    parent = node->parent.lock();
                }
                left_rotate(grandparent);
            }
            parent->color = false;
            grandparent->color = true;
            break;
        }
    }
    root->color = false;
}
template <typename Key>
void set<Key>::left_rotate(pointer node)
{
    auto child = node->right;
    auto parent = node->parent.lock();
    if (!parent)
    {
        root = child;
        child->parent.reset();
    }
    else if (node == parent->left)
    {
        parent->left = child;
        child->parent = parent;
    }
    else
    {
        parent->right = child;
        child->parent = parent;
    }
    node->right = child->left;
    if (child->left)
    {
        child->left->parent = node;
    }
    child->left = node;
    node->parent = child;
}
template <typename Key>
void set<Key>::right_rotate(pointer node)
{
    auto child = node->left;
    auto parent = node->parent.lock();
    if (!parent)
    {
        root = child;
        child->parent.reset();
    }
    else if (node == parent->left)
    {
        parent->left = child;
        child->parent = parent;
    }
    else
    {
        parent->right = child;
        child->parent = parent;
    }
    node->left = child->right;
    if (child->right)
    {
        child->right->parent = node;
    }
    child->right = node;
    node->parent = child;
}
template <typename Key>
void set<Key>::fix_deletion(pointer& node)
{
    while (node != root && (!node || !node->color))
    {
        auto parent = node->parent.lock();
        if (node == parent->left)
        {
            auto sibling = parent->right;
            if (sibling->color)
            {
                sibling->color = false;
                parent->color = true;
                left_rotate(parent);
                sibling = parent->right;
            }
            if ((!sibling->left || !sibling->left->color) && (!sibling->right || !sibling->right->color))
            {
                sibling->color = true;
                node = parent;
            }
            else
            {
                if (!sibling->right || !sibling->right->color)
                {
                    sibling->left->color = false;
                    sibling->color = true;
                    right_rotate(sibling);
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = false;
                sibling->right->color = false;
                left_rotate(parent);
                node = root;
            }
        }
        else
        {
            auto sibling = parent->left;
            if (sibling->color)
            {
                sibling->color = false;
                parent->color = true;
                right_rotate(parent);
                sibling = parent->left;
            }
            if ((!sibling->right || !sibling->right->color) && (!sibling->left || !sibling->left->color))
            {
                sibling->color = true;
                node = parent;
            }
            else
            {
                if (!sibling->left || !sibling->left->color)
                {
                    sibling->right->color = false;
                    sibling->color = true;
                    left_rotate(sibling);
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = false;
                sibling->left->color = false;
                right_rotate(parent);
                node = root;
            }
        }
    }
    if (node)
    {
        node->color = false;
    }
}
template <typename Key>
typename set<Key>::iterator set<Key>::begin()
{
    if (!root)
    {
        return { nullptr, root };
    }
    auto cur = root;
    while (cur->left)
    {
        cur = cur->left;
    }
    return { cur, root };
}
template <typename Key>
typename set<Key>::iterator set<Key>::end()
{
    return { nullptr, root };
}
template <typename Key>
void set<Key>::clear(pointer& node)
{
    if (!node)
    {
        return;
    }
    clear(node->left);
    clear(node->right);
    node.reset();
}
template <typename Key>
void set<Key>::clear()
{
    clear(root);
    _size = 0;
}
template <typename Key>
set<Key>::set(const set& other)
{
    root = nullptr;
    _size = other._size;
    add_other(other.root);
}
template <typename Key>
set<Key>& set<Key>::operator=(const set& other)
        {
    if (this == &other)
    {
        return *this;
    }
    clear();
    _size = other._size;
    add_other(other.root);
    return *this;
}
template <typename Key>
void set<Key>::add_other(pointer node)
{
    if (!node)
    {
        return;
    }
    insert(node->key);
    add_other(node->left);
    add_other(node->right);
}