# Exercises and Types of Problems

## Neetcode 150

- [Array & Hashing](./array/README.md)
- [Two Pointers](./two-pointers/README.md)
- [Sliding Window](./sliding-window/README.md)
- [Stack](./stack/README.md)
- [Binary Search](./binary%20search/README.md)
- [Linked List](./linked%20list/README.md)
- [Trees](./tree/README.md)
- [Tries](./tries/README.md)
- [Heap / PQ](./heap%20&%20pq/README.md)
- [Backtracking](./backtracking/README.md)
- [Graph](./graph/README.md)
- [Advanced Graph](./advanced%20graphs/README.md)
- [Dynamic Programming](./dynamic%20programming/README.md)
- [Greedy](./greedy/README.md)
- [Intervals](./intervals/README.md)
- [Math & Geometry](./math/README.md)
- [Binary](./binary/README.md)

## Misc

- [Divide & Conquer](./divide%20&%20conquer/README.md)
- Merkle Tree
- Trie

## Approach to a problem

1. If I cannot solve problem myself in 20 mins, go the hint.
2. If hint did not help in 10 mins, watch solution.
3. Go back the day after and resolve problem.

The majority of the tasks are taken from [Blind 75](https://www.teamblind.com/post/New-Year-Gift---Curated-List-of-Top-75-LeetCode-Questions-to-Save-Your-Time-OaM1orEU) and [Neetcode 150](https://neetcode.io/practice)

## Theory

### Time complexity

- $O(1)$

    ```python
    l = [1, 2, 3, 4, 5]
    for i in l:
        print(i)
    ```

- $O(log\space n)$

    ```python
    # Binary recursive search
    def binary_search(arr, target):
        left = 0
        right = len(arr) - 1

        while left <= right:
            mid = (left + right) // 2

            if arr[mid] == target:
                return mid
            elif arr[mid] < target:
                left = mid + 1
            else:
                right = mid - 1

        return -1
    ```

- $O(N)$

    ```python
    l = [1, 2, 3, 4, 5]
    copy_of_l = l.copy()
    for i in copy_of_l:
        print(i)
    ```

- $O(N^2)$

    ```python
    n = 5
    matrix = [[0 for _ in range(n)] for _ in range(n)]
    for row in matrix:
        for elem in row:
            print(elem)
    ```

### Space Complexity

Typically from the examples in the Internet Time & Space complexity would look the same. E.g. merge sort time & space complexity – $O(n\space logn)$. Below are examples to catch the difference.

### Solution 1: Naive Recursive Approach

```python
def fib_naive(n):
    if n <= 1:
        return n
    return fib_naive(n - 1) + fib_naive(n - 2)
```

- Time Complexity: Exponential $(O(2^n))$ as it recalculates the same Fibonacci numbers multiple times.
- Space Complexity: Linear $(O(n))$ due to the call stack used for recursion.

### Solution 2: Dynamic Programming Approach with Caching

```python
def fib_dynamic(n, cache={}):
    if n in cache:
        return cache[n]
    if n <= 1:
        return n
    result = fib_dynamic(n - 1, cache) + fib_dynamic(n - 2, cache)
    cache[n] = result
    return result
```

- Time Complexity: Linear $(O(n))$ as it computes each Fibonacci number once and stores it in the cache.
- Space Complexity: Linear $(O(n))$ due to the cache that stores previously calculated Fibonacci numbers.