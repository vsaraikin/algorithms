# Dynamic Programming

> ADD MatrixChain-Product Problem

## Problems

| Name/Link                                                                                                      | Attempts | Solved on My Own | Figured out algorithm | LC Premium |
| -------------------------------------------------------------------------------------------------------------- | -------- | ---------------- | --------------------- | ---------- |
| [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)                                              | 1        | -                | -                     | No         |
| [Coin Change](https://leetcode.com/problems/coin-change/)                                                      | 1        | -                | -                     | No         |
| [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)                | 1        | -                | -                     | No         |
| [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)                        | 1        | -                | -                     | No         |
| [Word Break Problem](https://leetcode.com/problems/word-break/)                                                | 1        | -                | -                     | No         |
| [Combination Sum](https://leetcode.com/problems/combination-sum-iv/)                                           | 1        | -                | -                     | No         |
| [House Robber](https://leetcode.com/problems/house-robber/)                                                    | 1        | -                | -                     | No         |
| [House Robber II](https://leetcode.com/problems/house-robber-ii/)                                              | 1        | -                | -                     | No         |
| [Decode Ways](https://leetcode.com/problems/decode-ways/)                                                      | 1        | -                | -                     | No         |
| [Unique Paths](https://leetcode.com/problems/unique-paths/)                                                    | 1        | +                | +                     | No         |
| [Jump Game](https://leetcode.com/problems/jump-game/)                                                          | -        | -                | -                     | No         |
| [Edit Distance](https://leetcode.com/problems/edit-distance/)                                                  | -        | -                | -                     | No         |
| [Minimum Score Triangulation of Polygon](https://leetcode.com/problems/minimum-score-triangulation-of-polygon) | -        | -                | -                     | No         |

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
