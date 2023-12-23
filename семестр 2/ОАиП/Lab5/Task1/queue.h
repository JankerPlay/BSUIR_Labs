#pragma once
#include <iostream>
#include <memory>
using namespace std;
template<typename T>
class queue
{
private:
    struct Node
    {
        shared_ptr<Node> next;
        weak_ptr<Node> prev;
        T data;
        explicit Node(const T& value) : data(value), next(nullptr), prev() {}
        Node() : next(nullptr), prev(), data() {}
        ~Node() = default;
    };
public:
    shared_ptr<Node> _begin;
    queue(const queue& other);
    queue(queue&& other) noexcept;
    queue& operator=(const queue& other);
    queue& operator=(queue&& other) noexcept;
    [[nodiscard]] size_t size() const;
    void push(const T& value);
    void pop();
    T& back();
    T& front();
    bool empty() const;
    void swap(queue &other);
    void clear();
    template<typename... Args>
    void emplace(Args&&... args);
    void removeDuplicates();
    queue() : _size(0)
    {
        _begin = make_shared<Node>();
        _end = _begin;
    }

    size_t _size;
    shared_ptr<Node> _end;
};
template<typename T>
void queue<T>::removeDuplicates()
{
    if (_size < 2)
        return;
    shared_ptr<Node> current = _begin;
    while (current != nullptr && current->next != nullptr)
    {
        shared_ptr<Node> runner = current;
        while (runner->next != nullptr)
        {
            if (runner->next->data == current->data)
            {
                runner->next = runner->next->next;
                _size--;
            }
            else
                runner = runner->next;
        }
        current = current->next;
    }
}
template<typename T>
template<typename... Args>
void queue<T>::emplace(Args &&...args)
{
    push(T(forward<Args>(args)...));
}
template<typename T>
queue<T>& queue<T>::operator=(queue&& other) noexcept
{
    clear();
    _begin = move(other._begin);
    _end = move(other._end);
    _size = other._size;
    other._size = 0;
    return *this;
}
template<typename T>
void queue<T>::clear()
{
    if (_size) {
        _begin.reset();
        _end.reset();
        _begin = make_shared<Node>();
        _end = _begin;
        _size = 0;
    }
}
template<typename T>
queue<T>& queue<T>::operator=(const queue& other)
{
    if (this == &other)
        return *this;
    clear();
    _size = 0;
    _begin = std::make_shared<Node>();
    _end = _begin;
    auto it(other._begin);
    for (size_t i = 0; i < other._size; ++i)
    {
        emplace(it->data);
        it = it->next;
    }
    return *this;
}
template<typename T>
void queue<T>::swap(queue &other)
{
    swap(_end, other._end);
    swap(_begin, other._begin);
    swap(_size, other._size);
}
template<typename T>
bool queue<T>::empty() const
{
    return _size == 0;
}
template<typename T>
        T& queue<T>::front()
{
    return _begin->data;
}
template<typename T>
T& queue<T>::back()
{
    return _end->prev.lock()->data;
}
template<typename T>
void queue<T>::pop()
{
    if (_size > 1) {
        _begin = _begin->next;
        _begin->prev.reset();
        _size--;
    } else if (_size == 1) {
        _begin.reset();
        _end.reset();
        _size--;
    }
}
template<typename T>
void queue<T>::push(const T &value)
{
    if (_size)
    {
        auto newNode = std::make_shared<Node>(value);
        newNode->data = value;
        newNode->prev = _end;
        _end->next = newNode;
        _end = newNode;
    }
    else
    {
        _begin = std::make_shared<Node>(value);
        _begin->data = value;
        _end = _begin;
    }
    _size++;
}
template<typename T>
queue<T>::queue(queue&& other) noexcept : _size(other._size), _begin(std::move(other._begin)), _end(std::move(other._end))
{
    other._size = 0;
}
template<typename T>
size_t queue<T>::size() const
{
    return _size;
}
template<typename T>
queue<T>::queue(const queue& other)
{
    _size = 0;
    _begin = std::make_shared<Node>();
    _end = _begin;
    auto it = other._begin;
    for (size_t i = 0; i < other._size; ++i)
    {
        emplace(it->data);
        it = it->next;
    }
    _size = other._size;
}