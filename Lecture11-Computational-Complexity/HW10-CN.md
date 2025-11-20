# Homework10

- [Homework10](#homework10)
  - [Question1](#question1)
      - [决策版定义](#决策版定义)
      - [证明该问题属于 NP](#证明该问题属于-np)
      - [从 SET COVER 归约（证明 NP-Hard）](#从-set-cover-归约证明-np-hard)
      - [归约正确性证明](#归约正确性证明)
      - [结论](#结论)
  - [Question2](#question2)
    - [决策问题定义](#决策问题定义)
    - [CLIQUE ∈ NP（高效认证）](#clique--np高效认证)
    - [从 Independent Set 归约，证明 NP-hard](#从-independent-set-归约证明-np-hard)
  - [Question3](#question3)

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

## Question2

Problem $\operatorname{CLIQUE}(G,k)$ asks whether, given a graph G, does G contain a k-clique? A k-clique is defined to be a set of k vertices such that each pair of these vertices shares an edge. Show via reduction that CLIQUE is NP-complete.

### 决策问题定义

决策版 CLIQUE 问题定义如下：

**输入：**

- 一张图 $G = (V, E)$
- 一个整数 k

**问题：**

图 G 中是否存在一个 **k-clique**？

也就是说，是否存在一个顶点子集 $S \subseteq V$，满足 $|S| = k$，并且对任意两个顶点 $u,v \in S$，都有边 $(u,v) \in E$。

### CLIQUE ∈ NP（高效认证）

先证明 CLIQUE 属于 NP。

**certificate（证明）：**

可以取一个大小为 k 的顶点集合 $S \subseteq V$。

**certifier（验证器）：**

给定 $(G,k)$ 和集合 S，验证器执行：

1. 检查 $|S| = k$。
2. 对 $S$ 中的每一对顶点 $u,v$，检查边 $(u,v)$ 是否在 $E$ 中。

顶点对最多有 $\binom{k}{2}$ 个，因此检查过程在输入规模的多项式时间内完成。

所以 CLIQUE 具有 efficient certification，属于 NP。

### 从 Independent Set 归约，证明 NP-hard

Independent Set（独立集）是 NP-complete，并且是从 3-SAT 用 gadgets 归约来的。

现在我们利用 图的补图（complement graph），把 Independent Set 归约到 CLIQUE。

**Independent Set 决策问题：**

输入：

- 图 $G = (V, E)$
- 整数 k

**问题：**

是否存在顶点集合 $S \subseteq V$，使得 $|S|\ge k$，并且 S 中任意两个顶点之间都 **没有边**（即没有一条边的两个端点都在 S 中）？课堂上已经证明过：Independent Set 是 NP-complete。

**Construction of the reduction / 归约的构造**

给定 Independent Set 的输入 $(G=(V,E), k)$，构造 CLIQUE 的输入 $(G'=(V,E'), k)$：

- $G'$ 的顶点集合与 G 相同： $V(G') := V(G)$。

- $G'$ 的边集合 $E'$ 取为 $E$ 的补图：

  对任意不同顶点 $u,v \in V$，定义 $(u,v) \in E' \iff (u,v) \notin E$。

也就是说：在原图中 **没有** 边的地方，在补图中就 **加** 一条边；原图中有边的地方，补图中就不连边。

这个构造只需要枚举所有顶点对一次，显然是多项式时间完成的。

参数 k 保持不变。

**归约正确性**

**“如果”方向（⇒）**

假设 $(G,k)$ 是 Independent Set 的 YES 实例。

那么存在集合 $S \subseteq V$，满足 $|S|\ge k$，并且对任何 $u,v \in S$，在原图 G 中都 **没有** 边 $(u,v) \in E$。

根据补图的构造，在 G 中没有边的地方，在 G' 中就一定有边：

也就是对所有 $u,v \in S$，都有 $(u,v) \in E'$。

因此在 $G'$ 中，集合 S 内的任意两点都相连，所以 $S$ 在 $G'$ 中构成一个大小至少为 k 的 clique。

于是 $(G',k)$ 是 CLIQUE 的 YES 实例。

**“只有如果”方向（⇐）**

反过来，假设 (G',k) 是 CLIQUE 的 YES 实例。

那么存在集合 $S \subseteq V$，满足 $|S|\ge k$，并且在 G' 中，S 中任意两个顶点之间都有边 $(u,v) \in E'$。

由补图定义，这意味着在原图 G 中，对所有 $u,v \in S$，都 **没有** 边 $(u,v) \in E$。

因此在 G 中，集合 S 中任意两个顶点都不相邻，S 就是一个大小至少为 k 的 independent set。

于是 $(G,k)$ 是 Independent Set 的 YES 实例。

## Question3

Recall the 3-SAT problem: Given a 3-CNF input formula, it tries to find an assignment of variables that satisfies **ALL** given clauses. Now, we consider a variation — the partial satisfiability problem, denoted as $3\text{-Sat}(\alpha)$, for a specified constant $\alpha$. Here, we are given a collection of $k$ clauses, each of which contains exactly three literals, and we are asked to determine whether there is an assignment of true/false values to the literals such that **at least $\alpha k$ clauses will be true**. Note that for $\alpha = 1$, we have the problem $3\text{-Sat}(1)$ which is exactly the 3-SAT problem as per definition. We want to analyze the problem corresponding to a smaller $\alpha$, in particular, $\alpha = \frac{15}{16},$ which gives us the problem $3\text{-Sat}\left(\frac{15}{16}\right)$.

**Show that the problem $3\text{-Sat}\left(\frac{15}{16}\right)$ is NP-complete.** (20 points)

**Hint:** If $x, y, z$ are variables, there are eight possible clauses containing them:

$(x \lor y \lor z),\ (\lnot x \lor y \lor z),\ (x \lor \lnot y \lor z),\ $

$(x \lor y \lor \lnot z),\ (\lnot x \lor \lnot y \lor z),\ (\lnot x \lor y \lor \lnot z),\ (x \lor \lnot y \lor \lnot z),\ (\lnot x \lor \lnot y \lor \lnot z).$

> [!tip]
>
> 这题真不简单啊。考试基本不可能想到。
>
> 1. 首先就是这个hint，这个hint是三个元素的所有子句能形成的组合。一个重要的性质就是，==无论如何组合，都必须有一个为假！（这个性质很重要，7必错1）==
> 2. 然后要把原来的子句个数，扩充到8的倍数。如何扩充呢，就加入必真子句，比如 $x \or \lnot x \or y$ 这种。
> 3. 扩充成8的倍数之后。每8个为一组，每一组分别加入一组 hint 中提到的组合子句集合。形成一个8+8的组合。此时这8+8的组合，是不可能全对的，必须错一个。前8个就是一个basic 3-sat, 后8必须错一个。因此就得到这个 15/16 了。
>
> 整体的思路就是如何。

> [!caution]
>
> Gadget 的 3 个变量必须是新变量（fresh variables），
>
> 因为如果 gadget 与原公式共享变量，则原公式的约束可能强迫 gadget 子句全部变为真（甚至 8/8 为真），
>
> 从而破坏 gadget 的“恰好 7 真 1 假”的关键性质，
>
> 进而使整个 15/16 构造失效。