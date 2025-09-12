/**
    write by Fengcheng Yu in 09/03/2025
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <queue>

class GaleShapleyAlgorithm
{
private:
    using VI = std::vector<int>;
    using VII = std::vector<std::vector<int>>; // redifine the vector type
    std::size_t __n = 0;                       // the number of the man or women
    VII __menPreference;                       // menPreference List: [][]
    VII __womenPreference;                     // womenPreference List: [][]
    VII __womenRank;                           // rank of man m in woman w's list (0 is the best)
    // note: use __womenRank to get the rank of one m in one w in O(1)
private:
    bool checkInputValid()
    {
        if (__n != __menPreference.size() || __n != __womenPreference.size())
            return false;
        if (__n != __menPreference[0].size()) // this two-dimensional array must be a square
            return false;
        // check if the input is valid
        // every row of __menPreference and __womenPreference must 0 ... n-1 permutation
        VI tmpList;
        for (int i = 0; i < __n; ++i)
            tmpList.push_back(i);
        // tmpList: [0, ..., n-1]
        // use the function is_permutation in algorithm to check each row
        for (int i = 0; i < __menPreference.size(); ++i)
        {
            if (!std::is_permutation(tmpList.begin(), tmpList.end(), __menPreference[i].begin()))
                return false;
            if (!std::is_permutation(tmpList.begin(), tmpList.end(), __womenPreference[i].begin()))
                return false;
        }
        // build women rank
        __womenRank.assign(__n, VI(__n, 0));
        for (int w = 0; w < __n; ++w)
        {
            // each women: w
            for (int rank = 0; rank < __n; ++rank)
            {
                int m = __womenPreference[w][rank];
                __womenRank[w][m] = rank;
            }
        }
        // for debug
        // for (int i = 0; i < __womenRank.size(); ++i)
        // {
        //     for (int j = 0; j < __womenRank[0].size(); ++j)
        //     {
        //         std::cout << __womenRank[i][j] << ",";
        //     }
        //     std::cout << std::endl;
        // }
        return true;
    }

public:
    GaleShapleyAlgorithm(const VII &menPreference, const VII &womenPreference)
        : __n(menPreference.size()), __menPreference(menPreference), __womenPreference(womenPreference) {}
    VI galeshapleyAlgorithm()
    {
        // the algorithm assumes that mens propose
        // if a woman proposes, the implementation process is symmetrical
        if (__n == 0)
            assert(false); // ignore __n == 0
        if (!checkInputValid())
        {
            std::cerr << "the input of the algorithm is unvalid" << std::endl;
            exit(1);
        }
        // begin algorithm
        VI manMatch(__n, -1);
        VI womenMatch(__n, -1);
        VI nextIdx(__n, 0); // man bids for the next woman he wants to pursue
        std::queue<int> freeMen;
        for (int i = 0; i < __n; ++i)
            freeMen.push(i); // push every men into a queue, wait for propose

        while (!freeMen.empty())
        {
            // the galeshapley can make sure that the loop can end.
            int m = freeMen.front(); // get one man
            freeMen.pop();
            // find the next woman he proposed
            // orginally is 0, but if 0 rejected the man, than 0 -> 1
            int w = __menPreference[m][nextIdx[m]++];
            if (womenMatch[w] == -1)
            {
                // this woman is free -> engaged
                womenMatch[w] = m;
                manMatch[m] = w;
            }
            else
            {
                // this woman is already engaged
                int m2 = womenMatch[w];
                if (__womenRank[w][m] < __womenRank[w][m2])
                {
                    // change the husband
                    womenMatch[w] = m;
                    manMatch[m] = w;
                    manMatch[m2] = -1;
                    freeMen.push(m2);
                }
                else
                {
                    freeMen.push(m);
                }
            }
        }
        return manMatch;
    }
    bool isStable(const VI &manMatch)
    {
        // todo
        return true;
    }
    void printManMatch(const VI &manMatch)
    {
        assert(manMatch.size() == __n);
        for (int i = 0; i < manMatch.size(); ++i)
            std::cout << "(m" << i << ",w" << manMatch[i] << ")" << std::endl;
    }
};

#if 0
int main()
{
    std::vector<std::vector<int>> manPref = {{0, 1, 2}, {0, 2, 1}, {2, 1, 0}};
    std::vector<std::vector<int>> womenPref = {{1, 0, 2}, {2, 0, 1}, {0, 1, 2}};
    // m0: 0 > 1 > 2; w0: 1 > 0 > 2
    // m1: 0 > 2 > 1; w1: 2 > 0 > 1
    // m2: 2 > 1 > 0; w2: 0 > 1 > 2
    /**
     * res:
    (0,0)
    (1,1)
    (2,2)
     */
    GaleShapleyAlgorithm gs(manPref, womenPref);
    std::vector<int> manMatch = gs.galeshapleyAlgorithm();
    gs.printManMatch(manMatch);
    return 0;
}
#endif

#include <random>
#include <chrono>
#define TEST_TIMES 10000

std::vector<std::vector<int>> generateMatrix(int n, int rowIdx, int firstVal, std::mt19937 &gen)
{
    std::vector<std::vector<int>> mat(n, std::vector<int>(n));
    std::vector<int> base(n);
    for (int i = 0; i < n; i++)
        base[i] = i;
    for (int i = 0; i < n; i++)
    {
        std::vector<int> row = base;
        std::shuffle(row.begin(), row.end(), gen);
        if (i == rowIdx)
        {
            // Ensures that the first element is the specified firstVal
            row.erase(std::find(row.begin(), row.end(), firstVal)); // Delete firstVal
            row.insert(row.begin(), firstVal);                      // insert at the front
        }
        mat[i] = row;
    }
    return mat;
}
int main()
{
    // question 2
    auto start = std::chrono::high_resolution_clock::now(); // begin
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distN(2, 100);
    for (int i = 0; i < TEST_TIMES; ++i)
    {
        // Randomly generate a positive integer between 2 and 10000
        int n = distN(gen); // number of man or woman

        // Randomly generate two integers m and w
        // Indicates that w is the first choice of m, and m is the first choice of w
        std::uniform_int_distribution<int> distMW(0, n - 1);
        int m = distMW(gen);
        int w = distMW(gen);
        std::cout << "------------- round: " << i << " -------------" << std::endl;
        std::cout << "m: " << m << ", w: " << w << std::endl;
        std::vector<std::vector<int>> menPref = generateMatrix(n, m, w, gen);
        std::vector<std::vector<int>> womenPref = generateMatrix(n, w, m, gen);
        GaleShapleyAlgorithm gs(menPref, womenPref);
        std::vector<int> manMatch = gs.galeshapleyAlgorithm();
        // check if (m, w) in the man Match, if yes -> correct
        if(manMatch[m] == w) {
            std::cout << "find" << "(" << m << "," << w << ") in the matching res, correct" << std::endl;
        } else {
            std::cout << "do not" << "find" << "(" << m << "," << w << ") in the matching res, something wrong!" << std::endl;
            exit(1);
        }
    }
    auto end = std::chrono::high_resolution_clock::now(); // end
    std::chrono::duration<double> time = end - start;
    std::cout << "total time: " << time.count() << std::endl;
    return 0;
}