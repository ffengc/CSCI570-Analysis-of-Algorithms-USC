# Homework10

- [Homework10](#homework10)
  - [Question1](#question1)
      - [决策版定义](#决策版定义)
      - [证明该问题属于 NP](#证明该问题属于-np)
      - [从 SET COVER 归约（证明 NP-Hard）](#从-set-cover-归约证明-np-hard)
      - [归约正确性证明](#归约正确性证明)
      - [结论](#结论)

**如何证明一个问题是 NP-Complete / NP-Hard (Q1):**

- 定义决策版的问题
- 证明该问题属于 NP 问题（用 efficient certification)
- 从一个 NP-Complete 问题上规约 
- 规约的正确性证明（两个方向，如果问题A是YES则..., 如果问题B是YES则, ...）
- 结论

## Question1

The Sushi Express wants to implement a new feature, "order batching." The menu consists of a set of disired food items $F$ and set of combos $c_1, ..., c_n$ where each combo is a set of food items along with a price - we represent combo $c_i = (\{f_i^1, f_i^2, ..., f_i^k\}, p_i)$, where each $f_i^j$ is a food item in the combo. If a student orders $c_i$, they receive each of the food items, and they pay the cost $p_i$. In the new order batching system, the students would input a list of food items that they want, and the order batching system should find the cheapest set of combos, which would include at least one of each desired food item. Write the decision version of this problem, and show via reduction that this decision problem is NP Hard.

> Example:
>
> Foods F = {Fries, Burger, Pizza, drink, sandwich, cookie, chips}
>
> C1 = ({Fries, Pizza, cookie}, 10$)
>
> C2 = ({Fries, drink, sandwich}, 15$)
>
> C3 = ({drink, Pizza, chips, burger}, 17$)

#### 决策版定义

我们把寿司套餐问题的决策版定义如下：

**输入：**

- 一组食物种类 $F$。

- 一组套餐 $C_1,\dots,C_n$，其中

  $C_i = (S_i, p_i), \quad S_i \subseteq F$.

- 学生想要的食物集合 $R \subseteq F$。

- 一个预算上限 $B$。

**问题：**

是否存在一个套餐索引集合 $I \subseteq \{1,\dots,n\}$，使得

1. $\displaystyle \bigcup_{i\in I} S_i \supseteq R$（联合起来覆盖所有想要的食物），
2. $\displaystyle \sum_{i\in I} p_i \le B$（总价格不超过预算）？

#### 证明该问题属于 NP

一个 certificate（证明）可以是套餐下标集合 $I\subseteq\{1,\dots,n\}$。

certifier（验证器）在多项式时间内做：

1. 计算 $\sum_{i\in I} p_i$，检查是否 $\le B$。
2. 计算 $\bigcup_{i\in I} S_i$，检查是否包含 $R$ 中所有食物。
3. （可选）检查 $I$ 中没有重复元素。

这些操作只需要扫描集合与相加，均为多项式时间。

因此该问题具有 efficient certification，属于 NP。

#### 从 SET COVER 归约（证明 NP-Hard）

我们从经典的 NP-complete 问题 **SET COVER** 做归约。

SET COVER 的输入：

- 一个元素全集 $U = \{e_1,\dots,e_m\}$
- 一组子集 $S_1,\dots,S_n \subseteq U$
- 一个整数 $k$

我们构造寿司套餐实例如下：

1. 食物集合设为

   $F := U$.

2. 对每个子集 $S_i$，创建一个套餐

   $C_i = (S_i, p_i)$,

   并设所有套餐的价格为

   $p_i := 1$.

3. 想要的食物集合设为

   $R := U$.

4. 预算上限设为

   $B := k$.

该构造显然是多项式时间完成。

#### 归约正确性证明

**（⇒）如果 SET COVER 的答案是 YES：**

假设存在索引集合 $I$，使得 $|I| \le k$ 且

$\bigcup_{i\in I} S_i = U$。

在寿司套餐问题中选同样的 $I$：

- 总价为 $\sum_{i\in I} p_i = |I| \le B (=k)$，

- 覆盖的食物是

  $\bigcup_{i\in I} S_i = U = R$。

因此寿司套餐实例答案也是 YES。

**（⇐）如果寿司套餐问题答案是 YES：**

假设存在套餐集合 I 满足：

- $\bigcup_{i\in I} S_i \supseteq R (=U)$，
- $\sum_{i\in I} p_i \le B (=k)$。

由于每个 $p_i = 1$，总价 $\le B$ 即意味着 $|I| \le k$。

并且这些套餐覆盖了全部 U。

因此在 SET COVER 里，同样的 I 是一个大小 $≤ k$ 的覆盖。

故 SET COVER 的答案也是 YES。

#### 结论

我们已经证明：

1. 寿司套餐决策问题属于 NP。
2. SET COVER 能多项式归约到寿司套餐问题。
3. 因此寿司套餐问题是 NP-Hard。
4. 结合第 1 点，它实际上是 NP-Complete。