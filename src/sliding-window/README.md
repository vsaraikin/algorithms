# Sliding Window

| Name                                                                                                                            | Level  | Solution           | LC Premium |
| ------------------------------------------------------------------------------------------------------------------------------- | ------ | ------------------ | ---------- |
| [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)                               | Easy   | [Python](python/121.py21.py) |            |
| [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | Medium | [Python](python/3.py/3.py)   |            |
| [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)               | Medium | [Python](python/424.py24.py) |            |
| [Permutation in String](https://leetcode.com/problems/permutation-in-string/)                                                   | Medium | [Python](python/567.py67.py) |            |
| [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)                                           | Medium | [Python](python/209.py09.py) |            |
| [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)                                             | Hard   | [Python](python/76.py76.py)  |            |
| [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)                                                 | Hard   | [Python](python/239.py39.py) |            |


## Theory

A sliding window algorithm is a technique used for efficiently processing arrays or lists by maintaining a "window" of elements as it moves through the data. This window is typically defined by two pointers: the left and right pointers. 

## Common Problems

Typically the following terms mentioned in the task:
- Array
- String
- Sub Array
- Sub String
- Largest Sum
- Maximum Sum
- Minimum Sum


## Template

```python
def sliding_window_problem(s):
    # Initialize the left and right pointers
    left, right = 0, 0

    # Initialize any additional variables or data structures needed

    # Initialize the result or answer variable
    result = []

    while right < len(s):
        # Expand the window by moving the right pointer to the right
        # Update any data or variables as needed

        # Check if the current window satisfies the problem criteria
        while window_satisfies_criteria:
            # Update the result or answer based on the current window

            # Contract the window by moving the left pointer to the right
            # Update any data or variables as needed

        # Continue expanding the window by moving the right pointer to the right
        # Update any data or variables as needed

    return result
```