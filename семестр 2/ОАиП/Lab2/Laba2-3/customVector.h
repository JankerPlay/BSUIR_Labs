#pragma once
#include "bibl.h"
template <typename DT>
class CV {
private:
    DT* arr;
    ll capacity;
    ll length;
public:
    explicit CV(ll = 50);
   ll push_back(DT);
    DT pop_back();
    ll size() const;
    DT& operator[](ll);
};
template <typename DT>
CV<DT>::CV(ll n) : capacity(n), arr(new DT[n]), length(0)
{
}
template <typename DT>
ll CV<DT>::push_back(DT data)
{
    if (length == capacity) {
        DT* old = arr;
        arr = new DT[capacity = capacity * 2];
        copy(old, old + length, arr);
        delete[] old;
    }
    arr[length++] = data;
    return length;
}
template <typename DT>
ll CV<DT>::size() const
{
    return length;
}
template <typename DT>
DT& CV<DT>::operator[](ll index)
{
    if (index >= length)
    {
        exit(0);
    }
    return *(arr + index);
}
template <typename DT>
DT CV<DT>::pop_back()
{
    return arr[length-- - 1];
}
