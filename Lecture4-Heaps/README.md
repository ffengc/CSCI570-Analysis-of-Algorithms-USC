# Lecture4-Heaps

- [Lecture4-Heaps](#lecture4-heaps)
  - [what is the Priority Queues](#what-is-the-priority-queues)
  - [Binary Heap](#binary-heap)
    - [full binary tree and complete binary tree](#full-binary-tree-and-complete-binary-tree)
    - [Max Binary Heap Complexity Analysis](#max-binary-heap-complexity-analysis)
    - [build the heap, O(n) or O(nlogn)](#build-the-heap-on-or-onlogn)
    - [merge problem](#merge-problem)
    - [Code](#code)
  - [Binomial Heap](#binomial-heap)
  - [Fibonacci Heap](#fibonacci-heap)

## what is the Priority Queues

a priority queue has to perform these two operations fast!

- insert an element into the set
- find the smallest element in the set

try with some data structures:

| Implementation       | Insert | Find Min |
|----------------------|--------|----------|
| Array Implementation | O(1)   | O(n)     |
| Sorted Array         | O(n)   | O(1)     |
| Linked List          | O(1)   | O(n)     |
| Sorted Linked List   | O(n)   | O(1)     |

## Binary Heap

### full binary tree and complete binary tree

满二叉树和完全二叉树的定义。这部分我个人比较熟悉了，稍微简单略过。

**some conclusions need to remember:**

assume that a node in a complete binary tree: $i^{th}$, (root number is $1^{st}$)

- its parent: $i/2$
- its left child: $2 \cdot i \ (2\cdot i \le n, \text{otherwise it has no left child})$
- its right child: $2 \cdot i + 1 \ (2\cdot i \le n, \text{otherwise it has no right child})$

注意一下，课件上是上面的这个写法，根节点从1开始算。

一般写代码根节点是从0开始算：
- Parent(i) = (i-1)/2 （整除取整）
- Lchild(i) = 2i + 1
- Rchild(i) = 2i + 2


### Max Binary Heap Complexity Analysis

| Operation (Max Heap 大顶堆)      | Complexity | Explain |
|----------------------|--------|-------|
| find max | O(1)   | 直接取堆顶元素 |
| insert         | O(logn)   |插入到数组最后，**向上调整**|
| extract max          | O(logn)   |交换到最后，**向下调整**|
| delete   | O(logn)   |同理|
| decrease-key| O(logn)|同理|


### build the heap, O(n) or O(nlogn)

可以O(n)建堆！这个很重要。

建堆要用向下调整建，才能做到 O(n)。

### merge problem

what is the best runtime to merge two binary heaps of size n ?


可以做到 O(n).

把另一个堆数组的内容放到第一个堆的后面，然后调用建堆，此时是 O(n).

**remember:** build the heap can be O(n).

### Code

Simulate the implementation of STL `priority_queue`.

code: [stl_priority_queue.hpp](./stl_priority_queue.hpp)

## Binomial Heap

## Fibonacci Heap