#include <iostream>
#include <vector>
#include <algorithm>
template <typename T>
class Heap
{
private:
    std::vector<T> base;
    void siftUp(size_t i)
    {
        while (i > 0)
        {
            size_t parent = (i - 1) / 2;
            if (base[parent] < base[i])
            {
                std::swap(base[parent], base[i]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }
    void siftDown(size_t i)
    {
        size_t size = base.size();
        while (i < size)
        {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t largest = i;
            if (left < size && base[left] > base[largest])
            {
                largest = left;
            }
            if (right < size && base[right] > base[largest])
            {
                largest = right;
            }
            if (largest != i)
            {
                std::swap(base[i], base[largest]);
                i = largest;
            }
            else
            {
                break;
            }
        }
    }
public:
    Heap() = default;
    void insert(const T& value)
    {
        base.push_back(value);
        siftUp(base.size() - 1);
    }
    T& max()
    {
        if (base.empty())
        {
            throw std::runtime_error("empty heap");
        }
        T& res = base[0];
        base[0] = base.back();
        base.pop_back();
        siftDown(0);
        return res;
    }
    [[nodiscard]] size_t size() const
    {
        return base.size();
    }
    [[nodiscard]] bool empty() const
    {
        return base.empty();
    }
};