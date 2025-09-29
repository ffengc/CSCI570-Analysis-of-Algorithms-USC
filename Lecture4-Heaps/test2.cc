

/**
 *  * this code write by fengchengyu in 09/15/2025 for homework4 question1
 */

#include "medianHeap.hpp"
#include <iostream>

void test1()
{
    fengchengyu::median_heap midHeap = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    std::cout << midHeap.find_median() << std::endl;
    midHeap.extract_median();
    std::cout << midHeap.find_median() << std::endl;
    midHeap.extract_median();
    std::cout << midHeap.find_median() << std::endl;
    midHeap.insert(100);
    std::cout << midHeap.find_median() << std::endl;
    midHeap.insert(0);
    std::cout << midHeap.find_median() << std::endl;
}

int main()
{
    test1();
    return 0;
}