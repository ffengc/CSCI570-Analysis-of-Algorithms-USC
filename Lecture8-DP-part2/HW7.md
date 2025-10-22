# Homework 7

- [Homework 7](#homework-7)
  - [Question1](#question1)
    - [Subproblems](#subproblems)
    - [Recurrence](#recurrence)
    - [Codes](#codes)
    - [Complexity](#complexity)
  - [Question 2](#question-2)
    - [Subproblems](#subproblems-1)
    - [Recurrence](#recurrence-1)
    - [Codes](#codes-1)
    - [Complexity](#complexity-1)
  - [Question 3](#question-3)
    - [Preliminary analysis](#preliminary-analysis)
    - [LIS Problem](#lis-problem)
    - [LDS Problem](#lds-problem)
    - [Solve the LBS Problem](#solve-the-lbs-problem)
    - [Codes](#codes-2)
    - [Complexity](#complexity-2)

## Question1

Suppose we are given $n$ balloons, indexed from $0$ to $n − 1$. Each balloon is painted with a number on it represented by array `nums`. You are asked to burst all the balloons. If you burst balloon $i$, you will get 	`nums[left] ∗ nums[i] ∗ nums[right]` coins. Here, `left` and `right` are balloons adjacent to `i` **at the time of bursting**. After bursting any balloon, its `left` and `right` then become adjacent (thus, there aren’t any “gaps” at any point, see example below). 

Assume `nums[−1] = nums[n] = 1` when determining the coins obtained by bursting the corner balloons, (-1 and n are not indices of real balloons, therefore you can not burst them). Design a dynamic programming algorithm to find the maximum coins you can collect by bursting the balloons. (20 points)

### Subproblems

First, let’s deal with the boundary conditions. Pad the array with two virtual balloons of value 1 at both ends: `lst = [1] + nums + [1]`.

For any two indices `l < r`, consider the **open interval** `(l, r)`—i.e., the balloons strictly between l and r.

Define the length of the interval `len = l-r`, in the middle, we have `len-1` balloons. For example, when `len=2, l=1, r=3`, we have one balloon (#2) in the middle.

> Let `dp[l][r]` be the **maximum coins** we can collect by bursting **all balloons in the open interval** `(l, r)` while keeping `lst[l]` and `lst[r]` unburst as boundaries.

Intuition: if the **last** balloon burst inside `(l, r)` is `k`, then by the time we burst `k` its adjacent balloons are exactly the boundaries `l` and `r`. So the last-burst gain is `lst[l] * lst[k] * lst[r]`, and everything left/right of `k` has already been optimally finished as two independent subproblems.

### Recurrence

For any `l < r`:
$$
dp[l][r] \;=\; \max_{\,l<k<r}\Big( dp[l][k] \;+\; dp[k][r] \;+\; val[l]\cdot val[k]\cdot val[r] \Big)
$$
**Base case:** if there is no balloon strictly between l and r (i.e., `r = l + 1`), then `dp[l][r] = 0`.

Target answer: `dp[0][n+1]` where `n = nums.length`.

### Codes

**Pseudocode: **

```pseudocode
function BurstBalloons(nums):
    # Convert nums to a list (deque) and add boundary 1s
    lst ← deque(nums)
    push_front(lst, 1)
    push_back(lst, 1)
    sz ← length(lst)

    # dp[l][r] = maximum coins from bursting all balloons 
    # in the open interval (l, r)  (excluding lst[l] and lst[r])
    dp ← 2D array of size sz×sz, filled with 0

    # Base case:
    # When r = l + 1, there are no balloons between l and r → dp[l][r] = 0

    # Iterate over all possible interval lengths
    for len ← 2 to sz − 1:                     # interval length (r − l)
        for l ← 0 to sz − len − 1:             # left boundary
            r ← l + len                        # right boundary
            # Enumerate the last balloon to burst inside (l, r)
            for k ← l + 1 to r − 1:
                gain ← lst[l] × lst[k] × lst[r]
                dp[l][r] ← max(dp[l][r], dp[l][k] + dp[k][r] + gain)

    return dp[0][sz − 1]
```

input: nums = [3, 1, 5, 8]

result: 167

the result can be seen in C++ codes part.

**C++ codes:**

```cpp
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
void question1() { 
    std::vector<int> input = {3, 1, 5, 8};
    std::cout << burstBalloonsProblem(input) << std::endl; // 167
}
```

**result:**

![image-20251021175723883](./assets/image-20251021175723883.png)

### Complexity

- There are $O((n+2)^2) = O(n^2)$ states `dp[l][r]`.
- For each state we try all `k` in `(l, r)`, costing $O(n)$.
- **Time complexity:** $O(n^3)$.
- **Space complexity:** $O(n^2)$

**Efficiency:** This is the standard optimal DP for the problem. For typical constraints (e.g., $n \le 500$ is too large but $n \le 300$ in practice is borderline; most coding settings use $n \le 300$ or less), $O(n^3)$ with $O(n^2)$space is considered efficient and is the accepted solution.

## Question 2

Tommy and Bruiny are playing a turn-based game. It involves $N$ marbles placed in a row. Each marble $i$ has a positive value $m_i$. On each player’s turn, they can remove either the leftmost marble or the rightmost marble from the row and receive a score given by the value of that marble. The players’ goal is to beat the opponent's score by the highestmargin possible (equivalently, minimizing the losing margin in the case of the player with the lesser score).

### Subproblems

Let `dp[l][r]` represents the maximum score difference (current player's score minus opponents's score) obtained from the subarray of marbles `m[1..r]`.

Intuitively,` dp[1][r]` represents that: 

> If it is your turn and the remaining marbles are from index 1 to r, how many more points can you finish ahead of your opponent, assuming both play optimally.

### Recurrence

**Base case:**

when `l==r`, there is only one marble to pick, so the current player simply takes it: `dp[i][i] = m[i]`.

**Recurrence relation:**

As sate `[l,r]`, the current player has two choices:

1. take the left marble: `m[l]`

   Therefore, the opponent then plays optimally on `[l+1, r]`, gaining an advantage of `dp[l+1][r]`. The relation: `m[l] - dp[l+1][r]`.

2. take the right marble: `m[r]`

   therefore, `m[r] - dp[l][r-1]`

Hence, the recurrence relation formula:
$$
dp[l][r] = \max(m[l]-dp[l+1][r], \ m[r] - dp[l][r-1])
$$
**Traversal Order:**

We need to calculate `dp[0][n-1]`, therefore, we need to calculate the `dp` array from the diagonal to the right-up direction. Therfore, `row--`, `col++`.

### Codes

**Pseudocode: **

```pseudocode
function MarbleGame(m[0..n−1]):
    dp ← n×n array of 0
    for i ← 0..n−1:
        dp[i][i] ← m[i]
    for j ← 1..n−1:                # right boundary
        for i ← j−1 downto 0:      # left boundary
            takeLeft  ← m[i] − dp[i+1][j]
            takeRight ← m[j] − dp[i][j−1]
            dp[i][j] ← max(takeLeft, takeRight)

    return dp[0][n−1]              # final score difference (Tommy − Bruiny)
```

input: {1, 5, 2}

output: -2

This is in line with expectations.

**C++ codes:**

```cpp
int solveMarblesProblem (const std::vector<int>& marbles) {
    // dp[l][r]: in this term, what's the score diff: me - opponent
    // dp[l][r] = max(m[l] - dp[l+1][r], m[r] - dp[l][r-1])
    // dp[l][l] = m[l]
    // obj: dp[0][n-1]
    // dp direction: right-up 
    if (marbles.empty()) return 0;
    int n = marbles.size();
    auto dp = std::vector<std::vector<int>>(n, std::vector<int>(n));
    for(int i = 0; i < n; ++i)
        dp[i][i] = marbles[i];
    // dp
    for(int j = 1; j < n; ++j) {
        for(int i = j - 1; i >= 0; --i) {
            dp[i][j] = std::max(marbles[i] - dp[i + 1][j], marbles[j] - dp[i][j-1]);
        }
    }
    return dp[0][n-1];
}
void question2() {
    std::vector<int> marbles = {1, 5, 2};
    std::cout << "marbles problem: " << solveMarblesProblem(marbles) << std::endl;
}
```

input: {1, 5, 2}

output: -2

This is in line with expectations.

![image-20251022143935244](./assets/image-20251022143935244.png)

### Complexity

The dynamic programming table has $O(n^2)$ states, and each state is computed in constant time.

Therefore, the time complexity is $O(n^2)$ and the space complexity is also $O(n^2)$.

Since the algorithm reduces the original exponential search (all possible move sequences) to a quadratic DP solution, it is considered efficient and optimal for this problem size.

## Question 3

The Trojan Band consisting of $n$ band members hurries to line up in a straight line to start a march. Due to the height differences, the line is looking very messy. The band leader decides to pull out a few band members so that the line *follows a formation* with the remaining band members staying where they are. We say that k members remaining in the line with heights $r_1, r_2,... ,r_k$ are *in formation* if $r_1 < r_2 < ... < r_i > ... > r_k$, for some $1 ≤ i ≤ k$.

Give an algorithm using Dynamic Programming that runs in $O(n^2)$ time to find the minimum number of band members to pull out of the line, so that we are left with a *formation* as described.

### Preliminary analysis

This question is to find a bitonic subsequence of the array. A **bitonic subsequence** is a sequence of numbers that first **strictly increases** and then **strictly decreases**. So, this question is a **longest bitonic subsequence problem (LBS)**.

The left part of the bitonic subsequence can be calculated by LIS (longest increasing subsequence), and the right part can be calculated by LDS (longest decreasing subsequence).

**Therefore, in order to solve this problem, the LIS  problem needs to be explained and solved first.**

### LIS Problem

The LBS problem is similar to the longest increasing subsequence (LIS) problem. 

A LIS is a sequence derived from an array by removing (or not removing) elements from the array without changing the order of the remaining elements, and the rest of the elements are in strictly increasing order.

Now, I will explain how to use DP to solve the LIS problem.

**Define the subproblems:**

Define the orginal array `A[]`.

Define a one dimension array `LIS[]`, which represents the array of dynamic programming (dp array). 

Define `LIS[i]` represents the length of LIS in array A ==ending== with `A[i]`. For example, `LIS[1]` represents that, when we only consider `A[0]` and `A[1]`, what's the length of the LIS of `{A[0], A[1]}`.

**Build the recurrence relation:**

Base Case: For each `i`, the corresponding `LIS[i]`starts with a size of at least 1.

Then, the longest ascending subsequence at position `i` is equal to the maximum of the longest ascending subsequences at positions `j` from `0` to`i-1`  and them plus 1.
therefore:  `if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);`

**pseudocode code for LIS problem:**

`LIS[]` is `dp[]` .

in LIS problem, we usually return the length of LIS. But in bitonic sequence problem, we need to return the whole `LIS[]` dp array. I'll explain it later.

 ```pseudocode
function LIS(nums):
    n ← length(nums)
    if n == 1:
        return (1, [1])
    # Initialize DP array
    dp[0..n-1] ← 1
    # Compute LIS ending at each position i
    for i from 1 to n-1:
        max_length ← 1
        for j from 0 to i-1:
            if nums[i] > nums[j]:
                max_length ← max(max_length, dp[j] + 1)
        dp[i] ← max_length
    # Find overall maximum LIS length
    max_LIS ← maximum value in dp
    return (max_LIS, dp)
 ```

**C++ code for LIS problem:**

```cpp
std::pair<int, std::vector<int>> LIS(vector<int>& nums) {
    if(nums.size() == 1) return 1;
    auto dp = std::vector<int>(nums.size(), 1);
    for(int i = 1; i < nums.size(); ++i) {
        int _max_length = 1;
        for(int j = 0; j < i; ++j)
            if(nums[i] > nums[j]) _max_length = std::max(dp[j] + 1, _max_length);
        dp[i] = _max_length;
    }
    return {*std::max_element(dp.begin(), dp.end()), dp};
}
```

### LDS Problem

A LDS is a sequence derived from an array by removing (or not removing) elements from the array without changing the order of the remaining elements, and the rest of the elements are in strictly decreasing order.

Define `LDS[i]` represents the length of LIS in array `A` ==starts== with `A[i]`. For example, `LDS[2]` represents that, when we only consider `A[2], A[3], ..., A[n]`, what's the length of the LDS of `{A[2], A[3], ..., A[n]}`.

To calculate `LDS[]` is very easy:

1. reverse the `A` as `A*`
2. calculate the `LIS[]` array of `A*` as $LIS_{A^*}[]$
3. reverse the $LIS_{A^*}[]$ and we can get $LDS_A[]$

### Solve the LBS Problem

Now we have the `LIS[]` array and the `LDS[]` array of the array `A`. 

Therefore obviously, for each `i`: 

- the length of the LIS of array `{A[0], ..., A[i]}` is `LIS[i]`,
- the length of the LDS of array `{A[i], ..., A[n]}` is `LDS[i]`

Therefore, if `i` is the highest peak of the bitonic sequence, the length of the bitonic sequence is: `LBS[i] = LIS[i] + LDS[i] - 1` (since `A[i]` is calculated twice).

**Therefore, we only need to traverse each i and get the maximum result.**

### Codes

**pseudocode code :**

```pseudocode
function LIS(nums):
		# ...
		return (max_LIS, dp)
function lengthOfLBS(nums):
    # Step 1. Compute LIS (Longest Increasing Subsequence)
    (LIS_length, LIS_list) ← LIS(nums)

    # Step 2. Compute LDS by reversing and reusing LIS
    tmp ← reverse(nums)
    (LDS_length, LDS_list) ← LIS(tmp)
    LDS_list ← reverse(LDS_list)

    # Step 3. Combine LIS and LDS for each position i
    LBS_result ← -∞
    for i from 0 to n-1:
        bitonic_len ← LIS_list[i] + LDS_list[i] - 1
        LBS_result ← max(LBS_result, bitonic_len)

    return LBS_result
```

**C++ code:**

```cpp
std::pair<int, std::vector<int>> LIS(const std::vector<int> &nums)
{
    // ...
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
```

**test:**

```cpp
void question3()
{
    std::vector<int> inputSeq = {67, 65, 72, 75, 73, 70, 70, 68};
    std::cout << lengthOfLBS(inputSeq) << std::endl; // 6
}
```

output: 6

![image-20251021180520711](./assets/image-20251021180520711.png)

### Complexity

The LBS algorithm computes two auxiliary arrays — the Longest Increasing Subsequence (LIS) and the Longest Decreasing Subsequence (LDS) — each using a nested loop.

- Computing `LIS[i]` for all `i` requires $O(n^2)$ time, since for every element, we may compare it with all previous elements.
- Computing `LDS[i]` is symmetrical and also takes $O(n^2)$ time (reverse the list takes $O(n)$ time).
- Combining LIS and LDS results takes $O(n)$ time.

Hence, the overall **time complexity** is:

$T(n) = O(n^2) + O(n^2) + O(n) = O(n^2)$

Therefore, the overall time complexity of the algorithm is **O(n²)** and the space complexity is **O(n)**.

**Efficient solution or not?**

Since any comparison-based dynamic programming solution for subsequence problems (like LIS/LBS) generally requires at least quadratic time, this $O(n²)$ algorithm is considered efficient and optimal for this problem size.