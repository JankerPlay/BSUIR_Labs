#include <iostream>
template<typename Key, typename Value>
class AVLTree
{
public:
    struct Node
    {
        Key key;
        Value value;
        Node *left;
        Node *right;
        Node() : left(nullptr), right(nullptr), key(Key()), value(Value()) {}
        explicit Node(const Key &key, const Value &value) : left(nullptr), right(nullptr), key(key), value(value) {}
    };
    Node *root;
    Node* remove(Node *&node, const Key &key)
    {
        if (!node)
            return node;
        if (key < node->key)
        {
            node->left = remove(node->left, key);
            node = balance(node);
        }
        else if (key > node->key)
        {
            node->right = remove(node->right, key);
            node = balance(node);
        }
        else
        {
            if (!node->left && !node->right)
            {
                delete node;
                node = nullptr;
            }
            else if (!node->left)
            {
                auto temp = node;
                node = node->right;
                delete temp;
            }
            else if (!node->right)
            {
                auto temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                auto temp = findMax(node->left);
                node->key = temp->key;
                node->value = temp->value;
                node->left = remove(node->left, temp->key);
                node = balance(node);
            }
        }
        return node;
    }
    Node* findMax(Node *node) const
    {
        while (node->right)
            node = node->right;
        return node;
    }
    Node* rightRotate(Node *&node)
    {
        auto newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }
    Node* leftRotate(Node *&node)
    {
        auto newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }
    int height(Node *node) const
    {
        if (!node)
            return 0;
        return std::max(height(node->left), height(node->right)) + 1;
    }
    Node* balance(Node *&node)
    {
        int leftH = height(node->left);
        int rightH = height(node->right);
        if (leftH - rightH > 1)
        {
            if (height(node->left->left) >= height(node->left->right))
                node = rightRotate(node);
            else
            {
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }
        }
        else if (rightH - leftH > 1)
        {
            if (height(node->right->right) >= height(node->right->left))
                node = leftRotate(node);
            else
            {
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }
        }
        return node;
    }

    void insert(Node *&node, const Key &key, const Value &value) {
        if (!node) {
            node = new Node(key, value);
            return;
        }

        if (key < node->key)
            insert(node->left, key, value);
        else if (key > node->key)
            insert(node->right, key, value);

        node = balance(node);
    }
    Node *removeSubtree(Node *, const Key &);
    void clear(Node *node) {
        if (!node)
            return;
        clear(node->right);
        clear(node->left);
        delete node;
    }

public:
    AVLTree()
            : root(nullptr) {}
    void insert(const Key &, const Value &);
    void remove(const Key &);
    Value &operator[](const Key &);
    void clear()
    {
        clear(root);
        root = nullptr;
    }
};
template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::removeSubtree(AVLTree::Node *node, const Key &key)
{
    if (!node)
    {
        return node;
    }
    if (key < node->key)
    {
        node->left = removeSubtree(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = removeSubtree(node->right, key);
    }
    else
    {
        if (node->left)
            node->left = removeSubtree(node->left, key);
        if (node->right)
            node->right = removeSubtree(node->right, key);
        delete node;
        return nullptr;
    }
    return balance(node);
}
template<typename Key, typename Value>
Value &AVLTree<Key, Value>::operator[](const Key &key)
        {
    auto cur = root;
    while (cur)
    {
        if (key > cur->key)
            cur = cur->right;
        else if (key < cur->key)
            cur = cur->left;
        else
            return cur->value;
    }
    insert(root, key, Value());
    return operator[](key);
}
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key &key)
{
    remove(root, key);
    root = balance(root);
}
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const Key &key, const Value &value)
{
    insert(root, key, value);
}