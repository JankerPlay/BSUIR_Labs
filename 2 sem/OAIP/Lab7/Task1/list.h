#include <iostream>
#include <memory>
template <typename T>
class heap
{
private:
    struct Node
    {
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;
        T data;
        explicit Node(const T& value)
                : data(value),
                  next(nullptr),
                  prev(next) {}
        Node()
                : data(T()),
                  next(nullptr),
                  prev(next) {}
    };
    std::shared_ptr<Node> _begin;
    std::shared_ptr<Node> _end;
    size_t _size;
    void siftUp(std::shared_ptr<Node>);
    void siftDown(std::shared_ptr<Node>);
public:
    heap()
            : _begin(nullptr),
              _end(nullptr),
              _size(0) {}

    void insert(const T&);
    T& min();
    [[nodiscard]] size_t size() const;
};
template <typename T>
size_t heap<T>::size() const
{
    return _size;
}
template <typename T>
void heap<T>::siftUp(std::shared_ptr<Node> node)
{
    if (!(node->prev.lock()))
    {
        return;
    }
    if (node->data < node->prev.lock()->data)
    {
        auto prev = node->prev.lock();
        auto tmp = node->data;
        node->data = prev->data;
        prev->data = tmp;
        siftUp(node->prev.lock());
    }
}
template <typename T>
void heap<T>::siftDown(std::shared_ptr<Node> node)
{
    if (!node->next)
    {
        return;
    }
        auto child = node->next;
    if (child->next && child->next->data < child->data)
    {
        child = child->next;
    }
    if (child->data < node->data)
    {
        auto tmp = node->data;
        node->data = child->data;
        child->data = tmp;
        siftDown(child);
    }
}
template <typename T>
void heap<T>::insert(const T& value)
{
    auto newNode = std::make_shared<Node>(value);
    if (!_size)
    {
        _begin = _end = newNode;
    }
    else
    {
        _end->next = newNode;
        newNode->prev = _end;
        _end = newNode;
        siftUp(newNode);
    }
    _size++;
}
template <typename T>
T& heap<T>::min()
{
    if (!_size)
    {
        throw std::out_of_range("empty heap");
    }
    auto res = _begin->data;
    if (_begin == _end)
    {
        _begin.reset();
        _end = nullptr;
        _begin = nullptr;
    }
    else
    {
        _begin->data = _end->data;
        _end = _end->prev.lock();
        _end->next = nullptr;
        siftDown(_begin);
    }
    --_size;
    return res;
}