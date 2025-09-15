
/**
 * https://github.com/ffengc/rookie-cplusplus/edit/master/stl_priority_queue/stl_priority_queue.hpp: 2024 version
 * this version write by fengchengyu in 09/15/2025 for review
 */

#ifndef __fengcheng_yu_stl_priority_queue__
#define __fengcheng_yu_stl_priority_queue__

#include <vector>
#include <deque>
#include <algorithm>

namespace fengchengyu_stl
{
    template <class T, class Container = std::deque<T>, class Compare = std::less<T>>
    /**
     * T: the data type
     * Container: the adapter, the array
     * Compare: the compare functor
     * note: in stl, default pq is the max-heap, which use the std::less
     *          build min-heap: std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
     */
    class priority_queue
    {
    private:
        Container __con; //
    private:
        template <class iter_type>
        void __initialize_by_iterator(iter_type first, iter_type last)
        {
            // use down adjust to build the heap -> can do it in O(n)
            while (first != last)
                __con.push_back(*first++);
            for (int i = (__con.size() - 1 - 1) / 2; i >= 0; i--)
                // sz-1 represents the last leaf node
                // -> (sz-1-1)/2 represents the last leaf node's parent
                __adjust_down(i); // call heapify
        } //
    public:
        // constructors
        priority_queue() {} // default constructor
        template <class iter_type>
        priority_queue(iter_type first, iter_type last) { __initialize_by_iterator(first, last); }
        priority_queue(const std::initializer_list<T> &lst) { __initialize_by_iterator(lst.begin(), lst.end()); } //
    private:
        // adjust up and adjust down (heapify)
        void __adjust_up(std::size_t child)
        {
            Compare com;
            std::size_t parent = (child - 1) / 2; // parent index
            while (child > 0)
            {
                if (com(__con[parent], __con[child]))
                {
                    std::swap(__con[child], __con[parent]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                    break; // adjust up done
            }
        }
        void __adjust_down(std::size_t parent)
        {
            Compare com;
            std::size_t child = parent * 2 + 1;
            while (child < __con.size())
            {
                // find the bigger child to go up (max heap)
                if (child + 1 < __con.size() && com(__con[child], __con[child + 1]))
                    ++child; // select right child
                if (com(__con[parent], __con[child]))
                {
                    std::swap(__con[child], __con[parent]);
                    parent = child;
                    child = parent * 2 + 1;
                }
                else
                    break;
            }
        } //
    public:
        void push(const T &x)
        {
            __con.push_back(x);
            __adjust_up(__con.size() - 1);
        }
        void pop()
        {
            std::swap(__con[0], __con[__con.size() - 1]);
            __con.pop_back();
            __adjust_down(0);
        }
        const T &top() const { return __con[0]; }
        bool empty() const { return __con.empty(); }
        std::size_t size() const { return __con.size(); }
    };
} // namespace fengchengyu_stl

#endif