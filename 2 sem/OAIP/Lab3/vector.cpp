#include "iterator.cpp"
#include <iostream>
template<typename T>
class vector {
private:
    T* _arr;
    size_t _size;
    size_t _capacity;
public:
    vector();
    ~vector();
    vector(it::iterator<T>, it::iterator<T>);
    vector(const vector&);
    vector(std::initializer_list<T>);
    vector& operator=(const vector&);
    void push_back(const T&);
    void pop_back();
    size_t size() const;
    void reserve(int);
    void resize(int, const T & = T());
    void erase(it::iterator<T>);
    void erase(it::iterator<T>, it::iterator<T>);
    void insert(it::iterator<T>, const T& value);
    template<typename InputIterator>
    void insert(const it::iterator<T>&, InputIterator, InputIterator);
    size_t max_size() const;
    void assign(size_t, const T&);
    template<class... Args>
    void emplace(it::iterator<T>, Args &&...);
    template<class... Args>
    void emplace_back(Args &&...);
    void clear();
    size_t capacity() const;
    void swap(const vector<T>&);
    T& back();
    T* data();
    T& front();
    bool empty() const;
    it::iterator<T> begin() const;
    it::iterator<T> end() const;
    it::reverse_iterator<T> rbegin() const;
    it::reverse_iterator<T> rend() const;
    it::const_iterator<T> cbegin() const;
    it::const_iterator<T> cend() const;
    T& operator[](int);
    const T& operator[](int) const;
    T& at(int) const;
};
template<typename T>
it::reverse_iterator<T> vector<T>::rbegin() const
{
    return it::reverse_iterator<T>(_arr + _size - 1);
}
template<typename T>
it::reverse_iterator<T> vector<T>::rend() const
{
    return it::reverse_iterator<T>(_arr - 1);
}
template<typename T>
void vector<T>::swap(const vector<T>& other)
{
    T* temp_arr = _arr;
    _arr = other._arr;
    other._arr = temp_arr;
    size_t temp_size = _size;
    _size = other._size;
    other._size = temp_size;
    size_t temp_capacity = _capacity;
    _capacity = other._capacity;
    other._capacity = temp_capacity;
}
template<typename T>
void vector<T>::insert(it::iterator<T> _pos, const T& value)
{
    it::iterator<T> it = vector::begin();
    size_t ind = 0;
    while (it != _pos)
    {
        ind++;
        it++;
    }
    if (_capacity <= _size + 1)
    {
        size_t new_capacity = _capacity * 2;
        T* new_arr = new T[new_capacity];
        for (size_t i = 0; i < _size; ++i)
        {
            new (&new_arr[i]) T(_arr[i]);
            _arr[i].~T();
        }
        delete[] _arr;
        _arr = new_arr;
        _capacity = new_capacity;
    }
    it = vector::begin();
    for (int i = 0; i < ind; ++i)
    {
        it++;
    }
    size_t i;
    try
    {
        for (i = _size; i > ind; --i)
        {
            new (&_arr[i]) T(_arr[i - 1]);
            (_arr + i - 1)->~T();
        }
        new (&*it) T(value);
        _size++;
    }
    catch (...)
    {
        vector::clear();
        throw;
    }
}
template<typename T>
template<typename InputIterator>
void vector<T>::insert(const it::iterator<T>& _pos, InputIterator _other_beg, InputIterator _other_end) {
    auto other = _other_beg;
    size_t count = 0;
    while (other != _other_end) {
        other++;
        count++;
    }
    it::iterator<T> it = vector::begin();
    size_t ind = 0;
    while (it != _pos) {
        ind++;
        it++;
    }
    if (_size + count >= _capacity) {
        size_t new_capacity = _capacity * 2;
        T* new_arr = new T[new_capacity];
        for (size_t i = 0; i < ind; ++i) {
            new (&new_arr[i]) T(_arr[i]);
            _arr[i].~T();
        }
        for (size_t i = 0; other != _other_end; ++i) {
            new (&new_arr[ind + i]) T(*(other++));
        }
        for (size_t i = ind; i < _size; ++i) {
            new (&new_arr[count + i]) T(_arr[i]);
            _arr[i].~T();
        }
        delete[] _arr;
        _arr = new_arr;
        _capacity = new_capacity;
    }
    else {
        for (size_t i = _size - 1 + count; i > ind; --i) {
            new (&_arr[i]) T(_arr[i - count]);
            (_arr + i - count)->~T();
        }
        other = _other_beg;
        for (size_t i = ind; other != _other_end; ++i) {
            new (_arr + i) T(*(other++));
        }
    }
    _size += count;
}
template<typename T>
bool vector<T>::empty() const {
    return _size == 0;
}
template<typename T>
T& vector<T>::front() {
    return *vector::begin();
}
template<typename T>
template<typename... Args>
void vector<T>::emplace_back(Args &&...args) {
    T newObj(args...);
    vector::push_back(newObj);
}
template<typename T>
vector<T>::vector() {
    _arr = static_cast<T*>(operator new(sizeof(T)));
    _capacity = 1;
    _size = 0;
}
template<typename T>
vector<T>::~vector() {
    if (_arr) {
        for (size_t i = 0; i < _size; ++i) {
            (_arr + i)->~T();
        }
        operator delete(_arr);
    }
    _arr = nullptr;
    _size = _capacity = 0;
}
template<typename T>
vector<T>::vector(it::iterator<T> _beg, it::iterator<T> _end) {
    _size = 0;
    _capacity = 0;
    auto it = _beg;
    while (it != _end) {
        vector::push_back(*it);
        it++;
    }
}
template<typename T>
vector<T>::vector(const vector& other) {
    if (this != &other) {
        _arr = reinterpret_cast<T*>(new int8_t[other._capacity * sizeof(T)]);
        if (_arr) {
            _size = 0;
            _capacity = other._capacity;
            try {
                for (int i = 0; i < other._size; ++i) {
                    new (_arr + i) T(other._arr[i]);
                }
                _size = other._size;
            }
            catch (...) {
                vector::clear();
                throw;
            }
        }
        else {
            throw std::bad_alloc();
        }
    }
}
template<typename T>
vector<T>::vector(std::initializer_list<T> vec)
    : _size(0), _capacity(0)
{
    reserve(vec.size());
    for (const auto& elem : vec) {
        emplace_back(elem);
    }
}
template<typename T>
vector<T>& vector<T>::operator=(const vector& other) {
    if (this != &other) {
        vector<T> temp(other);
        T* temp_arr = temp._arr;
        temp._arr = _arr;
        _arr = temp_arr;

        size_t temp_size = temp._size;
        temp._size = _size;
        _size = temp_size;

        size_t temp_capacity = temp._capacity;
        temp._capacity = _capacity;
        _capacity = temp_capacity;
    }
    return *this;
}
template<typename T>
void vector<T>::push_back(const T& value) {
    if (_size >= _capacity) {
        reserve(2 * _capacity);
    }
    ::new (static_cast<void*>(_arr + _size)) T(value);
    ++_size;
}
template<typename T>
void vector<T>::pop_back() {
    if (_size == 0) {
        return;
    }
    --_size;
    _arr[_size].~T();
}
template<typename T>
[[nodiscard]] size_t vector<T>::size() const {
    return _size;
}
template<typename T>
void vector<T>::reserve(int n) {
    if (n <= _capacity) {
        return;
    }
    T* new_arr = static_cast<T*>(::operator new[](n * sizeof(T)));
    int i;
    try {
        for (i = 0; i < _size; ++i) {
            ::new (new_arr + i) T(_arr[i]);
        }
    }
    catch (...) {
        for (int j = 0; j < i; ++j) {
            (new_arr + j)->~T();
        }
        ::operator delete[](new_arr);
        throw;
    }
    ::operator delete[](_arr);
    _arr = new_arr;
    _capacity = n;
}
template<typename T>
void vector<T>::resize(int n, const T& value) {
    if (n < _size) {
        for (int i = n; i < _size; ++i) {
            (_arr + i)->~T();
        }
        _size = n;
    }
    else if (n > _size) {
        if (n <= _capacity) {
            for (int i = _size; i < n; ++i) {
                ::new (_arr + i) T(value);
            }
            _size = n;
        }
        else {
            vector new_vec(n, value);
            swap(new_vec);
        }
    }
}
template<typename T>
void vector<T>::erase(it::iterator<T> _iter) {
    size_t ind = 0;
    for (auto it = begin(); it != _iter && ind < _size; ++it) {
        ind++;
    }
    try {
        for (size_t i = ind + 1; i < _size; ++i) {
            new (_arr + i - 1) T(_arr[i]);
            (_arr + i)->~T();
        }
        _size--;
    } catch (...) {
        vector::clear();
        throw;
    }
}
template<typename T>
void vector<T>::erase(it::iterator<T> begin, it::iterator<T> end) {
    size_t count = end - begin;
    size_t ind = begin - vector::begin();
    for (size_t i = ind; i < _size; ++i) {
        _arr[i - count] = std::move(_arr[i]);
    }
    for (size_t i = _size - count; i < _size; ++i) {
        _arr[i].~T();
    }
    _size -= count;
}
template<typename T>
[[nodiscard]] size_t vector<T>::max_size() const {
    return LLONG_MAX;
}
template<typename T>
void vector<T>::assign(size_t count, const T& value) {
    clear();
    for (int i = 0; i < count; ++i) {
        push_back(value);
    }
}
template<typename T>
template<typename... Args>
void vector<T>::emplace(it::iterator<T> pos, Args &&...args) {
    pos.get_pointer()->~T();
    new (pos.get_pointer()) T(args...);
}
template<typename T>
void vector<T>::clear() {
    for (int i = 0; i < _size; ++i) {
        (_arr + i)->~T();
    }
    _size = 0;
}
template<typename T>
size_t vector<T>::capacity() const{
    return _capacity;
}
template<typename T>
T& vector<T>::back() {
    return _arr[_size - 1];
}
template<typename T>
T* vector<T>::data() {
    return &_arr[0];
}
template<typename T>
it::iterator<T> vector<T>::begin() const {
    return it::iterator(_arr);
}
template<typename T>
it::iterator<T> vector<T>::end() const {
    return it::iterator(_arr + _size);
}
template<typename T>
it::const_iterator<T> vector<T>::cbegin() const {
    return it::const_iterator(_arr);
}
template<typename T>
it::const_iterator<T> vector<T>::cend() const {
    return it::const_iterator(_arr + _size);
}
template<typename T>
T& vector<T>::operator[](int index) {
    return _arr[index];
}
template<typename T>
const T& vector<T>::operator[](int index) const {
    return _arr[index];
}
template<typename T>
T& vector<T>::at(int index) const {
    if (index >= _size)
        throw std::out_of_range("index out of range");
    return _arr[index];
}
