# https://leetcode.com/problems/clone-graph

class Node:
    def __init__(self, val):
        self.val = val
        self.neighbors = []

class Solution:
    def cloneGraph(self, node: Node):
        def dfs(current_node: Node, clone_map: dict):
            if not current_node:
                return None

            if current_node in clone_map:
                return clone_map[current_node]

            clone_node = Node(current_node.val)
            clone_map[current_node] = clone_node

            for neighbor in current_node.neighbors:
                clone_neighbor = dfs(neighbor, clone_map)
                clone_node.neighbors.append(clone_neighbor)

            return clone_node

        return dfs(node, {})
      
            
        
adjList = [[2,4],[1,3],[2,4],[1,3]]
graph = []
for i in range(len(adjList)):
    graph.append(Node(i+1))

for i in range(len(adjList)):
    for neighbor_idx in adjList[i]:
        graph[i].neighbors.append(graph[neighbor_idx - 1])

s = Solution()
cloned_graph = s.cloneGraph(graph[0])  # Get the deep copy of the graph
