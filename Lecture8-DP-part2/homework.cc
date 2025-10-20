

/**
 *  @brief code write by fengchengyu in 10/20/2025 for homework7
 *  @date 10/20/2025
 *  @author fengchengyu
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::pair<int, std::vector<int>> LIS(const std::vector<int> &nums)
{
    if (nums.size() == 1)
        return {1, {1}};
    auto dp = std::vector<int>(nums.size(), 1);
    for (int i = 1; i < nums.size(); ++i)
    {
        int _max_length = 1;
        for (int j = 0; j < i; ++j)
            if (nums[i] > nums[j])
                _max_length = std::max(dp[j] + 1, _max_length);
        dp[i] = _max_length;
    }
    return {*std::max_element(dp.begin(), dp.end()), dp};
}

int lengthOfLBS(const std::vector<int> &nums)
{
    auto LIS_list = LIS(nums).second;
    // reverse the seq
    auto tmp = nums;
    std::reverse(tmp.begin(), tmp.end());
    auto LDS_list = LIS(tmp).second;
    std::reverse(LDS_list.begin(), LDS_list.end());
    // now we have LIS and LDS
    int lengthOfLBS_result = -1;
    for(int i = 0; i < nums.size(); ++i) 
        lengthOfLBS_result = std::max(lengthOfLBS_result, LIS_list[i] + LDS_list[i] - 1);
    return lengthOfLBS_result;
}

void question3()
{
    std::vector<int> inputSeq = {67, 65, 72, 75, 73, 70, 70, 68};
    std::cout << lengthOfLBS(inputSeq) << std::endl;
}
int main()
{
    question3();
    return 0;
}
