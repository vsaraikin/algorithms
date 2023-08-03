# Graphs

## Problems


| Name/Link                                                                                                                            | LC Premium | Attempts | Solved on My Own | Figured out Algorithm |
| ------------------------------------------------------------------------------------------------------------------------------------ | ---------- | -------- | ---------------- | --------------------- |
| [Clone Graph](https://leetcode.com/problems/clone-graph/)                                                                            | No         | 1        | No               | Yes                   |
| [Course Schedule](https://leetcode.com/problems/course-schedule/)                                                                    | No         | 1        | No               | Yes                   |
| [Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)                                            | No         | -        | -                | -                     |
| [Number of Islands](https://leetcode.com/problems/number-of-islands/)                                                                | No         | -        | -                | -                     |
| [Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)                                          | No         | -        | -                | -                     |
| [Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)                                                                  | Yes        | -        | -                | -                     |
| [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/)                                                                  | Yes        | -        | -                | -                     |
| [N of Conn. Components in an Undirected Graph](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) | Yes        | -        | -                | -                     |



## Theory 


## Aproaches
1. DFS:
```python
def dfs_iterative(graph: dict[str], start: str):
    visited = set()
    stack = [start]
    
    while stack:
        current_node = stack.pop()
        if current_node not in visited:
            visited.add(current_node)
            print(current_node)
            
            for neighbour in graph[current_node]:
                if neighbour not in stack:
                    stack.append(neighbour)
                 
                 
def dfs_recursive(graph: dict[str], current_node: str, visited=None):
    if not visited:
        visited = set()
        
    visited.add(current_node)
    print(current_node)
    
    for neighbour in graph[current_node]:
        if neighbour not in visited:
            dfs_recursive(graph, neighbour, visited)
```

2. BFS
3. Dijsktra
4. 


## Common problems