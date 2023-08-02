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


# Example graph represented as an adjacency list
graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F'],
    'D': [],
    'E': ['F'],
    'F': []
}

# Starting DFS from node 'A'
# dfs_iterative(graph, 'A')
dfs_recursive(graph, 'A')
