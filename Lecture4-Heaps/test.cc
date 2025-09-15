

/**
 *  * this code write by fengchengyu in 09/15/2025 for review
 */


 
#include "stl_priority_queue.hpp"
#include <iostream>

void test1() {
    fengchengyu_stl::priority_queue<int> pq;
    pq.push(5);
    pq.push(3);
    pq.push(2);
    pq.push(10);
    pq.push(1);
    pq.push(0);
    while (!pq.empty())
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";   
}

void test2()
{
    // build min-heap
    fengchengyu_stl::priority_queue<int, std::vector<int>, std::greater<int>> pq = {1, 10, 2, 9, 8, 3, 5, 9, 6, 4};
    while (!pq.empty())
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";
}

bool myfunction (int i,int j) { return (i<j); }
void test3()
{
    // Note the difference between sort(), which input a function object and priority_queue which input a class.
    std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    struct myclass
    {
        bool operator()(int i, int j) { return (i < j); }
    };
    std::sort(arr.begin(), arr.end(), myclass());
    std::sort(arr.begin(), arr.end(), myfunction);
    // What sort wants is a function object, not a functor (a functor is a class that can be called like a function)
    // So after the class is overloaded (), the class name ()--> is a function object
}

int main() {
    test3();
    return 0;
}