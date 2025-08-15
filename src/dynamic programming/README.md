# Dynamic Programming

> ADD MatrixChain-Product Problem

## 1D Dynamic Programming

| Problem                                                                                         | Difficulty | Python                    | C++                  |
| ----------------------------------------------------------------------------------------------- | ---------- | ------------------------- | -------------------- |
| [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)                               | Easy       | [Python](./python/70.py)  | [C++](./cpp/70.cpp)  |
| [Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)             | Easy       | [Python](./python/746.py) | [C++](./cpp/746.cpp) |
| [House Robber](https://leetcode.com/problems/house-robber/)                                     | Medium     | [Python](./python/198.py) | [C++](./cpp/198.cpp) |
| [House Robber II](https://leetcode.com/problems/house-robber-ii/)                               | Medium     | [Python](./python/213.py) | [C++](./cpp/213.cpp) |
| [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)   | Medium     | [Python](./python/5.py)   | [C++](./cpp/5.cpp)   |
| [Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/)                 | Medium     | [Python](./python/647.py) | [C++](./cpp/647.cpp) |
| [Decode Ways](https://leetcode.com/problems/decode-ways/)                                       | Medium     | [Python](./python/91.py)  | [C++](./cpp/91.cpp)  |
| [Coin Change](https://leetcode.com/problems/coin-change/)                                       | Medium     | [Python](./python/322.py) | [C++](./cpp/322.cpp) |
| [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)             | Medium     | [Python](./python/152.py) | [C++](./cpp/152.cpp) |
| [Word Break](https://leetcode.com/problems/word-break/)                                         | Medium     | [Python](./python/139.py) | [C++](./cpp/139.cpp) |
| [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) | Medium     | [Python](./python/300.py) | [C++](./cpp/300.cpp) |
| [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)         | Medium     | [Python](./python/416.py) | [C++](./cpp/416.cpp) |

## 2D Dynamic Programming

| Problem                                                                                                                       | Difficulty | Python                     | C++                   |
| ----------------------------------------------------------------------------------------------------------------------------- | ---------- | -------------------------- | --------------------- |
| [Unique Paths](https://leetcode.com/problems/unique-paths/)                                                                   | Medium     | [Python](./python/62.py)   | [C++](./cpp/62.cpp)   |
| [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)                                       | Medium     | [Python](./python/1143.py) | [C++](./cpp/1143.cpp) |
| [Best Time to Buy And Sell Stock With Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/) | Medium     | [Python](./python/309.py)  | [C++](./cpp/309.cpp)  |
| [Coin Change II](https://leetcode.com/problems/coin-change-ii/)                                                               | Medium     | [Python](./python/518.py)  | [C++](./cpp/518.cpp)  |
| [Target Sum](https://leetcode.com/problems/target-sum/)                                                                       | Medium     | [Python](./python/494.py)  | [C++](./cpp/494.cpp)  |
| [Interleaving String](https://leetcode.com/problems/interleaving-string/)                                                     | Medium     | [Python](./python/97.py)   | [C++](./cpp/97.cpp)   |
| [Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)                     | Hard       | [Python](./python/329.py)  | [C++](./cpp/329.cpp)  |
| [Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)                                                 | Hard       | [Python](./python/115.py)  | [C++](./cpp/115.cpp)  |
| [Edit Distance](https://leetcode.com/problems/edit-distance/)                                                                 | Medium     | [Python](./python/72.py)   | [C++](./cpp/72.cpp)   |
| [Burst Balloons](https://leetcode.com/problems/burst-balloons/)                                                               | Hard       | [Python](./python/312.py)  | [C++](./cpp/312.cpp)  |
| [Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/)                                     | Hard       | [Python](./python/10.py)   | [C++](./cpp/10.cpp)   |

## Approaches

There are two approaches to formulate a dynamic programming solution:

1. Top-Down Approach:  This approach follows the memoization technique. It consists of recursion and caching.
2. Bottom-Up Approach: This approach uses the tabulation technique to implement the dynamic programming solution. In this approach, iteration replaces recursion.


   1. Analyzing Recursive Algorithms.
   Recurrence relation of recursive algorithms. 
   The recurrence relation for the time complexity of some problems are given below:

   * Fibonacci Number
   T(N) = T(N-1) + T(N-2) </br>
   Base Conditions: T(0) = 0 and T(1) = 1 \\

   * Binary Search
   T(N) = T(N/2) + C 
   Base Condition: T(1) = 1 \\

   * Merge Sort
   T(N) = 2 T(N/2) + CN
   Base Condition: T(1) = 1

## Common Problems

### The Fibonacci sequence

**Recursion Solution:**

```python
def fib(n):
    if n <= 1:
        return n
    else:
        return fib(n-1) + fib(n-2)

print(fib(10))  # Output: 55
```

**Dynamic Programming Solution:**

```python
def fib_dp(n):
    fib_values = [0, 1] + [0] * (n - 1)

    for i in range(2, n + 1):
        fib_values[i] = fib_values[i - 1] + fib_values[i - 2]

    return fib_values[n]

print(fib_dp(10))  # Output: 55
```

### The Coin Change Problem

**Recursion Solution:**

```python
def coinChange(coins, amount):
    if amount == 0:
        return 0

    if min(coins) > amount:
        return -1

    min_coins = float('inf')

    for c in coins:
        res = coinChange(coins, amount - c)
        if res != -1:
            min_coins = min(min_coins, res + 1)
    
    if min_coins == float('inf'):
        return -1
    else:
        return min_coins

print(coinChange([1, 2, 5], 11))  # Output: 3
```

**Dynamic Programming Solution:**

```python
def coinChange(coins, amount):
    dp = [0] + [float('inf')] * amount

    for coin in coins:
        for i in range(coin, amount + 1):
            dp[i] = min(dp[i], dp[i - coin] + 1)

    if min_coins == float('inf'):
        return -1
    else:
        return min_coins

print(coinChange([1, 2, 5], 11))  # Output: 3
```

### The Longest Common Subsequence Problem

**Recursion Solution:**

```python
def lcs(X, Y, m, n):
    # Base case: If we've reached the end of a string, return 0
    if m == 0 or n == 0:
       return 0
    # If the characters match, return 1 + result of LCS check for rest of the strings
    elif X[m-1] == Y[n-1]:
       return 1 + lcs(X, Y, m-1, n-1)
    # If they don't match, return the maximum result of LCS check by advancing one character in either string
    else:
       return max(lcs(X, Y, m, n-1), lcs(X, Y, m-1, n))

X = "AGGTAB"
Y = "GXTXAYB"
m = len(X)
n = len(Y)
print(lcs(X, Y, m, n))  # Output: 4
```

**Dynamic Programming Solution:**

```python
def lcs(X , Y):
    # Find lengths of two strings
    m = len(X)
    n = len(Y)

    # Declare the 2D DP array filled with zeroes
    dp = [[0]*(n+1) for _ in range(m+1)]

    # Build the DP array from the bottom up
    for i in range(1, m+1):
        for j in range(1, n+1):
            # If the characters match, the LCS length at this point is 1 + LCS length up to the previous characters
            if X[i-1] == Y[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            # If they don't match, the LCS length at this point is the maximum of the LCS length up to the previous character in string X or in string Y
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])

    return dp[m][n]

X = "AGGTAB"
Y = "GXTXAYB"
print(lcs(X, Y))  # Output: 4
```

## References

- [Playlist – Dynamic Programming, Tushar Roy](https://www.youtube.com/playlist?list=PLrmLmBdmIlpsHaNTPP_jHHDx_os9ItYXr)
