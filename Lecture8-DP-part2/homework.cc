

/**
 *  @brief code write by fengchengyu in 10/20/2025 for homework7
 *  @date 10/20/2025
 *  @author fengchengyu
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

int burstBalloonsProblem(const std::vector<int>& nums) {
    // the first loop: the len of the interval - len=2 -> there is 1 balloon in
    // the middle
    //          0 1 2 3: len=3-0=3, there is 2 ballon in the middle
    // the second loop: the begin of the interval
    // the third loop: the middle point k
    std::deque<int> lst(nums.begin(), nums.end());
    lst.push_front(1);
    lst.push_back(1);
    int sz = lst.size();
    // add 1 in the front and the back
    // dp[i][j] means that, in (i,j) interval (not include nums[i] and nums[j]), whats the max result
    // the interval is len=j-1, 
    auto dp = std::vector<std::vector<int>>(sz, std::vector<int>(sz, 0));

    // base case: len=1, when r=l+1
    // there is no balloon in the middle, nothing can burst, therefore =0.

    // first loop
    for(int len = 2; len < sz; ++len) {
        // the length of interval cannot less than 2
        // len=2: 0, 1, 2, there is only one balloon in the middle

        // second loop
        for(int l = 0; l + len < sz; ++l) {
            // in this case, r=l+len
            int r = l + len;
            // the middle point, the last burst balloon
            for(int k = l + 1; k < r; ++k) {
                dp[l][r] = std::max(dp[l][r], dp[l][k] + dp[k][r] + lst[k] * lst[l] * lst[r]);
            }
        }
    }
    return dp[0][sz-1];
}

// use the same way, try to solve the Matrix Chain Multiplication Problem

int matrixChainMultiplicationProblem(const std::vector<std::pair<int,int>> matrixs) {
    /**
     * @param: matrix[i].first and matrix[i].second => row and col of matrix[i]
     * @return: min number of element multiplications
     */
    int sz = matrixs.size();
    auto dp = std::vector<std::vector<int>>(sz, std::vector<int>(sz, 0));
    const int INF = 9999999;
    // first loop: len
    for(int len = 2; len <= sz; ++len) { // it's <= not <, cuz the len can be equal to the size of matrixs list
        // second loop: the left
        for(int l = 0; l + len - 1 < sz; ++l) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for(int k = l; k < r; ++k) { // need to start from l
                // when k=l,
                // left part: matrix[l], right part: matrix[l+1]...matrix[r]
                int row_of_matrix_l = matrixs[l].first;
                int col_of_matrix_k = matrixs[k].second;
                int col_of_matrix_r = matrixs[r].second;
                int new_cost = dp[l][k] + dp[k+1][r] + row_of_matrix_l*col_of_matrix_k*col_of_matrix_r;
                dp[l][r] = std::min(dp[l][r], new_cost);
            }
        }
    }
    return dp[0][sz-1];
}

void question_matrix() {
    std::vector<std::pair<int,int>> input = {{2, 10}, {10, 50}, {50, 20}};
    std::cout << matrixChainMultiplicationProblem(input) << std::endl;
}

void question1() { 
    std::vector<int> input = {3, 1, 5, 8};
    std::cout << burstBalloonsProblem(input) << std::endl;
}

std::pair<int, std::vector<int>> LIS(const std::vector<int>& nums) {
    if (nums.size() == 1) return {1, {1}};
    auto dp = std::vector<int>(nums.size(), 1);
    for (int i = 1; i < nums.size(); ++i) {
        int _max_length = 1;
        for (int j = 0; j < i; ++j)
            if (nums[i] > nums[j])
                _max_length = std::max(dp[j] + 1, _max_length);
        dp[i] = _max_length;
    }
    return {*std::max_element(dp.begin(), dp.end()), dp};
}
int lengthOfLBS(const std::vector<int>& nums) {
    auto LIS_list = LIS(nums).second;
    // reverse the seq
    auto tmp = nums;
    std::reverse(tmp.begin(), tmp.end());
    auto LDS_list = LIS(tmp).second;
    std::reverse(LDS_list.begin(), LDS_list.end());
    // now we have LIS and LDS
    int lengthOfLBS_result = -1;
    for (int i = 0; i < nums.size(); ++i)
        lengthOfLBS_result =
            std::max(lengthOfLBS_result, LIS_list[i] + LDS_list[i] - 1);
    return lengthOfLBS_result;
}
void question3() {
    std::vector<int> inputSeq = {67, 65, 72, 75, 73, 70, 70, 68};
    std::cout << lengthOfLBS(inputSeq) << std::endl;
}
int main() {
    question3();
    return 0;
}
