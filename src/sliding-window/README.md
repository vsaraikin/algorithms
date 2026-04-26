# Sliding Window

![solved: 7](https://img.shields.io/badge/solved-7-blue) ![Easy: 1](https://img.shields.io/badge/Easy-1-brightgreen) ![Medium: 4](https://img.shields.io/badge/Medium-4-yellow) ![Hard: 2](https://img.shields.io/badge/Hard-2-red) ![Python: 7](https://img.shields.io/badge/Python-7-3776AB) ![C%2B%2B: 5](https://img.shields.io/badge/C%2B%2B-5-00599C)

> A movable subrange over an array or string; expand/contract it to satisfy a constraint in O(n).

## Problems

| # | Problem | Difficulty | Python | C++ |
| --- | --- | --- | --- | --- |
| 121 | [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | Easy | [solution.py](./121/solution.py) | [solution.cpp](./121/solution.cpp) |
| 3 | [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | Medium | [solution.py](./3/solution.py) | [solution.cpp](./3/solution.cpp) |
| 209 | [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) | Medium | [solution.py](./209/solution.py) | [solution.cpp](./209/solution.cpp) |
| 424 | [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) | Medium | [solution.py](./424/solution.py) | [solution.cpp](./424/solution.cpp) |
| 567 | [Permutation in String](https://leetcode.com/problems/permutation-in-string/) | Medium | [solution.py](./567/solution.py) | [solution.cpp](./567/solution.cpp) |
| 76 | [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) | Hard | [solution.py](./76/solution.py) | — |
| 239 | [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) | Hard | [solution.py](./239/solution.py) | — |

## Template

```python
def sliding_window(s):
    left = 0
    result = []

    for right in range(len(s)):
        # expand window with s[right]

        while window_violates_constraint():
            # shrink window from the left
            left += 1

        # record answer for the current valid window

    return result
```
