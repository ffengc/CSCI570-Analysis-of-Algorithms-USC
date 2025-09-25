

/**
 * write by fengchengyu in 09/25/2025 for homework4 question1
 */
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace fengchengyu
{
    class median_heap
    {
    private:
        // min-heap: stores larger half
        std::priority_queue<int, std::deque<int>, std::greater<int>> __up_heap; // min heap
        // max-heap: stores smaller half
        std::priority_queue<int> __down_heap; // max heap
        // balance the sizes of two heaps
        void __rebalance()
        {
            if (__down_heap.size() > __up_heap.size() + 1)
            {
                __up_heap.push(__down_heap.top());
                __down_heap.pop();
            }
            else if (__up_heap.size() > __down_heap.size() + 1)
            {
                __down_heap.push(__up_heap.top());
                __up_heap.pop();
            }
        }

    public:
        // default constructor
        median_heap() {}
        // constructor from vector, using O(n) build
        median_heap(const std::initializer_list<int> &nums)
        {
            if (nums.size() == 0)
                return;
            // find med in O(n)
            std::vector<int> copy(nums);
            std::nth_element(copy.begin(), copy.begin() + copy.size() / 2, copy.end());
            int med = copy[copy.size() / 2];
            // partition into two arrays
            std::vector<int> left, right;
            left.reserve(nums.size());
            right.reserve(nums.size());
            for (int x : nums)
            {
                if (x <= med)
                    left.push_back(x);
                else
                    right.push_back(x);
            }
            // build max-heap for left, min-heap for right in O(n)
            // tips: we cannot use the push of the heap, which may lead to O(nlogn)
            std::make_heap(left.begin(), left.end());
            __down_heap = std::priority_queue<int>(left.begin(), left.end());
            std::make_heap(right.begin(), right.end(), std::greater<int>());
            __up_heap = std::priority_queue<int, std::deque<int>, std::greater<int>>(right.begin(), right.end());
            // rebalance if size diff > 1
            __rebalance();
        }
        // insert element
        void insert(int x)
        {
            if (__down_heap.empty() || x <= __down_heap.top())
                __down_heap.push(x);
            else
                __up_heap.push(x);
            __rebalance();
        }
        // find median
        double find_median() const
        {
            if (__down_heap.empty() && __up_heap.empty())
                throw std::runtime_error("No elements");
            if (__down_heap.size() == __up_heap.size())
                // rule: median = top of max-heap
                return __down_heap.top();
            else if (__down_heap.size() > __up_heap.size())
                return __down_heap.top();
            else
                return __up_heap.top();
        }
        // extract median
        int extract_median()
        {
            if (__down_heap.empty() && __up_heap.empty())
                throw std::runtime_error("No elements");
            int med;
            if (__down_heap.size() == __up_heap.size())
            {
                med = __down_heap.top();
                __down_heap.pop();
            }
            else if (__down_heap.size() > __up_heap.size())
            {
                med = __down_heap.top();
                __down_heap.pop();
            }
            else
            {
                med = __up_heap.top();
                __up_heap.pop();
            }
            // we dont need to call the rebalance
            return med;
        }
    };
}