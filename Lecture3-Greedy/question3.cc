
/**
 * write by fengchengyu in 09/18/2025 for question3 in Homework3
 */

#include <stdint.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

/**
 * @brief Compute the minimum calories required to merge all chains into one.
 *
 * @param chains_weight A vector containing the weights of all chains.
 * @return uint64_t The minimum total calories burnt (each merge costs 100 * (W1 + W2)).
 */
uint32_t combineChainsWithLeastCalories(const std::vector<std::size_t>& chains_weight) {
    // build the min-heap
    uint32_t result = 0;
    std::priority_queue<size_t,std::vector<std::size_t>, std::greater<std::size_t>>pq(chains_weight.begin(), chains_weight.end());
    while(true) {
        if(pq.size() == 1) return result;
        int weight1 = pq.top();
        pq.pop();
        int weight2 = pq.top();
        pq.pop();
        result += 100 * (weight1 + weight2);
        pq.push(weight1 + weight2);
    }
}

int main() {
    std::vector<std::size_t> chains = {4, 3, 2, 6};
    std::cout << "Minimum calories = " 
              << combineChainsWithLeastCalories(chains) << "\n";
    return 0;
}