#pragma once

#include <cstring>

template<typename Array>
class ArrayIterator
{
public:
    using ValueType = typename Array::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
private:
    PointerType pointer;
public:
    ArrayIterator(PointerType pointer)
        : pointer(pointer)
    {

    }

    ArrayIterator& operator++()
    {
        pointer++;
        return *this;
    }

    ArrayIterator operator++(int)
    {
        ArrayIterator iterator = *this;
        ++(*this);
        return iterator;
    }

     ArrayIterator& operator--()
    {
        pointer--;
        return *this;
    }

    ArrayIterator operator--(int)
    {
        ArrayIterator iterator = *this;
        --(*this);
        return iterator;
    }

    ReferenceType operator[](size_t index)
    {
        return *(pointer + index);
    }

    PointerType operator->()
    {
        return pointer;
    }

    ReferenceType operator*()
    {
        return *pointer;
    }

    bool operator==(const ArrayIterator& other) const
    {
        return pointer == other.pointer;
    }

    bool operator!=(const ArrayIterator& other) const
    {
        return !(*this == other);
    }
};



template<typename T, size_t tSize>
class Array
{
private:
    T mData[tSize];

public:
    using ValueType = T;
    using Iterator = ArrayIterator<Array<T, tSize>>;
public:
    Array()
    {

    }

    constexpr size_t size()
    {
        return tSize;
    }

    T& operator[](size_t index)
    {
        return mData[index];
    }

    const T& operator[](size_t index) const
    {
        return mData[index];
    }

    T* data()
    {
        return mData;
    }

    const T* data() const
    {
        return mData;
    }

    Iterator begin()
    {
        return Iterator(mData);
    }

    Iterator end()
    {
        return Iterator(mData + tSize);
    }
};