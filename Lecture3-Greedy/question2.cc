

/**
 * write by fengchengyu in 09/18/2025 for question2 in Homework3
 */

#include <stdint.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <math.h>

/**
 * @brief Compute the maximum possible score defined as 
 *        Π a_i^{b_i}, by permuting two input sequences A and B.
 *
 * @param A A vector of positive integers (sequence A).
 * @param B A vector of positive integers (sequence B), same length as A.
 * @return uint32_t The maximum score.
 */
uint32_t maxScore(std::vector<int>& A, std::vector<int>& B) {
    assert(A.size() == B.size());
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    uint32_t result = 1;
    for(int i = 0; i < A.size(); ++i)
        result *= pow(A[i], B[i]);
    return result;
}

int main() {
    std::vector<int> A = {2, 3, 1};
    std::vector<int> B = {5, 2, 1};
    std::cout << "Max score = " << maxScore(A, B) << "\n";
    return 0;
}