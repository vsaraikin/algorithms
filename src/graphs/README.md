# Graphs

![solved: 4](https://img.shields.io/badge/solved-4-blue) ![Medium: 4](https://img.shields.io/badge/Medium-4-yellow) ![Python: 4](https://img.shields.io/badge/Python-4-3776AB)

> BFS, DFS, and Union-Find over explicit or implicit graphs.

## Problems

| # | Problem | Difficulty | Python | C++ |
| --- | --- | --- | --- | --- |
| 130 | [Surrounded Regions](https://leetcode.com/problems/surrounded-regions/) | Medium | [solution.py](./130/solution.py) | — |
| 133 | [Clone Graph](https://leetcode.com/problems/clone-graph/) | Medium | [solution.py](./133/solution.py) | — |
| 207 | [Course Schedule](https://leetcode.com/problems/course-schedule/) | Medium | [solution.py](./207/solution.py) | — |
| 417 | [Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/) | Medium | [solution.py](./417/solution.py) | — |

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
