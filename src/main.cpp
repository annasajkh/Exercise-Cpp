
#include "../include/ArrayList.h"
#include <iostream>
#include "../include/Array.h"

#define print(x) std::cout << x << std::endl

int main()
{
    ArrayList<int, 1> list;

    list.emplaceBack(1);
    list.emplaceBack(2);
    list.emplaceBack(3);
    list.emplaceBack(4);
    list.emplaceBack(5);
    list.emplaceBack(6);
    
    for (size_t i = 0; i < list.length; i++)
    {
        print(list[i]);
    }


    print("---------------------");

    for(int value : list)
    {
        print(value);
    }
    print("---------------------");

    Array<int, 2> array;
    array[0] = 0;
    array[1] = 1;

    for (size_t i = 0; i < array.size(); i++)
    {
        print(array[i]);
    }

    print("---------------------");

    for(int value : array)
    {
        print(value);
    }
}