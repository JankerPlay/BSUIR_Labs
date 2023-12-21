#include <QString>
#include <QVector>
#include <bits/stdc++.h>
template<class T>
class stack
        {
private:
    struct Node
            {
        Node *_next;
        T _data;
        Node() : _next(nullptr), _data(T()) {}
        explicit Node(const T &data) : _data(data), _next(nullptr) {}
    };
    size_t _size;
    Node *_top;
public:
    stack() : _size(0), _top(new Node()) {}
    stack(const stack &other)
    {
        if (!other._top)
        {
            _top = nullptr;
            _size = 0;
        }
        else
        {
            auto tmp = other._top;
            auto tmp2 = new Node(tmp->_data);
            tmp = tmp->_next;
            _top = tmp2;
            _size = other._size;
            while (tmp)
            {
                tmp2->_next = new Node();
                tmp2 = tmp2->_next;
                tmp2->_data = tmp->_data;
                tmp = tmp->_next;
            }
            tmp2->_next = nullptr;
        }
    }
    stack &operator=(const stack &other)
    {
        if (this != &other)
        {
            clear();
            delete _top;
            if (!other._top)
            {
                _top = nullptr;
                _size = 0;
            }
            else
            {
                auto tmp = other._top;
                auto tmp2 = new Node(tmp->_data);
                tmp = tmp->_next;
                _top = tmp2;
                _size = other._size;
                while (tmp)
                {
                    tmp2->_next = new Node();
                    tmp2 = tmp2->_next;
                    tmp2->_data = tmp->_data;
                    tmp = tmp->_next;
                }
                tmp2->_next = nullptr;
            }
        }
        return *this;
    }
    ~stack()
    {
        Node *tmp = _top;
        for (int i = 0; i < _size; ++i)
        {
            Node *buf = tmp->_next;
            delete tmp;
            tmp = buf;
        }
    }
    void push(const T &newElement)
    {
        auto newEl = new Node(newElement);
        if (_size > 0)
        {
            newEl->_next = _top;
            _top = newEl;
        }
        else
        {
            newEl->_next = nullptr;
            _top = newEl;
        }
        _size++;
    }
    T &top()
    {
        if (_top)
            return _top->_data;
        else
        {
            _top = new Node();
            return _top->_data;
        }
    }
    T pop()
    {
        if (_size)
        {
            auto rem = _top->_data;
            Node *tmp = _top->_next;
            delete _top;
            _top = tmp;
            _size--;
            return rem;
        } else
            return T();
    }
    [[nodiscard]] bool empty() const
    {
        return !_size;
    }
    void clear()
    {
        while (_size)
        {
            pop();
        }
        _top = new Node();
    }
};
template<typename Key, typename Value, size_t K = 2048>
class HTable
{
protected:
    stack<std::pair<Key, Value>> *base;
    size_t _size;
    size_t hash(const Key &);
    bool contains(stack<std::pair<Key, Value>> &, const Key &);
    void replace(stack<std::pair<Key, Value>> &, const Key &, const Value &);
    Value &get(stack<std::pair<Key, Value>> &, const Key &);
    void erase(stack<std::pair<Key, Value>> &, const Key &);
public:
    HTable() : base(new stack<std::pair<Key, Value>>[K]{}),  _size(0) {}
    ~HTable();
    void clear();
    HTable &operator=(const HTable &);
    HTable &operator=(HTable &&) noexcept;
    void insert(const Key &, const Value &);
    void erase(const Key &);
    Value &operator[](const Key &);
};
template<typename Key, typename Value, size_t K>
bool HTable<Key, Value, K>::contains(stack<std::pair<Key, Value>> &st, const Key &key)
{
    stack<std::pair<Key, Value>> tmp;
    while (!st.empty())
    {
        if (st.top().first == key)
        {
            while (!tmp.empty())
            {
                st.push(tmp.pop());
            }
            return true;
        }
        tmp.push(st.pop());
    }
    while (!tmp.empty())
        st.push(tmp.pop());
    return false;
}
template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::replace(stack<std::pair<Key, Value>> &st, const Key &key, const Value &value)
{
    stack<std::pair<Key, Value>> tmp;
    while (!st.empty())
    {
        if (st.top().first == key)
        {
            st.top().second = value;
            while (!tmp.empty())
                st.push(tmp.pop());
            return;
        }
        tmp.push(st.pop());
    }
    while (!tmp.empty())
        st.push(tmp.pop());
}
template<typename Key, typename Value, size_t K>
Value &HTable<Key, Value, K>::get(stack<std::pair<Key, Value>> &st, const Key &key)
{
    stack<std::pair<Key, Value>> tmp;
    while (!st.empty())
    {
        if (st.top().first == key)
        {
            auto& r = st.top().second;
            while (!tmp.empty())
                st.push(tmp.pop());
            return r;
        }
        tmp.push(st.pop());
    }
    while (!tmp.empty())
        st.push(tmp.pop());
    st.push(std::make_pair(key, Value()));
    return st.top().second;
}
template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::erase(stack<std::pair<Key, Value>> &st, const Key &key)
{
    stack<std::pair<Key, Value>> tmp;
    while (!st.empty())
    {
        if (st.top().first == key)
        {
            st.pop();
            break;
        }
        tmp.push(st.pop());
    }
    while (!tmp.empty())
        st.push(tmp.pop());
}
template<typename Key, typename Value, size_t K>
HTable<Key, Value, K>::~HTable()
{
    delete[] base;
}
template<typename Key, typename Value, size_t K>
HTable<Key, Value, K> &HTable<Key, Value, K>::operator=(HTable &&other) noexcept
{
    delete[] base;
    base = other.base;
    _size = other._size;
    other.base = nullptr;
    other._size = 0;
}
template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::clear()
{
    for (size_t i = 0; i < K; ++i)
        base[i].clear();
    _size = 0;
}
template<typename Key, typename Value, size_t K>
HTable<Key, Value, K> &HTable<Key, Value, K>::operator=(const HTable &other)
{
    if (this != &other)
    {
        delete[] base;
        base = reinterpret_cast<stack<std::pair<Key, Value>>*>(new int8_t*[K * sizeof(stack<std::pair<Key, Value>>) * other._size]);
        for (size_t i = 0; i < other._size; ++i)
            new (base + i) stack<std::pair<Key, Value>>(other.base[i]);
        _size = other._size;
    }
    return *this;
}
template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::erase(const Key &key)
{
    erase(base[hash(key)], key);
}
template<typename Key, typename Value, size_t K>
Value &HTable<Key, Value, K>::operator[](const Key &key)
{
    return get(base[hash(key)], key);
}
template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::insert(const Key &key, const Value &value)
{
    size_t i = hash(key);
    if (contains(base[i], key))
        replace(base[i], key, value);
    else
    {
        base[i].push(std::make_pair(key, value));
        ++_size;
    }
}
template<typename Key, typename Value, size_t K>
size_t HTable<Key, Value, K>::hash(const Key &key)
{
    return static_cast<size_t>(key * 13 / 3) % K;
}
class Solve : public HTable<int, int, 15>
{
private:
    static constexpr size_t K = 15;
public:
    Solve() = default;
    void CreateRandom(int min, int max);
    QVector<QString> Stacks();
    void RemoveNegative();
};
void Solve::CreateRandom(int min, int max)
{
    srand(time(nullptr));
    for (int i = 0; i < 500; ++i)
    {
        int r = rand() % ((max - min) + 1) + min;
        insert(r, 0);
    }
}
QVector<QString> Solve::Stacks()
{
    QVector<QString> stacks;
    for (size_t i = 0; i < K; ++i)
    {
        QString buf;
        auto tmp = base[i];
        while (!tmp.empty())
            buf.append(QString::number(tmp.pop().first) + " ");
        stacks.push_back(buf);
    }
    return stacks;
}
void Solve::RemoveNegative()
{
    for (int i = -100; i < 0; ++i)
        erase(i);
}