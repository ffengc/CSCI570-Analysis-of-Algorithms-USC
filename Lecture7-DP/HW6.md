# Homework 6

**Name:** Fengcheng Yu

**USCID:** xxx

**Email:** xxx

## Question1

James wants to surprise his fiancée with exquisite jewellery made from gold. He owns many gold mines and wants the goldsmith to make different items. He gives the goldsmith a list of $n$ different types of items, where each item type weighs $w_i$ grams and each has a value of $v_i$. James’ fiancée likes jewellery but only has space for some items, as her jewellery box has a maximum capacity of $W$ grams. James wants the goldsmith to make items from the list and insists that the combined weight of all the items must be equal to or less than $W$ grams, but at the same time, maximizing the total value of all the created items. Design a DP algorithm to output the total optimal value of the items, whose total weight doesn’t exceed $W$ grams. Note that the final jewellery box can contain multiple instances of the same jewellery. (20 points)

### Define the subproblems

First, this is a unbounded knapsack problem.

Define a two dimension array `Opt`, which represents the array of dynamic programming (dp array). 

`Opt(i, j)` indicates the maximum value that can be loaded into the backpack when there is only item `[0,i]` and the backpack capacity is `j`. (Define arrays and item indexs starting from 0)

For example, `Opt(1, 3)` represents that, when there is only item #0 and item #1, and the capacity of the knapsack is 3, the maximum value we can load to the knapsack.

### Build the recurrence relation

First, we need to initialize the dp array.  **(Base Case)**

- The first row represents when there is only item #0, what's the maximum value we can load when the capacity of the knapsack is from 0 to $W$.  

  - It is obvious that when `j < weight[0]`, `Opt(0, j)`should be 0, because the backpack capacity is less than the weight of item #0.

    When`j >= weight[0]`, `Opt(0,j)` will continue to hold `weight[0]` if it can hold it, and there will be an infinite number of each item.

- The first col represents when the capacity of the knapsack is 0, what's the maximum value we can load. Obviously, it's all 0 since the weight of the items are greater than 0. So we cannot load any items.

Then, we need to build the recurrence relation.

For example, we need to calculate `Opt(1,4)` (`Opt[1][4]`)

There are two cases, one with item 1 and the other without. We need to take the maximum value.

- `Opt[1][4]` = `max(Opt[0][4], Opt[1][1] + the value of item 1)`

The above process can be abstracted as follows:

- Without item #i: The backpack capacity is `j`, and the maximum value without item i is `Opt[i - 1][j]`.

- With item #i: After the knapsack is empty of the capacity for item #i, the backpack capacity is `j - weight[i]`. `Opt[i][j - weight[i]]` is the maximum value when the backpack capacity is `j - weight[i]` and item #i is not placed. Then `Opt[i][j - weight[i]] + value[i]` (the value of item #i) is the maximum value obtained by placing item #i in the backpack.

Recursive formula: `Opt[i][j] = max(Opt[i - 1][j], Opt[i][j - weight[i]] + value[i]);`

### Codes

**pseudocode:**

```pseudocode
Algorithm UnboundedKnapsack(capacity, weights[1..n], values[1..n]):
    Let OPT[0..n-1][0..capacity] be a 2D array
    # Initialize the first row (only item 0 can be chosen)
    for j ← 0 to capacity do
        if j >= weights[0] then
            OPT[0][j] ← OPT[0][j - weights[0]] + values[0]
        else
            OPT[0][j] ← 0
        end if
    end for
    # Fill the DP table
    for i ← 1 to n-1 do
        for j ← 0 to capacity do
            if j < weights[i] then
                OPT[i][j] ← OPT[i-1][j]
            else
                OPT[i][j] ← max( OPT[i-1][j], OPT[i][j - weights[i]] + values[i] )
            end if
        end for
    end for
    return OPT[n-1][capacity]
```

Example call:

```pseudocode
weights = [1, 2, 3, 4]
values  = [2, 4, 4, 5]
capacity = 5

Answer = UnboundedKnapsack(capacity, weights, values)
Output: 10
```

**code in C++:**

```cpp
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
    for(int i = 1; i < n; ++i)
        for(int j = 0; j <= capacity; ++j)
            if(j < weights[i]) opt[i][j] = opt[i-1][j];
            else opt[i][j] = std::max(opt[i-1][j], opt[i][j-weights[i]] + values[i]);
    return opt[n-1][capacity];
}
void question1()
{
    std::vector<int> weights = {1, 2, 3, 4};
    std::vector<int> values = {2, 4, 4, 5};
    int capacity = 5;
    std::cout << unbounded_knapsack_problem(capacity, weights, values) << std::endl; // 10
}
int main()
{
    question1();
    return 0;
}
```

### Complexity

**Time complexity:**

The DP table has $n × W$ entries, where $n$ is the number of jewellery types and $W$ is the maximum capacity.

Each entry `OPT[i][j]` is computed in O(1) time (a single max and addition).

Hence the overall **time complexity = O(n × W)**.

**Space complexity:**

The 2-D version uses `O(n × W)` space; it can be optimized to `O(W)` if only one dimension is kept.

**Efficiency:**

Because the algorithm runs in polynomial time with respect to $n$ and $W$, it is considered **efficient** for moderate input sizes.

## Question2

You are participating in a game show, where you are presented with a line of briefcases. On top of each briefcase, you can see the amount of money you can win by choosing that briefcase. However, after each time you pick out a briefcase, the host will remove the two briefcases adjacent to it (or the only adjacent briefcase if the corner-one was picked). 

Your goal is to maximize the amount of money you can win; however, if your final amount collected is more than $K$ dollars, you will lose all your money. Design a dynamicprogramming algorithm to compute the maximum earnings possible without exceeding K dollars by picking suitcases as per the aforementioned rules.

### Define the subproblems

This is a variant of the 01 knapsack problem. **In this problem, the weights and the values are same.**

First, define a two dimension array `Opt`, which represents the array of dynamic programming (dp array). 

`Opt(i, j)` indicates the maximum value that can be loaded into the knapsack when there is only item `[0,i]` and the backpack capacity is `j`. (Define arrays and item indexs starting from 0, **NO adjacent items are loaded**)

For example, `Opt(1, 3)` represents that, when there is only item #0 and item #1, and the capacity of the knapsack is 3, the maximum value we can load to the knapsack. **(NO adjacent items are loaded)**

### Build the recurrence relation

First, we need to initialize the dp array. **(Base Case)**

- The first row represents when there is only item #0, what's the maximum value we can load when the capacity of the knapsack is from 0 to $W$.  

  - It is obvious that when `j < weight[0]`, `Opt(0, j)`should be 0, because the backpack capacity is less than the weight of item #0.

    When`j >= weight[0]`, `Opt(0,j)` will hold `value[0]`.

- The first col represents when the capacity of the knapsack is 0, what's the maximum value we can load. Obviously, it's all 0 since the weight of the items are greater than 0. So we cannot load any items.

Then, we need to build the recurrence relation.

For example, we need to calculate `Opt(2,4)` (`Opt[2][4]`)

There are two cases, one with item #2 and the other without. We need to take the maximum value.

- `Opt[2][4]` = `max(Opt[1][4], Opt[0][1] + the value of item 2)`

The above process can be abstracted as follows:

- Without item #i: The backpack capacity is `j`, and the maximum value without item i is `Opt[i - 1][j]`.

- With item #i: After the knapsack is empty of the capacity for item #i, the backpack capacity is `j - weight[i]`. `Opt[i-2][j - weight[i]]` is the maximum value when the backpack capacity is `j - weight[i]` and item #i is not placed **(because we cannot choose adjacent items, therefore, in this case, we cannot choose item #i-1)**. Then `Opt[i-2][j - weight[i]] + value[i]` is the maximum value obtained by placing item #i in the knapsack.

Recursive formula: `Opt[i][j] = max(Opt[i - 1][j], Opt[i - 2][j - weight[i]] + value[i]);`

> [!IMPORTANT]
>
> As the recusive formula needs to calculate the `Opt[i-2][...]`, therefore, we need to initialize the second row of the dp array as well.

The **second row** of the DP table corresponds to the case where we have two items available: item #0 and item #1.

Therefore, we initialize it manually as follows:

- When `j < weight[1]`:

  The knapsack cannot include item #1, so the best we can do is the same as in the previous row — that is, `dp[1][j] = dp[0][j]`.

- When `j >= weight[1]`:

  We have two choices — either keep the previous best (`dp[0][j]`) or take item #1 (since items #0 and #1 are adjacent, we cannot take both).

  Thus, `dp[1][j] = max(dp[0][j], value[1])`

### Codes

**pseudocode:**

```pseudocode
Algorithm NoAdjacent01Knapsack(capacity, weights[0..n-1], values[0..n-1]):
    n ← length(weights)
    if n == 0:
        assert(false)
    if n == 1:
        if weights[0] <= capacity:
            return values[0]
        else:
            return 0
    Create 2D array DP[0..n-1][0..capacity], initialized to 0 # DP[][] is the Opt[][]
    # ---- Base Case: first row ----
    for j ← 0 to capacity do
        if j >= weights[0]:
            DP[0][j] ← values[0]
        else:
            DP[0][j] ← 0
        end if
    end for
    # ---- Base Case: second row ----
    for j ← 0 to capacity do
        if j < weights[1]:
            DP[1][j] ← DP[0][j]
        else:
            DP[1][j] ← max(values[0], values[1])
        end if
    end for
    # ---- Main DP recurrence ----
    for i ← 2 to n-1 do
        for j ← 0 to capacity do
            if j < weights[i]:
                DP[i][j] ← DP[i-1][j]
            else:
                DP[i][j] ← max(DP[i-1][j],
                                DP[i-2][j - weights[i]] + values[i])
            end if
        end for
    end for
    return DP[n-1][capacity]
```

Example Call:
```pseudocode
cases = {{5},              // Case 1: Only one briefcase
          {3, 4, 5},       // Case 2: Simple small example
          {2, 5, 4, 6},    // Case 3: Typical case
          {4, 5, 7, 3, 6}, // Case 4: Multiple combinations possible
          {8, 9, 10},      // Case 5: All items exceed capacity
          {44, 51, 46, 55, 23, 12}}  // Case6: example on the pdf}      
capacities = {10, 7, 9, 12, 5};
/**
    Test Case 1: 5      // Only item fits
    Test Case 2: 5      // Best pick: item #1 (value 5)
    Test Case 3: 8      // Best pick: items #0 and #3 → 2 + 6 = 8
    Test Case 4: 11     // Best pick: items #0 and #2 → 4 + 7 = 11
    Test Case 5: 0      // All items exceed K
    Test Case 6: 99
 */
```

**codes in C++:**

```cpp
int no_adjacent_01_knapsack_problem(int capacity,
                                    const std::vector<int> &weights,
                                    const std::vector<int> &values)
{
    int n = weights.size();
    auto dp = std::vector<std::vector<int>>(n, std::vector<int>(capacity + 1)); // dp[][] is the opt[][]
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
        {8, 9, 10}       // Case 5: All items exceed capacity
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
```

### Complexity

**Time complexity:**

The DP table has $n × W$ entries, where $n$ is the number of jewellery types and $W$ is the maximum capacity.

Each entry `DP[i][j]` is computed in O(1) time (a single max and addition).

Hence the overall **time complexity = O(n × W)**.

**Space complexity:**

The 2-D version uses `O(n × W)` space; it can be optimized to `O(W)` if only one dimension is kept.

**Efficiency:**

Because the algorithm runs in polynomial time with respect to $n$ and $W$, it is considered **efficient** for moderate input sizes.

## Question 3

Suppose you have a rod of length $N$, and you want to cut up the rod and sell the pieces in a way that maximizes the total amount of money you get. A piece of length $i$ is worth $p_i$ dollars. Devise a Dynamic Programming algorithm to determine the maximum amount of money you can get by cutting the rod strategically and selling the cut pieces. (20 points)

### Define the subproblems

This problem can be transformed into a unbounded knapsack problem:

- Knapsack capacity = total length N of the pole
-  “Items” = each possible cutting length i (lengths from 1 to N)
- Each item can be taken any number of times (because a pole can be cut into multiple segments of the same length)
- “Weight” of each item = i
- “Value” of each item = p[i]

→ So it is a complete knapsack problem.

**The following part of the idea is exactly the same as the unbounded knapsack problem.**

Define a two dimension array `Opt`, which represents the array of dynamic programming (dp array). 

`Opt(i, j)` indicates the maximum value that can be loaded into the backpack when there is only item `[0,i]` and the backpack capacity is `j`. (Define arrays and item indexs starting from 0)

### Build the recurrence relation

First, we need to initialize the dp array.  **(Base Case)**

- The first row represents when there is only item #0, what's the maximum value we can load when the capacity of the knapsack is from 0 to $W$.  

  - It is obvious that when `j < weight[0]`, `Opt(0, j)`should be 0, because the backpack capacity is less than the weight of item #0.

    When`j >= weight[0]`, `Opt(0,j)` will continue to hold `weight[0]` if it can hold it, and there will be an infinite number of each item.

- The first col represents when the capacity of the knapsack is 0, what's the maximum value we can load. Obviously, it's all 0 since the weight of the items are greater than 0. So we cannot load any items.

Then, we need to build the recurrence relation.

The above process can be abstracted as follows:

- Without item #i: The backpack capacity is `j`, and the maximum value without item i is `Opt[i - 1][j]`.

- With item #i: After the knapsack is empty of the capacity for item #i, the backpack capacity is `j - weight[i]`. `Opt[i][j - weight[i]]` is the maximum value when the backpack capacity is `j - weight[i]` and item #i is not placed. Then `Opt[i][j - weight[i]] + value[i]` (the value of item #i) is the maximum value obtained by placing item #i in the backpack.

Recursive formula: `Opt[i][j] = max(Opt[i - 1][j], Opt[i][j - weight[i]] + value[i]);`

### Codes

**pseudocode:**

```pseudocode
Algorithm UnboundedKnapsack(capacity, weights[1..n], values[1..n]):
    Let OPT[0..n-1][0..capacity] be a 2D array
    # Initialize the first row (only item 0 can be chosen)
    for j ← 0 to capacity do
        if j >= weights[0] then
            OPT[0][j] ← OPT[0][j - weights[0]] + values[0]
        else
            OPT[0][j] ← 0
        end if
    end for
    # Fill the DP table
    for i ← 1 to n-1 do
        for j ← 0 to capacity do
            if j < weights[i] then
                OPT[i][j] ← OPT[i-1][j]
            else
                OPT[i][j] ← max( OPT[i-1][j], OPT[i][j - weights[i]] + values[i] )
            end if
        end for
    end for
    return OPT[n-1][capacity]
```

example call:

```pseudocode
prices = {1, 5, 8, 9, 10, 17, 17, 20};
weights = {1, 2, 3, 4, 5, 6, 7, 8};
Ans = unbounded_knapsack_problem(N, weights, prices)
Ans: 22
•	8 (no cut): 20
•	4 + 4: 9 + 9 = 18
•	3 + 5: 8 + 10 = 18
```

**code in C++:**

```cpp
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
void question3() {
    int N = 8;
    std::vector<int>prices = {1, 5, 8, 9, 10, 17, 17, 20};
    std::vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << unbounded_knapsack_problem(N, weights, prices) << std::endl;
}
```

### Complexity

**Time complexity:**

The DP table has $n × W$ entries, where $n$ is the number of jewellery types and $W$ is the maximum capacity.

Each entry `DP[i][j]` is computed in O(1) time (a single max and addition).

Hence the overall **time complexity = O(n × W)**.

**Space complexity:**

The 2-D version uses `O(n × W)` space; it can be optimized to `O(W)` if only one dimension is kept.

**Efficiency:**

Because the algorithm runs in polynomial time with respect to $n$ and $W$, it is considered **efficient** for moderate input sizes.