# https://leetcode.com/problems/course-schedule

class Solution:
    def build_graph(self, numCourses: int, prerequisites: list[list[int]]):
        # Create an adjacency list to represent the graph
        adj_list = [[] for _ in range(numCourses)]

        # Fill the adjacency list with prerequisites
        for a, b in prerequisites:
            adj_list[a].append(b)
        
        return adj_list
    
    # Recursive solution
    def canFinish(self, numCourses: int, prerequisites: list[list[int]]) -> bool:
        adj_list = self.build_graph(numCourses, prerequisites)

        visited = [False] * numCourses

        def has_cycle(course):
            if visited[course]:
                return True

            # Mark the course as visited and add it to the current path
            visited[course] = True

            # Explore all the neighbors of the current course
            for neighbor in adj_list[course]:
                if has_cycle(neighbor):
                    return True

            visited[course] = False
            return False

        # Check for cycles starting from each course
        for course in range(numCourses):
            if has_cycle(course):
                return False

        return True

    def canFinish(self, numCourses: int, prerequisites: list[list[int]]) -> bool:
        adj_list = self.build_graph(numCourses, prerequisites)

        # Each vertex can have 3 different states:
        # state 0   : vertex is not visited. It's a default state.
        # state -1  : vertex is being processed. Either all of its descendants
        #             are not processed or it's still in the function call stack.
        # state 1   : vertex and all its descendants are processed.
        state = [0] * numCourses

        def hasCycle(v):
            if state[v] == 2:
                # This vertex is processed so we pass.
                return False
            if state[v] == 1:
                # This vertex is being processed and it means we have a cycle.
                return True

            # Set state to 1
            state[v] = 1

            for i in adj_list[v]:
                if hasCycle(i):
                    return True

            state[v] = 2
            return False

        # we traverse each vertex using DFS, if we find a cycle, stop and return
        for v in range(numCourses):
            if hasCycle(v):
                return False

        return True
            
s = Solution()
# assert s.canFinish(2, [[1,0]]) == True
assert s.canFinish(2, [[1,0], [0,1]]) == False