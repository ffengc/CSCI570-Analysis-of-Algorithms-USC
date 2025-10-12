
/**
 *  * this code write by fengchengyu in 10/11/2025 for homework7
 */

#include <vector>
#include <iostream>
#include <assert.h>

int unbounded_knapsack_problem(int capacity,
                               const std::vector<int> &weights,
                               const std::vector<int> &values)
{
    int n = weights.size(); // the number of the items
    auto opt = std::vector<std::vector<int>>(n, std::vector<int>(capacity + 1));
    // init the first row
    for (int j = 0; j <= capacity; ++j)
        if (j >= weights[0])
            opt[0][j] = opt[0][j - weights[0]] + values[0];
    // dp part
    for (int i = 1; i < n; ++i)
        for (int j = 0; j <= capacity; ++j)
            if (j < weights[i])
                opt[i][j] = opt[i - 1][j];
            else
                opt[i][j] = std::max(opt[i - 1][j], opt[i][j - weights[i]] + values[i]);
    return opt[n - 1][capacity];
}
void question1()
{
    std::vector<int> weights = {1, 2, 3, 4};
    std::vector<int> values = {2, 4, 4, 5};
    int capacity = 5;
    std::cout << unbounded_knapsack_problem(capacity, weights, values) << std::endl;
}

int no_adjacent_01_knapsack_problem(int capacity,
                                    const std::vector<int> &weights,
                                    const std::vector<int> &values)
{
    int n = weights.size();
    auto dp = std::vector<std::vector<int>>(n, std::vector<int>(capacity + 1));
    if(n == 0) assert(false);
    if(n == 1) return weights[0] <= capacity ? values[0] : 0;
    // base case
    // first row
    for(int j = 0; j <= capacity; j++)
        if(j >= weights[0]) dp[0][j] = values[0]; // item #0
    // second row
    for(int j = 0; j <= capacity; j++)
        if(j < weights[1]) dp[1][j] = dp[0][j];
        else dp[1][j] = std::max(values[0], values[1]);
    // begin to dp
    for(int i = 2; i < n; ++i)
        for(int j = 0; j <= capacity; ++j)
            if(j < weights[i]) dp[i][j] = dp[i-1][j];
            else dp[i][j] = std::max(dp[i-1][j], dp[i-2][j-weights[i]] + values[i]);
    return dp[n-1][capacity];
}
void question2()
{
    // Each test case uses the same vector for weights and values,
    // since the "money" amount serves as both the weight and the value.
    // The goal: maximize total money without exceeding K and without picking adjacent briefcases.
    std::vector<std::vector<int>> test_cases = {
        {5},             // Case 1: Only one briefcase
        {3, 4, 5},       // Case 2: Simple small example
        {2, 5, 4, 6},    // Case 3: Typical case
        {4, 5, 7, 3, 6}, // Case 4: Multiple combinations possible
        {8, 9, 10},      // Case 5: All items exceed capacity
        {44, 51, 46, 55, 23, 12} // Case6: example on the pdf
    };
    std::vector<int> capacities = {10, 7, 9, 12, 5, 100};
    for (int t = 0; t < test_cases.size(); ++t)
    {
        std::cout << "Test Case " << t + 1 << ": "
                  << no_adjacent_01_knapsack_problem(capacities[t],
                                                     test_cases[t],
                                                     test_cases[t])
                  << std::endl;
    }
    /**
        Test Case 1: 5      // Only item fits
        Test Case 2: 5      // Best pick: item #1 (value 5)
        Test Case 3: 8      // Best pick: items #0 and #3 → 2 + 6 = 8
        Test Case 4: 11     // Best pick: items #0 and #2 → 4 + 7 = 11
        Test Case 5: 0      // All items exceed K
        Test Case 6: 99
     */
}


void question3() {
    int N = 8;
    std::vector<int>prices = {1, 5, 8, 9, 10, 17, 17, 20};
    std::vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << unbounded_knapsack_problem(N, weights, prices) << std::endl;
}

int main()
{
    question3();
    return 0;
}