from collections import deque


def bfs(graph, start_node):
    visited = set()          # To keep track of visited nodes
    queue = deque([start_node])  # Initialize the queue with the starting node

    while queue:
        current_node = queue.popleft()  # Get the next node from the queue
        if current_node not in visited:
            print(current_node)  # Process the current node
            visited.add(current_node)     # Mark the current node as visited

            # Add unvisited neighbors to the queue
            for neighbor in graph[current_node]:
                if neighbor not in visited:
                    queue.append(neighbor)
                    

graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}


bfs(graph, 'A')
