#include <bits/stdc++.h>
template<typename T, class Allocator = std::allocator<T>>
class deque
{
public:
    class deque_iterator
    {
    private:
        const deque<T>* ptr;
        size_t index;
    public:
        deque_iterator() : ptr(nullptr), index(0) {}
        deque_iterator(const deque_iterator &other)
        {
            ptr = other.ptr;
            index = other.index;
        }
        deque_iterator(deque_iterator &&other) noexcept
        {
            ptr = other.ptr;
            index = other.index;
            other.ptr = nullptr;
        }
        explicit deque_iterator(const deque* ptr, size_t ind)
        {
            this->ptr = ptr;
            index = ind;
        }
        deque_iterator &operator++()
        {
            index++;
            return *this;
        }
        deque_iterator &operator--()
        {
            index--;
            return *this;
        }
        bool operator<(const deque_iterator& other) const
        {
            return index < other.index;
        }
        bool operator>(const deque_iterator& other) const
        {
            return index > other.index;
        }
        bool operator!=(const deque_iterator& other) const
        {
            return index != other.index;
        }
        bool operator==(const deque_iterator& other) const
        {
            return index == other.index;
        }
        deque_iterator &operator=(const deque_iterator &other)
        {
            if (this != &other)
            {
                ptr = other.ptr;
                index = other.index;
            }
            return *this;
        }
        deque_iterator &operator=(deque_iterator &&other) noexcept
        {
            ptr = other.ptr;
            index = other.index;
            other.ptr = nullptr;
            return *this;
        }
        deque_iterator &operator+=(size_t n)
        {
            index += n;
            return *this;
        }
        deque_iterator &operator-=(size_t n)
        {
            index -= n;
            return *this;
        }
        deque_iterator operator+(size_t n) const
        {
            auto it = *this;
            it.index += n;
            return it;
        }
        deque_iterator operator-(size_t n) const
        {
            auto it = *this;
            it.index -= n;
            return it;
        }
        size_t operator-(const deque_iterator& n)
        {
            return index - n.index;
        }
        T& operator*()
        {
            return (*ptr)[index];
        }
        T* operator->()
        {
            return *ptr + index;
        }
    };
private:
    static const size_t N = 32;
    T **base;
    size_t _size;
    size_t _capacity;
    Allocator alloc;
    std::pair<size_t, size_t> _begin;
    std::pair<size_t, size_t> _end;
    [[nodiscard]] size_t iaFromID(size_t id) const
    {
        return (id + (_begin.second + _begin.first * N)) % (_capacity * N);
    }
    [[nodiscard]] size_t ibFromIA(size_t ia) const
    {
        return ia / N;
    }
    [[nodiscard]] size_t icFromIA(size_t ia) const
    {
        return ia % N;
    }
public:
    deque();
    void push_back(const T &);
    void push_front(const T &);
    void pop_back();
    void pop_front();
    T &operator[](size_t) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t capacity() const;
    deque_iterator begin() const;
    deque_iterator end() const;
    void clear();
    bool empty();
};
template<typename T, class Allocator>
bool deque<T, Allocator>::empty()
{
    return !_size;
}
template<typename T, class Allocator>
void deque<T, Allocator>::clear()
{
    for (size_t i = 0; i < _size; ++i)
    {
        deque::pop_back();
    }
    _size = 0;
}
template<typename T, class Allocator>
typename deque<T, Allocator>::deque_iterator deque<T, Allocator>::end() const
{
    return deque_iterator(this, _size);
}
template<typename T, class Allocator>
typename deque<T, Allocator>::deque_iterator deque<T, Allocator>::begin() const
{
    return deque_iterator(this, 0);
}
template<typename T, class Allocator>
void deque<T, Allocator>::push_front(const T &value)
{
    size_t beg = _begin.first;
    if (!_begin.second)
    {
        if (_begin.first)
        {
            beg--;
        }
        else
        {
            beg = _capacity - 1;
        }
    }
    if (beg == _end.first)
    {
        auto newBase = new T*[ !_capacity ? 0 : _capacity * 2 ]{ nullptr };
        size_t count = 0;
        for (size_t i = _begin.first; count < _capacity; ++i)
        {
            i %= _capacity;
            newBase[count] = base[i];
            count++;
        }
        delete[] base;
        base = newBase;
        _capacity *= 2;
        _begin.first = 0;
        _end.first = ibFromIA(iaFromID(_size));
        _end.second = icFromIA(iaFromID(_size));
    }
    if (_begin.second)
    {
        _begin.second--;
    }
    else
    {
        if (_begin.first)
        {
            _begin.first--;
        }
        else
        {
            _begin.first = _capacity - 1;
        }
        _begin.second = N - 1;
    }
    if (!base[_begin.first])
    {
        base[_begin.first] = alloc.allocate(N);
    }
    alloc.construct(base[_begin.first] + _begin.second, value);
    _size++;
}
template<typename T, class Allocator>
void deque<T, Allocator>::pop_front()
{
    if (_size) {
        alloc.destroy(base[_begin.first] + _begin.second);
        _begin.second++;
        if (_begin.second == N)
        {
            _begin.second = 0;
            _begin.first++;
            if (_begin.first == _capacity)
            {
                _begin.first = 0;
            }
        }
        _size--;
        if (!_size)
        {
            _end.first = _end.second = 0;
        }
    }
}
template<typename T, class Allocator>
void deque<T, Allocator>::pop_back()
{
    if (_size == 0)
    {
        throw std::out_of_range("deque is empty");
    }
    if (_end.second == 0)
    {
        _end.first--;
        if (_end.first == -1)
        {
            _end.first = _capacity - 1;
        }
        _end.second = N;
    }
    _end.second--;
    alloc.destroy(base[_end.first] + _end.second);
    _size--;
    if (_size == 0)
    {
        _begin = std::make_pair(0, 0);
        _end = std::make_pair(0, 0);
    }
}
template<typename T, class Allocator>
size_t deque<T, Allocator>::capacity() const
{
    return _capacity * N;
}
template<typename T, class Allocator>
size_t deque<T, Allocator>::size() const
{
    return _size;
}
template<typename T, class Allocator>
T &deque<T, Allocator>::operator[](size_t index) const
{
    return base[ibFromIA(iaFromID(index))][icFromIA(iaFromID(index))];
}
template<typename T, class Allocator>
void deque<T, Allocator>::push_back(const T &value)
{
    if (_end.second == N)
    {
        _end.first = (_end.first + 1) % _capacity;
        _end.second = 0;
    }
    if (!_size or _end.first == _begin.first)
    {
        if (_size == _capacity * N)
        {
            auto newBase = new T*[_capacity * 2]{ nullptr };
            size_t count = 0;
            for (size_t i = _begin.first; count < _capacity; ++i)
            {
                i %= _capacity;
                newBase[count] = base[i];
                count++;
            }
            delete[] base;
            base = newBase;
            _capacity *= 2;
            _begin.first = 0;
            _end.first = _size ? _capacity / 2 : 0;
        }
    }
    size_t ib = ibFromIA(iaFromID(_size));
    if (!base[ib])
    {
        base[ib] = alloc.allocate(N);
    }
    alloc.construct(base[ib] + icFromIA(iaFromID(_size)), value);
    _size++;
    _end.second++;
}
template<typename T, class Allocator>
deque<T, Allocator>::deque() : _size(0), _capacity(N)
{
    _begin = {0, 0};
    _end = {0, 0};
    base = new T *[N] { nullptr };
    base[0] = alloc.allocate(N);
}