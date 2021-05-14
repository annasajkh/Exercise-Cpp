#pragma once

#include <cstring>
#include <iostream>

template<typename ArrayList>
class ArrayListIterator
{
public:
    using ValueType = typename ArrayList::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
private:
    PointerType pointer;
public:
    ArrayListIterator(PointerType pointer)
        : pointer(pointer)
    {

    }

    ArrayListIterator& operator++()
    {
        pointer++;
        return *this;
    }

    ArrayListIterator operator++(int)
    {
        ArrayListIterator iterator = *this;
        ++(*this);
        return iterator;
    }

     ArrayListIterator& operator--()
    {
        pointer--;
        return *this;
    }

    ArrayListIterator operator--(int)
    {
        ArrayListIterator iterator = *this;
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

    bool operator==(const ArrayListIterator& other) const
    {
        return pointer == other.pointer;
    }

    bool operator!=(const ArrayListIterator& other) const
    {
        return !(*this == other);
    }
};



template<typename T, size_t initalSize = 5>
class ArrayList
{
private:
    T* data;
    size_t dataSize;
public:
    using ValueType = T;
    using Iterator = ArrayListIterator<ArrayList<T>>;
public:
    size_t length;

    ArrayList()
    {
        data = new T[initalSize];
        length = 0;
        dataSize = initalSize;
    }

    size_t size() const
    {
        return length;
    }

    void outOfBounds(const size_t& index)
    {
        if(index > length - 1 || index < 0)
        {
            throw std::out_of_range("out of bounds");
        }
    }

    T& operator[](const size_t& index)
    {
        outOfBounds(index);
        return data[index];
    }


    void pop()
    {
        if(length > 0)
        {
            length--;
            data[length].~T();
        }
    }

    void swap(const size_t& a, const size_t& b)
    {
        outOfBounds(a);
        outOfBounds(b);

        T temp = data[a];

        data[a] = data[b];
        data[b] = temp;
    }

    void clear()
    {
        for (size_t i = 0; i < length; i++)
        {
            data[i].~T();
        }
        length = 0;
        
    }

    void reverse()
    {
        for (size_t i = 0; i < length / 2; i++)
        {
            swap(i, length - 1 - i);
        }
    }

    void insert(const size_t& index, const T& element)
    {
        if(index == length)
        {
            push(element);
            return;
        }

        outOfBounds(index);

        length++;

        if(length > dataSize)
        {
            reAlloc(length + length / 2);
        }

        for (size_t i = length; i > index; i--)
        {
            data[i] = std::move(data[i - 1]);
        }

        data[index] = element;

    }

    void insert(const size_t& index, const T&& element)
    {
        if(index == length)
        {
            push(element);
            return;
        }

        outOfBounds(index);


        length++;

        if(length> dataSize)
        {
            reAlloc(length + length / 2);
        }

        for (size_t i = length; i > index; i--)
        {
            data[i] = std::move(data[i - 1]);
        }

        data[index] = std::move(element);

    }
    
    void remove(const size_t& index)
    {    
        outOfBounds(index);

        if(index == length - 1)
        {
            pop();
            return;
        }

        for (size_t i = index; i < length; i++)
        {
            data[i] = std::move(data[i + 1]);
        }
        

        length--;
    }

    void push(const T& element)
    {
        length++;
        if(length > dataSize)
        {
            reAlloc(length + length / 2);
        }

        data[length - 1] = element;
    }

    void push(const T&& element)
    {
        length++;

        if(length > dataSize)
        {
            reAlloc(length + length / 2);
        }

        data[length - 1] = std::move(element);
    }

    template<typename... Args>
    T& emplaceBack(Args&&... args)
    {
        length++;

        if(length > dataSize)
        {
            reAlloc(length + length / 2);
        }

        data[length - 1] = T(std::forward<Args>(args)...);
        return data[length];
    }

    void reAlloc(size_t newSize)
    {
        T* newData = (T*)::operator new(newSize * sizeof(T));

        for (size_t i = 0; i < length - 1; i++)
        {
            new(&newData[i]) T(std::move(data[i]));
        }

        for (size_t i = 0; i < length - 1; i++)
        {
            data[i].~T();
        }

        ::operator delete(data, dataSize * sizeof(T));
        data = newData;
    }

    Iterator begin()
    {
        return Iterator(data);
    }

    Iterator end()
    {
        return Iterator(data + length);
    }

    ~ArrayList()
    {
        clear();
        ::operator delete(data, dataSize * sizeof(T));
    }

};