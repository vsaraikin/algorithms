# The Ultimate Handbook for Data Structures & Algorithms

This repository contains:
- `src/` problems, approaches, ds & a to solve
- `books/` to reference
- ...

  
## Theory

## Time complexity
* $O(1)$
```python
l = [1, 2, 3, 4, 5]
for i in l:
    print(i)
```
* $O(log\space n)$
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
* $O(N)$
```python
l = [1, 2, 3, 4, 5]
copy_of_l = l.copy()
for i in copy_of_l:
    print(i)
```
* $O(N^2)$
```python
n = 5
matrix = [[0 for _ in range(n)] for _ in range(n)]
for row in matrix:
    for elem in row:
        print(elem)
```

## Space Complexity


## References
* [Tech Interview Handbook — Cheatsheet](https://www.techinterviewhandbook.org/algorithms/study-cheatsheet/)
* [enjoyalgorithms — Guide to DSA](https://enjoyalgorithms.com/blog/step-by-step-guidance-to-master-data-structure-and-algorithms-for-coding-interview)
* [DSA Tutorial](https://www.geeksforgeeks.org/learn-data-structures-and-algorithms-dsa-tutorial/)
* [Two Pointers Exercises](https://towardsdatascience.com/two-pointer-approach-python-code-f3986b602640)

## Videos
* [MIT Lectures 2011 — DSA](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/video_galleries/lecture-videos/)
<!-- https://www.coursera.org/learn/algorithms-part1
https://www.coursera.org/learn/algorithms-part2
https://www.educative.io/courses/coderust-hacking-the-coding-interview
https://www.coursera.org/specializations/algorithms?irclickid=WRcwHl22gxyPT1IyXUS9p1tJUkFzh42c1XRG3U0&irgwc=1&utm_medium=partners&utm_source=impact&utm_campaign=3259109&utm_content=b2c -->

## Books
* [DSA using Python](https://runestone.academy/ns/books/published/pythonds/index.html)
* [DSA in Python](./books/Michael%20T.%20Goodrich,%20Roberto%20Tamassia,%20Michael%20H.%20Goldwasser%20-%20Data%20Structures%20and%20Algorithms%20in%20Python-Wiley%20(2013).pdf)
* [Introduction to Algorithms](./books/Thomas%20H.%20Cormen,%20Charles%20E.%20Leiserson,%20Ronald%20L.%20Rivest,%20Clifford%20Stein%20-%20Introduction%20to%20Algorithms-The%20MIT%20Press%20(2022).pdf)



