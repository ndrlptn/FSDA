
#include "Sort_and_search.h"
#include <iostream>

int main()
{
    int a[] = { 25, 57, 48, 37, 12 ,92, 86, 33 };
    twoWayInsertSort(a);
    for (int i = 0; i < 8; ++i)
        std::cout << a[i] << ", ";
}

