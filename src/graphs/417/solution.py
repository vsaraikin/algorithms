# https://leetcode.com/problems/course-schedule

class Solution:
    def pacificAtlantic(self, heights: list[list[int]]) -> list[list[int]]:
        def dfs(row, col, visited):
            visited[row][col] = True
            # ->, ⬆, <-, ⬇
            for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]: # row, col
                new_row, new_col = row + dr, col + dc
                if 0 <= new_row < m and 0 <= new_col < n and not visited[new_row][new_col] and heights[new_row][new_col] >= heights[row][col]:
                    dfs(new_row, new_col, visited)

        if not heights:
            return []

        m, n = len(heights), len(heights[0]) # m – rows, n - columns
        visited_pacific = [[False for _ in range(n)] for _ in range(m)]
        visited_atlantic = [[False for _ in range(n)] for _ in range(m)]

        # Start DFS from the Pacific coast (top and left edges)
        for row in range(m):
            dfs(row, 0, visited_pacific)
        for col in range(n):
            dfs(0, col, visited_pacific)

        # Start DFS from the Atlantic coast (bottom and right edges)
        for row in range(m):
            dfs(row, n - 1, visited_atlantic)
        for col in range(n):
            dfs(m - 1, col, visited_atlantic)

        # Find the cells that can flow to both oceans
        result = []
        for row in range(m):
            for col in range(n):
                if visited_pacific[row][col] and visited_atlantic[row][col]:
                    result.append([row, col])

        return result

s = Solution()
assert [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]] == \
    s.pacificAtlantic([[1,2,2,3,5],
                       [3,2,3,4,4],
                       [2,4,5,3,1],
                       [6,7,1,4,5],
                       [5,1,1,2,4]])

assert [[0,0]] == s.pacificAtlantic([[1]])
