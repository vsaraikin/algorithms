# The Ultimate Handbook for Data Structures & Algorithms

## References:
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

## Problems:
* [Blind 75 by topic](https://www.teamblind.com/post/New-Year-Gift---Curated-List-of-Top-75-LeetCode-Questions-to-Save-Your-Time-OaM1orEU)
* [Top 150 Leetcode](https://leetcode.com/studyplan/top-interview-150/)

## Books
* [DSA using Python](https://runestone.academy/ns/books/published/pythonds/index.html)
* [DSA in Python](./books/Michael%20T.%20Goodrich,%20Roberto%20Tamassia,%20Michael%20H.%20Goldwasser%20-%20Data%20Structures%20and%20Algorithms%20in%20Python-Wiley%20(2013).pdf)
* [Introduction to Algorithms](./books/Thomas%20H.%20Cormen,%20Charles%20E.%20Leiserson,%20Ronald%20L.%20Rivest,%20Clifford%20Stein%20-%20Introduction%20to%20Algorithms-The%20MIT%20Press%20(2022).pdf)


## Plan:
todo: later it will be toc

YANDEX: Sorting the array
YANDEX: Hashmap?

1. Time & Space Complexity.
2. Recursion
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

   2. Maximum Recursive Depth in Python
   3. Linear, Binary and Multiple Recursion
3. Divide and conquer
   1. Exercises
      1. 
4. Greedy algorithms
5. Basic DS
   1. Array
      1. Techniques – Two poiners
   2. Linked List
      1. Single-linked
      2. Double-linked
   3. Stack
   4. Queue
   5. Deque
   6. Matrix/Grid
   7. Graphs
      1. Data Structures for Graphs
      2. Graph Traversals
         1. DFS
         2. BFS
      3. Directed Acyclic Graphs
      4. Shortest Paths
         1. Weighted Graphs
         2. Dijkstra’s Algorithm
   8. Hashmaps
   9.  Heap
      1.  Heapsort
   10. Trees
       1.  Binary tree
       2.  Binary search tree
       3.  Trie

6. Basic Algorithms
   1. Searching Algorithm
      1. Merge Sort
      2. Bubble Sort
      3. 
   2. Sorting Algorithm
   3. Divide and Conquer Algorithm
   4. Greedy Mehtodology
   5. Recursion
   6. Backtracking Algorithm
   7. Dynamic Programming
   8. Pattern Searching
   9.  Mathematical Algorithms
   10. Geometric Algorithms
   11. Bitwise Algorithms
   12. Randomized Algorithms
   13. Branch and Bound Algorithm
7. Exercises
8. Advanced DS
9.  Exercises
10. Memory Management & Allocation


## Advanced stuff
1.  Dynamic Programming
   1.  MatrixChain-Product
2.  Priority queue
3.  B-Tree
4.  AVL
5.  Red-black


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

### Arrays

Arrays hold values of the same type at contiguous memory locations.

#### Terms:

Subarray - [3, 6, 1] is subarray of [2, **3, 6, 1**, 5, 4] (contiguous elements). 

Subsequence - [3, 1, 5] is a subsequence of [2, **3**, 6, **1**, **5**, 4] (noncontiguous elements).

#### Techniques:
Sliding window
Two pointers
Traversing from the right


A divide-and-conquer algorithm recursively breaks down a problem into two or more sub-problems of the same or related type, until these become simple enough to be solved directly. The solutions to the sub-problems are then combined to give a solution to the original problem.