# Graphs

![solved: 4/13](https://img.shields.io/badge/solved-4/13-blue) ![Medium: 4/12](https://img.shields.io/badge/Medium-4/12-yellow) ![Hard: 0/1](https://img.shields.io/badge/Hard-0/1-red) ![Python: 4](https://img.shields.io/badge/Python-4-3776AB)

> BFS, DFS, and Union-Find over explicit or implicit graphs.

## Problems

| # | Problem | Difficulty | Python | C++ |
| --- | --- | --- | --- | --- |
| 130 | [Surrounded Regions](https://leetcode.com/problems/surrounded-regions/) | Medium | [solution.py](./130/solution.py) | — |
| 133 | [Clone Graph](https://leetcode.com/problems/clone-graph/) | Medium | [solution.py](./133/solution.py) | — |
| 200 | [Number of Islands](https://leetcode.com/problems/number-of-islands/) | Medium | — | — |
| 207 | [Course Schedule](https://leetcode.com/problems/course-schedule/) | Medium | [solution.py](./207/solution.py) | — |
| 210 | [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) | Medium | — | — |
| 261 | [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/) | Medium | — | — |
| 286 | [Walls and Gates](https://leetcode.com/problems/walls-and-gates/) | Medium | — | — |
| 323 | [Number of Connected Components in an Undirected Graph](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) | Medium | — | — |
| 417 | [Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/) | Medium | [solution.py](./417/solution.py) | — |
| 684 | [Redundant Connection](https://leetcode.com/problems/redundant-connection/) | Medium | — | — |
| 695 | [Max Area of Island](https://leetcode.com/problems/max-area-of-island/) | Medium | — | — |
| 994 | [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) | Medium | — | — |
| 127 | [Word Ladder](https://leetcode.com/problems/word-ladder/) | Hard | — | — |

## Representations

```python
# Adjacency list (unweighted)
adj = {0: [1, 2], 1: [0, 2, 3], 2: [0, 1], 3: [1]}

# Adjacency list (weighted)
adj = {0: [(1, 2.5), (2, 1)], 1: [(0, 2.5), (2, 4), (3, 3)]}
```

## Traversals

```python
def bfs(graph, start):
    visited, queue = {start}, deque([start])
    while queue:
        node = queue.popleft()
        for nb in graph[node]:
            if nb not in visited:
                visited.add(nb)
                queue.append(nb)

def dfs(graph, node, visited):
    visited.add(node)
    for nb in graph[node]:
        if nb not in visited:
            dfs(graph, nb, visited)
```
